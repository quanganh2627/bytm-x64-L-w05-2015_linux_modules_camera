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

#ifndef CSS2600_ISYS_QUEUE_H
#define CSS2600_ISYS_QUEUE_H

#include <linux/list.h>
#include <linux/mutex.h>

#include <media/videobuf2-core.h>

struct css2600_isys;

struct css2600_isys_queue {
	struct vb2_queue vbq;
	struct vb2_alloc_ctx *ctx;
	struct mutex mutex;
	struct list_head queued;
};

struct css2600_isys_buffer {
	struct list_head head;
};

#define vb2_queue_to_css2600_isys_queue(__vb2) \
	container_of(__vb2, struct css2600_isys_queue, vbq)

#define to_css2600_isys_buffer(vb) \
	((struct css2600_isys_buffer *)((vb) + 1))

#define css2600_isys_buffer_to_vb2_buffer(ib) ((struct vb2_buffer *)(ib) - 1)

void css2600_isys_queue_lock(struct vb2_queue *q);
void css2600_isys_queue_unlock(struct vb2_queue *q);

int css2600_isys_queue_init(struct css2600_isys_queue *aq);
void css2600_isys_queue_cleanup(struct css2600_isys_queue *aq);

#endif /* CSS2600_ISYS_QUEUE_H */
