/*
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/wait.h>

#include "atomisp-psys-stub.h"
#include "atomisp-psys.h"
#include "psysstub.h"

#define ATOMISP_NUM_DEVICES	4

static dev_t atomisp_dev_t;
static DECLARE_BITMAP(atomisp_devices, ATOMISP_NUM_DEVICES);
static DEFINE_MUTEX(atomisp_devices_mutex);
static struct platform_device *atomisp_platform_device;

static struct bus_type atomisp_psys_bus = {
	.name = ATOMISP_PSYS_STUB_NAME,
};

static const struct atomisp_capability caps = {
	.version = 1,
	.driver = "atomisp-psys-stub",
};

static inline bool is_priority_valid(uint32_t priority)
{
	return priority < ATOMISP_CMD_PRIORITY_NUM;
}

static int atomisp_queue_event(struct atomisp_fh *fh, struct atomisp_event *e)
{
	struct atomisp_device *isp = device_to_atomisp_device(fh->dev);
	struct atomisp_eventq *eventq;
	struct atomisp_event *ev;

	eventq = kzalloc(sizeof(*eventq), GFP_KERNEL);
	if (!eventq)
		return -ENOMEM;
	ev = kzalloc(sizeof(*ev), GFP_KERNEL);
	if (!ev)
		goto out;
	*ev = *e;
	eventq->ev = ev;
	dev_dbg(fh->dev, "queue event %u (%p)\n", ev->type, ev);

	mutex_lock(&isp->mutex);
	list_add_tail(&eventq->list, &fh->eventq);
	mutex_unlock(&isp->mutex);

	wake_up_interruptible(&fh->wait);
	return 0;
out:
	kfree(eventq);
	return -ENOMEM;
}

/**
 * This should be moved to a separate file as this part will be
 * replaced by the actual PSYS hardware API.
 */
static int psysstub_validate_buffers(struct atomisp_command *command)
{
	struct atomisp_buffer *buffer;
	struct psysparam *params;
	int err = 0;

	if (command->bufcount < ATOMISP_PSYS_STUB_BUFS_MIN)
		return -EINVAL;

	buffer = kzalloc(sizeof(*buffer) * command->bufcount, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	if (copy_from_user(buffer, command->buffers,
				sizeof(*buffer) * command->bufcount)) {
		kfree(buffer);
		return -EFAULT;
	}

	/* get params */
	params = kzalloc(sizeof(*params), GFP_KERNEL);
	if (!params) {
		kfree(buffer);
		return -ENOMEM;
	}

	if (copy_from_user(params, buffer[ATOMISP_PSYS_STUB_PARAMS_IDX].userptr,
				sizeof(*params))) {
		err = -EFAULT;
		goto out;
	}

	if (buffer[ATOMISP_PSYS_STUB_VIDEO_INPUT_IDX].len <
	    params->input.bytesperline * params->input.height) {
		err = -EINVAL;
		goto out;
	}

	if (buffer[ATOMISP_PSYS_STUB_VIDEO_OUTPUT_IDX].len <
	    params->output.bytesperline * params->output.height) {
		err = -EINVAL;
		goto out;
	}

out:
	kfree(params);
	kfree(buffer);
	return err;
}

static int psysstub_runisp(struct atomisp_run_cmd *cmd)
{
	struct atomisp_event ev;
	int err = 0;

	if (!cmd)
		return -EINVAL;

	switch(cmd->command.id) {
	case ATOMISP_PSYS_STUB_PREVIEW:
		msleep(30);
		break;
	case ATOMISP_PSYS_STUB_VIDEO:
		usleep_range(14800, 15000);
		break;
	case ATOMISP_PSYS_STUB_CAPTURE:
		msleep(500);
		break;
	default:
		err = -EINVAL;
	}

	ev.type = ATOMISP_EVENT_TYPE_CMD_COMPLETE;
	ev.ev.cmd_done.id = cmd->command.id;
	atomisp_queue_event(cmd->fh, &ev);

	return err;
}

static struct atomisp_run_cmd *psysstub_get_next_cmd(struct atomisp_device *isp)
{
	struct atomisp_run_cmd *cmd = NULL;
	int i;

	mutex_lock(&isp->mutex);
	/* start from highest piority */
	for(i = 0; i < ATOMISP_CMD_PRIORITY_NUM; i++) {
		if (list_empty(&isp->commands[i]))
			continue;
		cmd = list_first_entry(&isp->commands[i],
				struct atomisp_run_cmd, list);
		list_del(&cmd->list);
		break;
	}
	if (!cmd)
		isp->queue_empty = true;
	mutex_unlock(&isp->mutex);
	return cmd;
}

static void psysstub_run_cmd(struct work_struct *work)
{
	struct atomisp_device *isp = container_of(work, struct atomisp_device, run_cmd);
	struct atomisp_run_cmd *cmd;

	while ((cmd = psysstub_get_next_cmd(isp)) != NULL) {
		psysstub_runisp(cmd);

		kfree(cmd);
	}
}

static int atomisp_open(struct inode *inode, struct file *file)
{
	struct atomisp_device *isp = inode_to_atomisp_device(inode);
	struct atomisp_fh *fh;

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	init_waitqueue_head(&fh->wait);
	INIT_LIST_HEAD(&fh->bufmap);
	INIT_LIST_HEAD(&fh->eventq);

	fh->dev = &isp->dev;
	file->private_data = fh;

	mutex_lock(&isp->mutex);

	list_add(&fh->list, &isp->fhs);

	mutex_unlock(&isp->mutex);

	return 0;
}

static struct atomisp_kbuffer *atomisp_lookup_kbuffer(struct atomisp_fh *fh, int fd)
{
	struct atomisp_kbuffer *kbuffer = NULL;

	list_for_each_entry(kbuffer, &fh->bufmap, list) {
		if (kbuffer->fd == fd)
			return kbuffer;
	}

	return 0;
}

static long atomisp_ioctl_mapbuf(struct file *file, struct atomisp_buffer __user *arg)
{
	struct atomisp_fh *fh = file->private_data;
	struct atomisp_kbuffer *kbuffer;
	struct atomisp_buffer buf;

	if (copy_from_user(&buf, arg, sizeof buf))
		return -EFAULT;
	kbuffer = atomisp_lookup_kbuffer(fh, buf.fd);
	if (!kbuffer)
		return -EINVAL;
	if (kbuffer->mapped)
		return -EINVAL;
	buf.flags |= ATOMISP_BUFFER_FLAG_MAPPED;
	if (copy_to_user(arg, &buf, sizeof buf)) {
		kfree(kbuffer);
		return -EFAULT;
	}
	kbuffer->mapped = 1;
	dev_dbg(fh->dev, "IOC_MAPBUF: mapped fd %d\n", kbuffer->fd);

	return 0;
}

static long atomisp_ioctl_unmapbuf(struct file *file, struct atomisp_buffer __user *arg)
{
	struct atomisp_fh *fh = file->private_data;
	struct atomisp_kbuffer *kbuffer;
	struct atomisp_buffer buf;

	if (copy_from_user(&buf, arg, sizeof buf))
		return -EFAULT;
	kbuffer = atomisp_lookup_kbuffer(fh, buf.fd);
	if (!kbuffer)
		return -EINVAL;
	if (!kbuffer->mapped)
		return -EINVAL;
	buf.flags &= ~ATOMISP_BUFFER_FLAG_MAPPED;
	if (copy_to_user(arg, &buf, sizeof buf)) {
		kfree(kbuffer);
		return -EFAULT;
	}
	kbuffer->mapped = 0;
	dev_dbg(fh->dev, "IOC_UNMAPBUF: fd %d\n", kbuffer->fd);

	return 0;
}

static long atomisp_ioctl_getbuf(struct file *file, struct atomisp_buffer __user *arg)
{
	struct atomisp_fh *fh = file->private_data;
	struct atomisp_kbuffer *kbuffer;
	struct atomisp_buffer buffer;

	if (copy_from_user(&buffer, arg, sizeof buffer))
		return -EFAULT;
	kbuffer = kzalloc(sizeof(*kbuffer), GFP_KERNEL);
	if (!kbuffer)
		return -ENOMEM;
	/* TODO: allocate with DMABUF */
	kbuffer->fd = (int)kbuffer;
	kbuffer->userptr = buffer.userptr;
	buffer.fd = kbuffer->fd;
	if (copy_to_user(arg, &buffer, sizeof buffer)) {
		kfree(kbuffer);
		return -EFAULT;
	}
	list_add_tail(&kbuffer->list, &fh->bufmap);
	dev_dbg(fh->dev, "IOC_GETBUF: userptr %p to %d\n", buffer.userptr, buffer.fd);
	return 0;
}

static long atomisp_ioctl_putbuf(struct file *file, struct atomisp_buffer __user *arg)
{
	struct atomisp_fh *fh = file->private_data;
	struct atomisp_kbuffer *kbuffer = NULL;
	struct atomisp_buffer buffer;

	if (copy_from_user(&buffer, arg, sizeof buffer))
		return -EFAULT;
	kbuffer = atomisp_lookup_kbuffer(fh, buffer.fd);
	if (!kbuffer)
		return -EINVAL;
	list_del(&kbuffer->list);
	kfree(kbuffer);
	dev_dbg(fh->dev, "IOC_PUTBUF: buffer %d\n", buffer.fd);

	return 0;
}

static long atomisp_ioctl_qcmd(struct file *file, struct atomisp_command __user *arg)
{
	struct atomisp_fh *fh = file->private_data;
	struct atomisp_device *isp = device_to_atomisp_device(fh->dev);
	struct atomisp_run_cmd *cmd;
	int err;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	if (copy_from_user(&cmd->command, arg, sizeof (cmd->command))) {
		err = -EFAULT;
		goto error;
	}

	dev_dbg(fh->dev, "IOC_QCMD: length %u\n", cmd->command.bufcount);

	if (!is_priority_valid(cmd->command.priority) ||
	    psysstub_validate_buffers(&cmd->command)) {
		err = -EINVAL;
		goto error;
	}
	cmd->fh = fh;

	list_add_tail(&cmd->list, &isp->commands[cmd->command.priority]);
	if (isp->queue_empty) {
		queue_work(isp->run_cmd_queue, &isp->run_cmd);
		isp->queue_empty = false;
	}

	return 0;

error:
	kfree(cmd);
	return err;
}

static long atomisp_ioctl_dqevent(struct file *file, struct atomisp_event __user *arg)
{
	struct atomisp_fh *fh = file->private_data;
	struct atomisp_eventq *evq;
	struct atomisp_event *ev;

	dev_dbg(fh->dev, "IOC_DQEVENT\n");

	/* TODO: eventq accesses must be serialized */
	/* TODO: should be able to block on this */

	if (list_empty(&fh->eventq))
		return -EINVAL;

	evq = list_first_entry(&fh->eventq, struct atomisp_eventq, list);
	ev = evq->ev;

	if (copy_to_user(arg, ev, sizeof *ev))
		return -EFAULT;

	list_del(&evq->list);
	kfree(evq);
	kfree(ev);

	return 0;
}

static long atomisp_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int err = 0;
	struct atomisp_fh *fh = file->private_data;
	struct atomisp_device *isp = device_to_atomisp_device(fh->dev);
	void __user *argp = (void __user*)arg;

	mutex_lock(&isp->mutex);
	switch (cmd) {
	case ATOMISP_IOC_QUERYCAP:
		err = copy_to_user(argp, &caps, sizeof caps);
		break;
	case ATOMISP_IOC_MAPBUF:
		err = atomisp_ioctl_mapbuf(file, argp);
		break;
	case ATOMISP_IOC_UNMAPBUF:
		err = atomisp_ioctl_unmapbuf(file, argp);
		break;
	case ATOMISP_IOC_GETBUF:
		err = atomisp_ioctl_getbuf(file, argp);
		break;
	case ATOMISP_IOC_PUTBUF:
		err = atomisp_ioctl_putbuf(file, argp);
		break;
	case ATOMISP_IOC_QCMD:
		err = atomisp_ioctl_qcmd(file, argp);
		break;
	case ATOMISP_IOC_DQEVENT:
		err = atomisp_ioctl_dqevent(file, argp);
		break;
	default:
		err = -ENOTTY;
	}
	mutex_unlock(&isp->mutex);
	return err;
}

static unsigned int atomisp_poll(struct file *file, struct poll_table_struct *wait)
{
	struct atomisp_fh *fh = file->private_data;
	struct atomisp_device *isp = device_to_atomisp_device(fh->dev);
	unsigned int res = 0;

	dev_dbg(fh->dev, "atomisp poll\n");

	poll_wait(file, &fh->wait, wait);

	mutex_lock(&isp->mutex);
	if (!list_empty(&fh->eventq))
		res = POLLIN;
	mutex_unlock(&isp->mutex);

	dev_dbg(fh->dev, "atomisp poll res %u\n", res);

	return res;
}


static int atomisp_release(struct inode *inode, struct file *file)
{
	struct atomisp_device *isp = inode_to_atomisp_device(inode);
	struct atomisp_fh *fh = file->private_data;
	struct atomisp_kbuffer *bm, *bm0;
	struct atomisp_run_cmd *cmd, *cmd0;
	int i;

	cancel_work_sync(&isp->run_cmd);

	mutex_lock(&isp->mutex);
	list_del(&fh->list);

	for (i = 0; i < ATOMISP_CMD_PRIORITY_NUM; i++)
		list_for_each_entry_safe(cmd, cmd0, &isp->commands[i], list) {
			list_del(&cmd->list);
			kfree(cmd);
		}

	list_for_each_entry_safe(bm, bm0, &fh->bufmap, list) {
		list_del(&bm->list);
		kfree(bm);
	}
	mutex_unlock(&isp->mutex);
	kfree(fh);

	return 0;
}

static const struct file_operations atomisp_fops = {
	.open = atomisp_open,
	.release = atomisp_release,
	.unlocked_ioctl = atomisp_ioctl,
	.poll = atomisp_poll,
	.owner = THIS_MODULE,
};

void atomisp_dev_release(struct device *dev)
{
}

static int atomisp_platform_probe(struct platform_device *pdev)
{
	struct atomisp_device *isp;
	unsigned int minor;
	int i;
	int rval = -E2BIG;

	mutex_lock(&atomisp_devices_mutex);

	minor = find_next_zero_bit(atomisp_devices, ATOMISP_NUM_DEVICES, 0);
	if (minor == ATOMISP_NUM_DEVICES) {
		dev_err(&pdev->dev, "too many devices\n");
		goto out_unlock;
	}

	isp = devm_kzalloc(&pdev->dev, sizeof(*isp), GFP_KERNEL);
	if (!isp) {
		dev_err(&pdev->dev, "Failed to alloc CI ISP structure\n");
		rval = -ENOMEM;
		goto out_unlock;
	}

	cdev_init(&isp->cdev, &atomisp_fops);
	isp->cdev.owner = atomisp_fops.owner;

	rval = cdev_add(&isp->cdev, MKDEV(MAJOR(atomisp_dev_t), minor), 1);
	if (rval) {
		dev_err(&pdev->dev, "cdev_add failed (%d)\n", rval);
		goto out_unlock;
	}

	set_bit(minor, atomisp_devices);

	isp->dev.bus = &atomisp_psys_bus;
	isp->dev.devt = MKDEV(MAJOR(atomisp_dev_t), minor);
	isp->dev.release = atomisp_dev_release;
	dev_set_name(&isp->dev, ATOMISP_PSYS_STUB_NAME "%d", minor);
	rval = device_register(&isp->dev);
	if (rval < 0) {
		dev_err(&isp->dev, "device_register failed\n");
		goto out_unlock;
	}

	platform_set_drvdata(pdev, isp);

	isp->run_cmd_queue = alloc_workqueue(caps.driver, WQ_UNBOUND, 1);
	if (isp->run_cmd_queue == NULL) {
		dev_err(&isp->dev, "Failed to initialize workq\n");
		rval = -ENOMEM;
		goto out_unlock;
	}
	INIT_WORK(&isp->run_cmd, psysstub_run_cmd);
	isp->queue_empty = true;

	for (i = 0; i < ATOMISP_CMD_PRIORITY_NUM; i++)
		INIT_LIST_HEAD(&isp->commands[i]);

	mutex_unlock(&atomisp_devices_mutex);
	mutex_init(&isp->mutex);
	INIT_LIST_HEAD(&isp->fhs);

	return 0;

out_unlock:
	mutex_unlock(&atomisp_devices_mutex);

	return rval;
}

static int atomisp_platform_remove(struct platform_device *pdev)
{
	struct atomisp_device *isp = platform_get_drvdata(pdev);

	mutex_lock(&atomisp_devices_mutex);

	if (isp->run_cmd_queue) {
		destroy_workqueue(isp->run_cmd_queue);
		isp->run_cmd_queue = NULL;
	}

	device_unregister(&isp->dev);

	clear_bit(MINOR(isp->cdev.dev), atomisp_devices);
	cdev_del(&isp->cdev);

	mutex_unlock(&atomisp_devices_mutex);

	mutex_destroy(&isp->mutex);

	return 0;
}

static struct platform_device_id atomisp_psys_id_table[] = {
        { ATOMISP_PSYS_STUB_NAME, 0 },
        { },
};

static struct platform_driver atomisp_platform_driver = {
	.driver = {
#ifdef CONFIG_PM
		.pm = &(const struct dev_pm_ops){},
#endif /* CONFIG_PM */
		.name = ATOMISP_PSYS_STUB_NAME,
		.owner = THIS_MODULE,
	},
	.probe = atomisp_platform_probe,
	.remove = atomisp_platform_remove,
	.id_table = atomisp_psys_id_table,
};

static int __init atomisp_init(void)
{
	int rval = alloc_chrdev_region(&atomisp_dev_t, 0, ATOMISP_NUM_DEVICES,
				       ATOMISP_PSYS_STUB_NAME);

	if (rval) {
		pr_warn("can't allocate atomisp chrdev region (%d)\n", rval);
		return rval;
	}

	rval = bus_register(&atomisp_psys_bus);
	if (rval) {
		pr_warn("can't register atomisp bus (%d)\n", rval);
		goto out_bus_register;
	}

	atomisp_platform_device = platform_device_alloc(ATOMISP_PSYS_STUB_NAME, -1);
	if (!atomisp_platform_device) {
		pr_warn("can't allocate platform device\n");
		rval = -ENOMEM;
		goto out_bus_register;
	}

	rval = platform_device_add(atomisp_platform_device);
	if (rval) {
		pr_warn("can't add pci driver (%d)\n", rval);
		goto out_platform_device_register;
	}

	rval = platform_driver_register(&atomisp_platform_driver);
	if (rval) {
		pr_warn("can't register pci driver (%d)\n", rval);
		goto out_platform_driver_register;
	}

	return 0;

out_platform_driver_register:
	platform_device_unregister(atomisp_platform_device);

out_platform_device_register:
	bus_unregister(&atomisp_psys_bus);

out_bus_register:
	unregister_chrdev_region(atomisp_dev_t, ATOMISP_NUM_DEVICES);

	return rval;
}

static void __exit atomisp_exit(void)
{
	platform_driver_unregister(&atomisp_platform_driver);
	platform_device_unregister(atomisp_platform_device);
	atomisp_platform_device = NULL;
	bus_unregister(&atomisp_psys_bus);
	unregister_chrdev_region(atomisp_dev_t, ATOMISP_NUM_DEVICES);
}

module_init(atomisp_init);
module_exit(atomisp_exit);

MODULE_AUTHOR("Sakari Ailus <sakari.ailus@intel.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Intel Atom ISP driver");
