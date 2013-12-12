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
 */

#include <linux/device.h>
#include <linux/dma-attrs.h>
#include <linux/iommu.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/sizes.h>
#include <linux/string.h>

#include <media/videobuf2-core.h>
#include <media/videobuf2-dma-contig.h>
#include <media/v4l2-ioctl.h>

#include "atomisp.h"
#include "atomisp-bus.h"
#include "atomisp-csi2.h"
#include "atomisp-isys.h"

static int queue_setup(struct vb2_queue *q, const struct v4l2_format *fmt,
		       unsigned int *num_buffers, unsigned int *num_planes,
		       unsigned int sizes[], void *alloc_ctxs[])
{
	return 0;
}

void atomisp_isys_queue_lock(struct vb2_queue *q)
{
	struct atomisp_isys_queue *aq = vb2_get_drv_priv(q);

	mutex_lock(&aq->mutex);
}

void atomisp_isys_queue_unlock(struct vb2_queue *q)
{
	struct atomisp_isys_queue *aq = vb2_get_drv_priv(q);

	mutex_unlock(&aq->mutex);
}

static int buf_init(struct vb2_buffer *vb)
{
	return 0;
}

static int buf_prepare(struct vb2_buffer *vb)
{
	return 0;
}

static int buf_finish(struct vb2_buffer *vb)
{
	return 0;
}

static void buf_cleanup(struct vb2_buffer *vb)
{
}

static int start_streaming(struct vb2_queue *q, unsigned int count)
{
	return 0;
}

static int stop_streaming(struct vb2_queue *q)
{
	return 0;
}

static void buf_queue(struct vb2_buffer *vb)
{
}

struct vb2_ops atomisp_isys_queue_ops = {
	.queue_setup = queue_setup,
	.wait_prepare = atomisp_isys_queue_lock,
	.wait_finish = atomisp_isys_queue_unlock,
	.buf_init = buf_init,
	.buf_prepare = buf_prepare,
	.buf_finish = buf_finish,
	.buf_cleanup = buf_cleanup,
	.start_streaming = start_streaming,
	.stop_streaming = stop_streaming,
	.buf_queue = buf_queue,
};

int atomisp_isys_queue_init(struct atomisp_isys *isys,
			    struct atomisp_isys_queue *aq)
{
	int rval;

	aq->isys = isys;
	aq->vbq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	aq->vbq.lock = &aq->mutex;
	aq->vbq.io_modes = VB2_USERPTR | VB2_DMABUF;
	aq->vbq.drv_priv = aq;
	aq->vbq.buf_struct_size = sizeof(struct atomisp_isys_buffer);
	aq->vbq.ops = &atomisp_isys_queue_ops;
	aq->vbq.mem_ops = &vb2_dma_contig_memops;
	aq->vbq.timestamp_type = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;

	rval = vb2_queue_init(&aq->vbq);
	if (rval)
		return rval;

	aq->ctx = vb2_dma_contig_init_ctx(&isys->adev->dev);
	if (IS_ERR(aq->ctx)) {
		vb2_queue_release(&aq->vbq);
		return PTR_ERR(aq->ctx);
	}

	mutex_init(&aq->mutex);

	return 0;
}

void atomisp_isys_queue_cleanup(struct atomisp_isys_queue *aq)
{
	if (IS_ERR_OR_NULL(aq->ctx))
		return;

	vb2_dma_contig_cleanup_ctx(aq->ctx);
	vb2_queue_release(&aq->vbq);
	mutex_destroy(&aq->mutex);

	aq->ctx = NULL;
}
