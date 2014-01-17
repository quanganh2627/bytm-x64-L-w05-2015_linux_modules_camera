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

#include <media/media-entity.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>

#include "atomisp-isys.h"
#include "atomisp-isys-video.h"

const struct atomisp_isys_pixelformat *atomisp_isys_get_pixelformat(
	struct atomisp_isys_video *av, uint32_t pixelformat)
{
	const struct atomisp_isys_pixelformat *pfmt, *found = av->pfmts;

	for (pfmt = av->pfmts; pfmt->bpp; pfmt++) {
		if (pfmt->pixelformat == pixelformat) {
			found = pfmt;
			break;
		}
	}

	return found;
}

static int vidioc_querycap(struct file *file, void *fh,
			   struct v4l2_capability *cap)
{
	return 0;
}

static int vidioc_enum_fmt_vid_cap(struct file *file, void *fh,
				   struct v4l2_fmtdesc *fmtdesc)
{
	return 0;
}

static int vidioc_g_fmt_vid_cap(struct file *file, void *fh,
				struct v4l2_format *fmt)
{
	struct atomisp_isys_video *av = video_drvdata(file);

	fmt->fmt.pix = av->pix;

	return 0;
}

static const struct atomisp_isys_pixelformat *__vidioc_try_fmt_vid_cap(
	struct atomisp_isys_video *av, struct v4l2_pix_format *pix)
{
	const struct atomisp_isys_pixelformat *pfmt =
		atomisp_isys_get_pixelformat(av, pix->pixelformat);

	pix->pixelformat = pfmt->pixelformat;
	pix->bytesperline = max(
		pix->bytesperline, pix->width * DIV_ROUND_UP(pfmt->bpp, 8));
	pix->sizeimage = pix->bytesperline * pix->height;

	return pfmt;
}

static int vidioc_s_fmt_vid_cap(struct file *file, void *fh,
				struct v4l2_format *fmt)
{
	struct atomisp_isys_video *av = video_drvdata(file);

	av->pfmt = __vidioc_try_fmt_vid_cap(av, &fmt->fmt.pix);
	av->pix = fmt->fmt.pix;

	return 0;
}

static int vidioc_try_fmt_vid_cap(struct file *file, void *fh,
				  struct v4l2_format *fmt)
{
	struct atomisp_isys_video *av = video_drvdata(file);

	__vidioc_try_fmt_vid_cap(av, &fmt->fmt.pix);

	return 0;
}

static const struct v4l2_ioctl_ops ioctl_ops = {
	.vidioc_querycap = vidioc_querycap,
	.vidioc_enum_fmt_vid_cap = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = vidioc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = vidioc_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = vidioc_try_fmt_vid_cap,
	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
};

int atomisp_isys_video_init(struct atomisp_isys_video *av,
			    struct atomisp_isys *isys)
{
	int rval;

	av->isys = isys;
	av->pfmt = __vidioc_try_fmt_vid_cap(av, &av->pix);

	rval = atomisp_isys_queue_init(&av->aq);
	if (rval)
		return rval;

	av->pad.flags = MEDIA_PAD_FL_SINK;
	rval = media_entity_init(&av->vdev.entity, 1, &av->pad, 0);
	if (rval)
		goto out_atomisp_isys_queue_cleanup;

	av->vdev.release = video_device_release_empty;
	av->vdev.fops = &atomisp_isys_fops;
	av->vdev.v4l2_dev = &isys->v4l2_dev;
	av->vdev.ioctl_ops = &ioctl_ops;
	video_set_drvdata(&av->vdev, av);

	rval = video_register_device(&av->vdev, VFL_TYPE_GRABBER, -1);
	if (rval)
		goto out_media_entity_cleanup;

	return rval;

out_media_entity_cleanup:
	media_entity_cleanup(&av->vdev.entity);

out_atomisp_isys_queue_cleanup:
	atomisp_isys_queue_cleanup(&av->aq);

	return rval;
}

void atomisp_isys_video_cleanup(struct atomisp_isys_video *av)
{
	video_unregister_device(&av->vdev);
	media_entity_cleanup(&av->vdev.entity);
}
