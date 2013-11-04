/* Release Version: ci_master_20131030_2214 */
/*
 * Support for Intel Camera Imaging ISP subsystem.
 *
 * Copyright (c) 2010 - 2013 Intel Corporation. All Rights Reserved.
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

#ifndef __PIXELGEN_PRIVATE_H_INCLUDED__
#define __PIXELGEN_PRIVATE_H_INCLUDED__
#include "pixelgen_public.h"
#include "hive_isp_css_host_ids_hrt.h"
#include "PixelGen_SysBlock_defs.h"
#include "device_access.h"	/* ia_css_device_load_uint32 */
#include "assert_support.h" /* assert */


/*****************************************************
 *
 * Native command interface (NCI).
 *
 *****************************************************/
/**
 * @brief Get the pixelgen state.
 * Refer to "pixelgen_public.h" for details.
 */
STORAGE_CLASS_PIXELGEN_C void pixelgen_ctrl_get_state(
		const pixelgen_ID_t ID,
		pixelgen_ctrl_state_t *state)
{

	state->com_enable =
		pixelgen_ctrl_reg_load(ID, _PXG_COM_ENABLE_REG_IDX);
	state->prbs_rstval0 =
		pixelgen_ctrl_reg_load(ID, _PXG_PRBS_RSTVAL_REG0_IDX);
	state->prbs_rstval1 =
		pixelgen_ctrl_reg_load(ID, _PXG_PRBS_RSTVAL_REG1_IDX);
	state->syng_sid =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_SID_REG_IDX);
	state->syng_free_run =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_FREE_RUN_REG_IDX);
	state->syng_pause =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_PAUSE_REG_IDX);
	state->syng_nof_frames =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_NOF_FRAME_REG_IDX);
	state->syng_nof_pixels =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_NOF_PIXEL_REG_IDX);
	state->syng_nof_line =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_NOF_LINE_REG_IDX);
	state->syng_hblank_cyc =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_HBLANK_CYC_REG_IDX);
	state->syng_vblank_cyc =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_VBLANK_CYC_REG_IDX);
	state->syng_stat_hcnt =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_STAT_HCNT_REG_IDX);
	state->syng_stat_vcnt =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_STAT_VCNT_REG_IDX);
	state->syng_stat_fcnt =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_STAT_FCNT_REG_IDX);
	state->syng_stat_done =
		pixelgen_ctrl_reg_load(ID, _PXG_SYNG_STAT_DONE_REG_IDX);
	state->tpg_mode =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_MODE_REG_IDX);
	state->tpg_hcnt_mask =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_HCNT_MASK_REG_IDX);
	state->tpg_vcnt_mask =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_VCNT_MASK_REG_IDX);
	state->tpg_xycnt_mask =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_XYCNT_MASK_REG_IDX);
	state->tpg_hcnt_delta =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_HCNT_DELTA_REG_IDX);
	state->tpg_vcnt_delta =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_VCNT_DELTA_REG_IDX);
	state->tpg_r1 =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_R1_REG_IDX);
	state->tpg_g1 =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_G1_REG_IDX);
	state->tpg_b1 =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_B1_REG_IDX);
	state->tpg_r2 =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_R2_REG_IDX);
	state->tpg_g2 =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_G2_REG_IDX);
	state->tpg_b2 =
		pixelgen_ctrl_reg_load(ID, _PXG_TPG_B2_REG_IDX);
}
/* end of NCI */
/*****************************************************
 *
 * Device level interface (DLI).
 *
 *****************************************************/
/**
 * @brief Load the register value.
 * Refer to "pixelgen_public.h" for details.
 */
STORAGE_CLASS_PIXELGEN_C hrt_data pixelgen_ctrl_reg_load(
	const pixelgen_ID_t ID,
	const hrt_address reg)
{
	assert(ID < N_PIXELGEN_ID);
	assert(PIXELGEN_CTRL_BASE[ID] != (hrt_address)-1);
	return ia_css_device_load_uint32(PIXELGEN_CTRL_BASE[ID] + reg*sizeof(hrt_data));
}


/**
 * @brief Store a value to the register.
 * Refer to "pixelgen_ctrl_public.h" for details.
 */
STORAGE_CLASS_PIXELGEN_C void pixelgen_ctrl_reg_store(
	const pixelgen_ID_t ID,
	const hrt_address reg,
	const hrt_data value)
{
	assert(ID < N_PIXELGEN_ID);
	assert(PIXELGEN_CTRL_BASE[ID] != (hrt_address)-1);

	ia_css_device_store_uint32(PIXELGEN_CTRL_BASE[ID] + reg*sizeof(hrt_data), value);
}
/** end of DLI */
#endif /* __PIXELGEN_PRIVATE_H_INCLUDED__ */
