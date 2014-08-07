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


#ifndef __REF_VECTOR_FUNC_TYPES_H_INCLUDED__
#define __REF_VECTOR_FUNC_TYPES_H_INCLUDED__


/*
 * Prerequisites:
 *
 */
#include "mpmath.h"
#include "isp_op1w_types.h"
#include "isp_op2w_types.h"

#define MAX_CONFIG_POINTS 5
#define INPUT_OFFSET_FACTOR 10
#define INPUT_SCALE_FACTOR 10
#define OUTPUT_SCALE_FACTOR 10
#define SLOPE_A_RESOLUTION 10
#define CONFIG_UNIT_LUT_SIZE 32

#define ONE_IN_Q14 (1<<(NUM_BITS-2))
#define Q29_TO_Q15_SHIFT_VAL (NUM_BITS-2)
#define Q28_TO_Q15_SHIFT_VAL (NUM_BITS-3)

/* Block matching algorithm related data */
/* NUM_OF_SADS = ((SEARCH_AREA_HEIGHT - REF_BLOCK_HEIGHT)/PIXEL_SHIFT + 1)* \
					((SEARCH_AREA_WIDTH - REF_BLOCK_WIDTH)/PIXEL_SHIFT + 1) */

#define SADS(sw_h,sw_w, ref_h, ref_w, p_sh) (((sw_h - ref_h)/p_sh + 1)*((sw_w - ref_w)/p_sh + 1))
#define SADS_16x16_1	SADS(16, 16, 8, 8, 1)
#define SADS_16x16_2	SADS(16, 16, 8, 8, 2)
#define SADS_14x14_1	SADS(14, 14, 8, 8, 1)
#define SADS_14x14_2	SADS(14, 14, 8, 8, 2)

#define BMA_OUTPUT_MATRIX_DIM(sw_h, ref_h, p_sh)	((sw_h - ref_h)/p_sh + 1)
#define BMA_OUT_16x16_2_32		BMA_OUTPUT_MATRIX_DIM(16, 8, 2)
#define BMA_OUT_14x14_2_32		BMA_OUTPUT_MATRIX_DIM(14, 8, 2)
#define BMA_OUT_16x16_1_32 		BMA_OUTPUT_MATRIX_DIM(16, 8, 1)
#define BMA_OUT_14x14_1_32 		BMA_OUTPUT_MATRIX_DIM(14, 8, 1)
#define BMA_SEARCH_BLOCK_SZ_16 	16
#define BMA_REF_BLOCK_SZ_8    	8
#define PIXEL_SHIFT_2         	2
#define PIXEL_SHIFT_1         	1
#define BMA_SEARCH_WIN_SZ_16  	16
#define BMA_SEARCH_WIN_SZ_14  	14


/*
 * Struct type specification
 */

typedef unsigned short tscalar1w_3bit;
typedef short tscalar1w_5bit_signed;
typedef unsigned short tscalar1w_5bit;
typedef short tscalar1w_range1wbit;
typedef short tscalar1w_unsigned_range1wbit;
typedef unsigned short tvector_5bit;
typedef unsigned short tvector_4bit;
typedef unsigned short tvector1w_unsigned;
typedef unsigned int   tvector2w_unsigned;
typedef short tscalar1w_signed_positive;
typedef short tvector1w_signed_positive;
typedef unsigned short tscalar1w_16bit;
typedef unsigned short tscalar1w_4bit;

typedef struct {
  tvector1w     v0  ;
  tvector1w     v1 ;
} s_1w_2x1_matrix;

typedef struct {
  tvector1w     v00  ;
  tvector1w     v01 ;
  tvector1w     v02 ;
} s_1w_1x3_matrix;

typedef struct {
  tvector1w v00; tvector1w v01; tvector1w v02;
  tvector1w v10; tvector1w v11; tvector1w v12;
} s_1w_2x3_matrix;

typedef struct {
  tvector1w     v00  ; tvector1w     v01 ; tvector1w     v02  ;
  tvector1w     v10  ; tvector1w     v11 ; tvector1w     v12  ;
  tvector1w     v20  ; tvector1w     v21 ; tvector1w     v22  ;
} s_1w_3x3_matrix;

typedef struct {
  tvector1w     v00  ; tvector1w     v01 ; tvector1w     v02  ;
  tvector1w     v10  ; tvector1w     v11 ; tvector1w     v12  ;
  tvector1w     v20  ; tvector1w     v21 ; tvector1w     v22  ;
  tvector1w     v30  ; tvector1w     v31 ; tvector1w     v32  ;
} s_1w_4x3_matrix;

typedef struct {
  tvector1w     v00 ;
  tvector1w     v01 ;
  tvector1w     v02 ;
  tvector1w     v03 ;
  tvector1w     v04 ;
} s_1w_1x5_matrix;

typedef struct {
  tvector1w     v00  ; tvector1w     v01 ; tvector1w     v02  ; tvector1w     v03 ; tvector1w     v04  ;
  tvector1w     v10  ; tvector1w     v11 ; tvector1w     v12  ; tvector1w     v13 ; tvector1w     v14  ;
  tvector1w     v20  ; tvector1w     v21 ; tvector1w     v22  ; tvector1w     v23 ; tvector1w     v24  ;
  tvector1w     v30  ; tvector1w     v31 ; tvector1w     v32  ; tvector1w     v33 ; tvector1w     v34  ;
  tvector1w     v40  ; tvector1w     v41 ; tvector1w     v42  ; tvector1w     v43 ; tvector1w     v44  ;
} s_1w_5x5_matrix;

typedef struct {
  tvector1w     v00 ;
  tvector1w     v01 ;
  tvector1w     v02 ;
  tvector1w     v03 ;
  tvector1w     v04 ;
  tvector1w     v05 ;
  tvector1w     v06 ;
  tvector1w     v07 ;
  tvector1w     v08 ;
} s_1w_1x9_matrix;

typedef struct {
	tvector1w v00;
	tvector1w v01;
	tvector1w v02;
	tvector1w v03;
} s_1w_1x4_matrix;

typedef struct {
	tvector1w v00; tvector1w v01; tvector1w v02; tvector1w v03;
	tvector1w v10; tvector1w v11; tvector1w v12; tvector1w v13;
	tvector1w v20; tvector1w v21; tvector1w v22; tvector1w v23;
	tvector1w v30; tvector1w v31; tvector1w v32; tvector1w v33;
} s_1w_4x4_matrix;

typedef struct {
	tvector1w v00;
	tvector1w v01;
	tvector1w v02;
	tvector1w v03;
	tvector1w v04;
	tvector1w v05;
} s_1w_1x6_matrix;

typedef struct {
	tvector1w x_cord[MAX_CONFIG_POINTS];
	tvector1w slope[MAX_CONFIG_POINTS-1];
	tvector1w y_offset[MAX_CONFIG_POINTS-1];
} ref_config_points;

typedef struct {
	tscalar1w_16bit slope_vec[CONFIG_UNIT_LUT_SIZE];
	tscalar1w_16bit offset_vec[CONFIG_UNIT_LUT_SIZE];
	tscalar1w_16bit x_cord_vec[CONFIG_UNIT_LUT_SIZE];
	tscalar1w_16bit exponent;
} ref_config_point_vectors;

typedef struct {
	tscalar1w search[BMA_SEARCH_BLOCK_SZ_16][BMA_SEARCH_BLOCK_SZ_16];
} bma_16x16_search_window;

typedef struct {
	tscalar1w ref[BMA_REF_BLOCK_SZ_8][BMA_REF_BLOCK_SZ_8];
} ref_block_8x8;

typedef struct {
	tscalar1w sads[SADS_16x16_1];
} bma_output_16_1;

typedef struct {
	tscalar1w sads[SADS_16x16_2];
} bma_output_16_2;

typedef struct {
	tscalar1w sads[SADS_14x14_2];
} bma_output_14_2;

typedef struct {
	tscalar1w sads[SADS_14x14_1];
} bma_output_14_1;

#endif /* __REF_VECTOR_FUNC_TYPES_H_INCLUDED__ */
