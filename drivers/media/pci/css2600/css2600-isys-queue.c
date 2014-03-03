/*
 * Copyright (c) 2013--2014 Intel Corporation. All Rights Reserved.
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

#include <linux/completion.h>
#include <linux/device.h>
#include <linux/dma-attrs.h>
#include <linux/iommu.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/sizes.h>
#include <linux/string.h>

#include <media/media-entity.h>
#include <media/videobuf2-core.h>
#include <media/videobuf2-dma-contig.h>
#include <media/v4l2-ioctl.h>

#include "css2600.h"
#include "css2600-bus.h"
#include "css2600-isys.h"
#include "css2600-isys-csi2.h"
#include "css2600-isys-video.h"

static int queue_setup(struct vb2_queue *q, const struct v4l2_format *fmt,
		       unsigned int *num_buffers, unsigned int *num_planes,
		       unsigned int sizes[], void *alloc_ctxs[])
{
	struct css2600_isys_queue *aq = vb2_queue_to_css2600_isys_queue(q);
	struct css2600_isys_video *av = css2600_isys_queue_to_video(aq);
	const struct css2600_isys_pixelformat *pfmt;
	const struct v4l2_pix_format *pix;

	if (fmt)
		pix = &fmt->fmt.pix;
	else
		pix = &av->pix;

	pfmt = css2600_isys_get_pixelformat(av, pix->pixelformat);

	*num_planes = 1;

	sizes[0] = pfmt->bpp * pix->width * pix->height / 8;
	alloc_ctxs[0] = aq->ctx;

	dev_dbg(&av->isys->adev->dev, "queue setup: buffer size %d\n",
		sizes[0]);

	return 0;
}

void css2600_isys_queue_lock(struct vb2_queue *q)
{
	struct css2600_isys_queue *aq = vb2_queue_to_css2600_isys_queue(q);
	struct css2600_isys_video *av = css2600_isys_queue_to_video(aq);

	dev_dbg(&av->isys->adev->dev, "queue lock\n");
	mutex_lock(&aq->mutex);
}

void css2600_isys_queue_unlock(struct vb2_queue *q)
{
	struct css2600_isys_queue *aq = vb2_queue_to_css2600_isys_queue(q);
	struct css2600_isys_video *av = css2600_isys_queue_to_video(aq);

	dev_dbg(&av->isys->adev->dev, "queue unlock\n");
	mutex_unlock(&aq->mutex);
}

static int buf_init(struct vb2_buffer *vb)
{
	struct css2600_isys_queue *aq =
		vb2_queue_to_css2600_isys_queue(vb->vb2_queue);
	struct css2600_isys_video *av = css2600_isys_queue_to_video(aq);

	dev_dbg(&av->isys->adev->dev, "buf_init\n");
	return 0;
}

static int buf_prepare(struct vb2_buffer *vb)
{
	struct css2600_isys_queue *aq =
		vb2_queue_to_css2600_isys_queue(vb->vb2_queue);
	struct css2600_isys_video *av = css2600_isys_queue_to_video(aq);

	dev_dbg(&av->isys->adev->dev, "configured size %u, buffer size %lu\n",
		av->pix.sizeimage, vb2_plane_size(vb, 0));

	if (av->pix.sizeimage > vb2_plane_size(vb, 0))
		return -EINVAL;

	vb2_set_plane_payload(vb, 0, av->pix.sizeimage);

	return 0;
}

static int buf_finish(struct vb2_buffer *vb)
{
	struct css2600_isys_queue *aq =
		vb2_queue_to_css2600_isys_queue(vb->vb2_queue);
	struct css2600_isys_video *av = css2600_isys_queue_to_video(aq);
	struct css2600_isys_buffer *ib = to_css2600_isys_buffer(vb);

	dev_dbg(&av->isys->adev->dev, "buf_finish %u\n", vb->v4l2_buf.index);
	mutex_lock(&aq->mutex);
	list_del(&ib->head);
	mutex_unlock(&aq->mutex);
	return 0;
}

static void buf_cleanup(struct vb2_buffer *vb)
{
	struct css2600_isys_queue *aq =
		vb2_queue_to_css2600_isys_queue(vb->vb2_queue);
	struct css2600_isys_video *av = css2600_isys_queue_to_video(aq);

	dev_dbg(&av->isys->adev->dev, "buf_cleanup\n");
}

static int start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct css2600_isys_queue *aq = vb2_queue_to_css2600_isys_queue(q);
	struct css2600_isys_video *av = css2600_isys_queue_to_video(aq);
	unsigned long flags;
	int rval;

	rval = css2600_isys_video_set_streaming(av, 1);
	if (rval)
		return rval;

	spin_lock_irqsave(&av->isys->lock, flags);
	av->isys->pipes[av->ip.source] = &av->ip;
	spin_unlock_irqrestore(&av->isys->lock, flags);

	reinit_completion(&av->ip.stream_start_completion);
	rval = -ia_css_isys_stream_start(av->isys->ssi, av->ip.source,
					 NULL);
	if (rval < 0) {
		dev_dbg(&av->isys->adev->dev, "can't start streaning (%d)\n",
			rval);
		goto out_fail;
	}

	wait_for_completion(&av->ip.stream_start_completion);
	dev_dbg(&av->isys->adev->dev, "stream start complete\n");

	return 0;

out_fail:
	css2600_isys_video_set_streaming(av, 0);
	spin_lock_irqsave(&av->isys->lock, flags);
	av->isys->pipes[av->ip.source] = NULL;
	spin_unlock_irqrestore(&av->isys->lock, flags);

	return rval;
}

static int stop_streaming(struct vb2_queue *q)
{
	struct css2600_isys_queue *aq = vb2_queue_to_css2600_isys_queue(q);
	struct css2600_isys_video *av = css2600_isys_queue_to_video(aq);
	struct css2600_isys_buffer *ib, *safe;
	unsigned long flags;
	int rval;

	css2600_isys_video_set_streaming(av, 0);

	mutex_lock(&aq->mutex);
	list_for_each_entry_safe(ib, safe, &aq->queued, head) {
		struct vb2_buffer *vb = css2600_isys_buffer_to_vb2_buffer(ib);

		vb2_buffer_done(vb, VB2_BUF_STATE_ERROR);
		list_del(&ib->head);
		dev_dbg(&av->isys->adev->dev, "stop_streaming %u\n",
			vb->v4l2_buf.index);
	}
	reinit_completion(&av->ip.stream_stop_completion);
	rval = -ia_css_isys_stream_stop(av->isys->ssi, av->ip.source);
	mutex_unlock(&aq->mutex);

	if (rval < 0) {
		dev_err(&av->isys->adev->dev,
			"ia_css_isys_stream_stop failed (%d)\n", rval);
		goto out;
	}

	wait_for_completion(&av->ip.stream_stop_completion);
	dev_dbg(&av->isys->adev->dev, "stream stop complete\n");

out:
	spin_lock_irqsave(&av->isys->lock, flags);
	av->isys->pipes[av->ip.source] = NULL;
	spin_unlock_irqrestore(&av->isys->lock, flags);

	return 0;
}

static void buf_queue(struct vb2_buffer *vb)
{
	struct css2600_isys_queue *aq =
		vb2_queue_to_css2600_isys_queue(vb->vb2_queue);
	struct css2600_isys_video *av = css2600_isys_queue_to_video(aq);
	struct css2600_isys_buffer *ib = to_css2600_isys_buffer(vb);
	struct ia_css_isys_frame_buff_set buf = {
		.output_pins = {
			{
				.payload.addr =
					*(dma_addr_t *)vb2_plane_cookie(vb, 0),
			}
		},
		.send_irq_sof = 1,
		.send_irq_eof = 1,
	};
	int rval;

	dev_dbg(&av->isys->adev->dev, "buf_queue %d\n", vb->v4l2_buf.index);

	rval = -ia_css_isys_stream_capture_indication(av->isys->ssi,
						      av->ip.source, &buf);
	if (rval < 0) {
		dev_dbg(&av->isys->adev->dev,
			"capture indication failed (%d)\n", rval);
		return;
	}

	list_add(&ib->head, &aq->queued);
}

struct vb2_ops css2600_isys_queue_ops = {
	.queue_setup = queue_setup,
	.wait_prepare = css2600_isys_queue_unlock,
	.wait_finish = css2600_isys_queue_lock,
	.buf_init = buf_init,
	.buf_prepare = buf_prepare,
	.buf_finish = buf_finish,
	.buf_cleanup = buf_cleanup,
	.start_streaming = start_streaming,
	.stop_streaming = stop_streaming,
	.buf_queue = buf_queue,
};

int css2600_isys_queue_init(struct css2600_isys_queue *aq)
{
	struct css2600_isys *isys = css2600_isys_queue_to_video(aq)->isys;
	int rval;

	aq->vbq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	aq->vbq.lock = &aq->mutex;
	aq->vbq.io_modes = VB2_USERPTR;
	aq->vbq.drv_priv = aq;
	aq->vbq.buf_struct_size = sizeof(struct css2600_isys_buffer)
		+ sizeof(struct vb2_buffer);
	aq->vbq.ops = &css2600_isys_queue_ops;
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
	INIT_LIST_HEAD(&aq->queued);

	return 0;
}

void css2600_isys_queue_cleanup(struct css2600_isys_queue *aq)
{
	if (IS_ERR_OR_NULL(aq->ctx))
		return;

	vb2_dma_contig_cleanup_ctx(aq->ctx);
	vb2_queue_release(&aq->vbq);
	mutex_destroy(&aq->mutex);

	aq->ctx = NULL;
}
