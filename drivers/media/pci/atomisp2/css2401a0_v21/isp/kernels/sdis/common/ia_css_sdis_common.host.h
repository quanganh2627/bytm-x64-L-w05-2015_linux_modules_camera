/*
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2010 - 2013 Intel Corporation.
 * All Rights Reserved.
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Intel Corporation
 * or licensors. Title to the Material remains with Intel
 * Corporation or its licensors. The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * licensors. The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material may
 * be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No License under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or
 * delivery of the Materials, either expressly, by implication, inducement,
 * estoppel or otherwise. Any license under such intellectual property rights
 * must be express and approved by Intel in writing.
 */

#ifndef _IA_CSS_SDIS_COMMON_HOST_H
#define _IA_CSS_SDIS_COMMON_HOST_H

#define ISP_MAX_SDIS_HOR_PROJ_NUM_ISP \
	__ISP_SDIS_HOR_PROJ_NUM_ISP(ISP_MAX_INTERNAL_WIDTH, ISP_MAX_INTERNAL_HEIGHT, \
		SH_CSS_DIS_DECI_FACTOR_LOG2, ISP_PIPE_VERSION)
#define ISP_MAX_SDIS_VER_PROJ_NUM_ISP \
	__ISP_SDIS_VER_PROJ_NUM_ISP(ISP_MAX_INTERNAL_WIDTH, ISP_MAX_INTERNAL_HEIGHT, \
		SH_CSS_DIS_DECI_FACTOR_LOG2, ISP_PIPE_VERSION)

#define ISP_MAX_SDIS_HOR_COEF_NUM_VECS \
	__ISP_SDIS_HOR_COEF_NUM_VECS(ISP_MAX_INTERNAL_WIDTH)
#define ISP_MAX_SDIS_VER_COEF_NUM_VECS \
	__ISP_SDIS_VER_COEF_NUM_VECS(ISP_MAX_INTERNAL_HEIGHT)

/* SDIS Coefficients: */
/* The ISP uses vectors to store the coefficients, so we round
   the number of coefficients up to vectors. */
#define __ISP_SDIS_HOR_COEF_NUM_VECS(in_width)  _ISP_VECS(_ISP_BQS(in_width))
#define __ISP_SDIS_VER_COEF_NUM_VECS(in_height) _ISP_VECS(_ISP_BQS(in_height))

/* SDIS Projections:
 * SDIS1: Horizontal projections are calculated for each line.
 * Vertical projections are calculated for each column.
 * SDIS2: Projections are calculated for each grid cell.
 * Grid cells that do not fall completely within the image are not
 * valid. The host needs to use the bigger one for the stride but
 * should only return the valid ones to the 3A. */
#define __ISP_SDIS_HOR_PROJ_NUM_ISP(in_width, in_height, deci_factor_log2, \
	isp_pipe_version) \
	((isp_pipe_version == 1) ? \
		CEIL_SHIFT(_ISP_BQS(in_height), deci_factor_log2) : \
		(CEIL_SHIFT(_ISP_BQS(in_width), deci_factor_log2) * \
		 CEIL_SHIFT(_ISP_BQS(in_height), deci_factor_log2)))

#define __ISP_SDIS_VER_PROJ_NUM_ISP(in_width, in_height, deci_factor_log2, \
	isp_pipe_version) \
	((isp_pipe_version == 1) ? \
		CEIL_SHIFT(_ISP_BQS(in_width), deci_factor_log2) : \
		(CEIL_SHIFT(_ISP_BQS(in_width), deci_factor_log2) * \
		 CEIL_SHIFT(_ISP_BQS(in_height), deci_factor_log2)))

#define SH_CSS_DIS_VER_NUM_COEF_TYPES(b) \
  (((b)->info->sp.pipeline.isp_pipe_version == 2) ? \
	IA_CSS_DVS2_NUM_COEF_TYPES : \
	IA_CSS_DVS_NUM_COEF_TYPES)

#ifndef PIPE_GENERATION
#if defined(__ISP) || defined (MK_FIRMWARE)

/* Array cannot be 2-dimensional, since driver ddr allocation does not know stride */
struct sh_css_isp_sdis_hori_proj_tbl {
  int32_t tbl[ISP_DVS_NUM_COEF_TYPES * ISP_MAX_SDIS_HOR_PROJ_NUM_ISP];
#if DVS2_PROJ_MARGIN > 0
  int32_t margin[DVS2_PROJ_MARGIN];
#endif
};

struct sh_css_isp_sdis_vert_proj_tbl {
  int32_t tbl[ISP_DVS_NUM_COEF_TYPES * ISP_MAX_SDIS_VER_PROJ_NUM_ISP];
#if DVS2_PROJ_MARGIN > 0
  int32_t margin[DVS2_PROJ_MARGIN];
#endif
};

struct sh_css_isp_sdis_hori_coef_tbl {
  VMEM_ARRAY(tbl[ISP_DVS_NUM_COEF_TYPES], ISP_MAX_SDIS_HOR_COEF_NUM_VECS*ISP_NWAY);
};

struct sh_css_isp_sdis_vert_coef_tbl {
  VMEM_ARRAY(tbl[ISP_DVS_NUM_COEF_TYPES], ISP_MAX_SDIS_VER_COEF_NUM_VECS*ISP_NWAY);
};

#endif /* defined(__ISP) || defined (MK_FIRMWARE) */
#endif /* PIPE_GENERATION */

#ifndef PIPE_GENERATION
struct s_sdis_config {
  unsigned horicoef_vectors;
  unsigned vertcoef_vectors;
  unsigned horiproj_num;
  unsigned vertproj_num;
};

extern struct s_sdis_config sdis_config;
#endif

#endif /* _IA_CSS_SDIS_COMMON_HOST_H */
