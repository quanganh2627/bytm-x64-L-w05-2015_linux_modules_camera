/*
 * Support for Intel Camera Imaging ISP subsystem.
 *
 * Copyright (c) 2010 - 2014 Intel Corporation. All Rights Reserved.
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

#ifndef __IA_CSS_PIPE_H__
#define __IA_CSS_PIPE_H__

#include <type_support.h>
#include "ia_css_stream.h"
#include "ia_css_frame.h"
#include "ia_css_pipeline.h"
#include "ia_css_binary.h"
#include "sh_css_legacy.h"
#include "sh_css_internal.h"

struct ia_css_preview_settings {
	struct ia_css_binary copy_binary;
	struct ia_css_binary preview_binary;
	struct ia_css_binary vf_pp_binary;
	struct ia_css_pipe *copy_pipe;
	struct ia_css_pipe *capture_pipe;
};

#define IA_CSS_DEFAULT_PREVIEW_SETTINGS \
{ \
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* copy_binary */\
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* preview_binary */\
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* vf_pp_binary */\
	NULL,				/* copy_pipe */\
	NULL,				/* capture_pipe */\
}

struct ia_css_capture_settings {
	struct ia_css_binary copy_binary;
	struct ia_css_binary primary_binary;
	struct ia_css_binary pre_isp_binary;
	struct ia_css_binary anr_gdc_binary;
	struct ia_css_binary post_isp_binary;
	struct ia_css_binary capture_pp_binary;
	struct ia_css_binary vf_pp_binary;
};

#define IA_CSS_DEFAULT_CAPTURE_SETTINGS \
{ \
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* copy_binary */\
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* primary_binary */\
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* pre_isp_binary */\
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* anr_gdc_binary */\
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* post_isp_binary */\
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* capture_pp_binary */\
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* vf_pp_binary */\
}

struct ia_css_video_settings {
	struct ia_css_binary copy_binary;
	struct ia_css_binary video_binary;
	struct ia_css_binary vf_pp_binary;
	struct ia_css_frame *delay_frames[NUM_VIDEO_DELAY_FRAMES];
	struct ia_css_frame *tnr_frames[NUM_VIDEO_TNR_FRAMES];
	struct ia_css_frame *vf_pp_in_frame;
	struct ia_css_pipe *copy_pipe;
	struct ia_css_pipe *capture_pipe;
};

#define IA_CSS_DEFAULT_VIDEO_SETTINGS \
{ \
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* copy_binary */ \
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* video_binary */ \
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* vf_pp_binary */ \
	{ NULL },			/* delay_frames */ \
	{ NULL },			/* tnr_frames */ \
	NULL,				/* vf_pp_in_frame */ \
	NULL,				/* copy_pipe */ \
	NULL,				/* capture_pipe */ \
}

struct ia_css_yuvpp_settings {
	struct ia_css_binary copy_binary;
	struct ia_css_binary *yuv_scaler_binary;
	struct ia_css_binary *vf_pp_binary;
	bool *is_output_stage;
	unsigned int num_yuv_scaler;
	unsigned int num_vf_pp;
	unsigned int num_output;
};

#define IA_CSS_DEFAULT_YUVPP_SETTINGS \
{ \
	IA_CSS_BINARY_DEFAULT_SETTINGS,	/* copy_binary */ \
	NULL,							/* yuv_scaler_binary */ \
	NULL,							/* vf_pp_binary */ \
	NULL,							/* is_output_stage */ \
	0,								/* num_yuv_scaler */ \
	0,								/* num_vf_pp */ \
	0,								/* num_output */ \
}

struct ia_css_pipe {
	/* TODO: Remove stop_requested and use stop_requested in the pipeline */
	bool                            stop_requested;
	struct ia_css_pipe_config       config;
	struct ia_css_pipe_extra_config extra_config;
	struct ia_css_pipe_info         info;
	enum ia_css_pipe_id		mode;
	struct ia_css_shading_table	*shading_table;
	struct ia_css_pipeline		pipeline;
	struct ia_css_frame_info	output_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	struct ia_css_frame_info	bds_output_info;
	struct ia_css_frame_info	vf_output_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	struct ia_css_frame_info	out_yuv_ds_input_info;
	struct ia_css_frame_info	vf_yuv_ds_input_info;
	struct ia_css_fw_info		*output_stage;	/* extra output stage */
	struct ia_css_fw_info		*vf_stage;	/* extra vf_stage */
	unsigned int				required_bds_factor;
	enum ia_css_frame_delay		dvs_frame_delay;
	int				num_invalid_frames;
	bool				enable_viewfinder;
	bool				enable_second_viewfinder;
	struct ia_css_stream		*stream;
	struct ia_css_frame		in_frame_struct;
	struct ia_css_frame		out_frame_struct;
	struct ia_css_frame		vf_frame_struct;
	struct ia_css_frame		*continuous_frames[NUM_CONTINUOUS_FRAMES];
	struct ia_css_metadata	*cont_md_buffers[NUM_CONTINUOUS_FRAMES];
	union {
		struct ia_css_preview_settings preview;
		struct ia_css_video_settings   video;
		struct ia_css_capture_settings capture;
		struct ia_css_yuvpp_settings yuvpp;
	} pipe_settings;

	/* This number is unique per pipe each instance of css. This number is
	 * reused as pipeline number also. There is a 1-1 mapping between pipe_num
	 * and sp thread id. Current logic limits pipe_num to
	 * SH_CSS_MAX_SP_THREADS */
	unsigned int pipe_num;
};

#define IA_CSS_DEFAULT_PIPE \
{ \
	false,					/* stop_requested */ \
	DEFAULT_PIPE_CONFIG,			/* config */ \
	DEFAULT_PIPE_EXTRA_CONFIG,		/* extra_config */ \
	DEFAULT_PIPE_INFO,			/* info */ \
	IA_CSS_PIPE_ID_ACC,			/* mode (pipe_id) */ \
	NULL,					/* shading_table */ \
	DEFAULT_PIPELINE,			/* pipeline */ \
	{IA_CSS_BINARY_DEFAULT_FRAME_INFO},	/* output_info */ \
	IA_CSS_BINARY_DEFAULT_FRAME_INFO,	/* bds_output_info */ \
	{IA_CSS_BINARY_DEFAULT_FRAME_INFO},	/* vf_output_info */ \
	IA_CSS_BINARY_DEFAULT_FRAME_INFO,	/* out_yuv_ds_input_info */ \
	IA_CSS_BINARY_DEFAULT_FRAME_INFO,	/* vf_yuv_ds_input_info */ \
	NULL,					/* output_stage */ \
	NULL,					/* vf_stage */ \
	SH_CSS_BDS_FACTOR_1_00,			/* required_bds_factor */ \
	IA_CSS_FRAME_DELAY_1,			/* dvs_frame_delay */ \
	0,					/* num_invalid_frames */ \
	true,					/* enable_viewfinder */ \
	true,					/* enable_second_viewfinder */ \
	NULL,					/* stream */ \
	DEFAULT_FRAME,				/* in_frame_struct */ \
	DEFAULT_FRAME,				/* out_frame_struct */ \
	DEFAULT_FRAME,				/* vf_frame_struct */ \
	{ NULL },				/* continuous_frames */ \
	{ NULL },				/* cont_md_buffers */ \
	{ IA_CSS_DEFAULT_PREVIEW_SETTINGS },		/* pipe_settings */ \
	PIPE_ENTRY_EMPTY_TOKEN,				/* pipe_num */\
}

void ia_css_pipe_map_queue(struct ia_css_pipe *pipe, bool map);

#endif /* __IA_CSS_PIPE_H__ */
