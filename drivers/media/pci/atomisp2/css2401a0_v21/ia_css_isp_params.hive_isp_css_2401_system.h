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

/* Generated code: do not edit or commmit. */

#ifndef _IA_CSS_ISP_PARAM_H
#define _IA_CSS_ISP_PARAM_H

enum ia_css_parameter_ids {
	IA_CSS_BH_ID,
	IA_CSS_DP_ID,
	IA_CSS_AA_ID,
	IA_CSS_ANR_ID,
	IA_CSS_NR_ID,
	IA_CSS_RAA_ID,
	IA_CSS_WB_ID,
	IA_CSS_YEE_ID,
	IA_CSS_OB_ID,
	IA_CSS_BNR_ID,
	IA_CSS_S3A_ID,
	IA_CSS_CSC_ID,
	IA_CSS_RGB2YUV_ID,
	IA_CSS_YUV2RGB_ID,
	IA_CSS_CE_ID,
	IA_CSS_GC_ID,
	IA_CSS_FC_ID,
	IA_CSS_DE_ID,
	IA_CSS_CNR_ID,
	IA_CSS_CTC_ID,
	IA_CSS_ECD_ID,
	IA_CSS_FPN_ID,
	IA_CSS_MACC_ID,
	IA_CSS_RAW_ID,
	IA_CSS_SC_ID,
	IA_CSS_TNR_ID,
	IA_CSS_YNR_ID,
	IA_CSS_R_GAMMA_ID,
	IA_CSS_G_GAMMA_ID,
	IA_CSS_XNR_ID,
	IA_CSS_B_GAMMA_ID,
	IA_CSS_NUM_PARAMETER_IDS
};

struct ia_css_memory_offsets {
	struct {
		uint16_t bh;
		uint16_t dp;
		uint16_t aa;
		uint16_t anr;
		uint16_t nr;
		uint16_t raa;
		uint16_t wb;
		uint16_t yee;
		uint16_t ob;
		uint16_t bnr;
		uint16_t s3a;
		uint16_t csc;
		uint16_t rgb2yuv;
		uint16_t yuv2rgb;
		uint16_t ce;
		uint16_t gc;
		uint16_t fc;
		uint16_t de;
		uint16_t cnr;
		uint16_t ctc;
		uint16_t ecd;
		uint16_t fpn;
		uint16_t macc;
		uint16_t raw;
		uint16_t sc;
		uint16_t tnr;
		uint16_t ynr;
	} dmem;
	struct {
		uint16_t bh;
	} hmem0;
	struct {
		uint16_t ctc;
		uint16_t r_gamma;
	} vamem0;
	struct {
		uint16_t g_gamma;
		uint16_t gc;
		uint16_t xnr;
	} vamem1;
	struct {
		uint16_t b_gamma;
	} vamem2;
	struct {
		uint16_t ob;
	} vmem;
};

#if defined(IA_CSS_INCLUDE_PARAMETERS)

struct ia_css_pipeline_stage; /* forward declaration */
extern void (* ia_css_kernel_process[IA_CSS_NUM_PARAMETER_IDS])(unsigned pipe_id,
                            const struct ia_css_pipeline_stage *stage,
                            struct ia_css_isp_parameters *params);

void
ia_css_set_dp_config(struct ia_css_isp_parameters *params,
			const struct ia_css_dp_config *config);

void
ia_css_set_wb_config(struct ia_css_isp_parameters *params,
			const struct ia_css_wb_config *config);

void
ia_css_set_tnr_config(struct ia_css_isp_parameters *params,
			const struct ia_css_tnr_config *config);

void
ia_css_set_ob_config(struct ia_css_isp_parameters *params,
			const struct ia_css_ob_config *config);

void
ia_css_set_de_config(struct ia_css_isp_parameters *params,
			const struct ia_css_de_config *config);

void
ia_css_set_anr_config(struct ia_css_isp_parameters *params,
			const struct ia_css_anr_config *config);

void
ia_css_set_ce_config(struct ia_css_isp_parameters *params,
			const struct ia_css_ce_config *config);

void
ia_css_set_ecd_config(struct ia_css_isp_parameters *params,
			const struct ia_css_ecd_config *config);

void
ia_css_set_ynr_config(struct ia_css_isp_parameters *params,
			const struct ia_css_ynr_config *config);

void
ia_css_set_fc_config(struct ia_css_isp_parameters *params,
			const struct ia_css_fc_config *config);

void
ia_css_set_cnr_config(struct ia_css_isp_parameters *params,
			const struct ia_css_cnr_config *config);

void
ia_css_set_macc_config(struct ia_css_isp_parameters *params,
			const struct ia_css_macc_config *config);

void
ia_css_set_ctc_config(struct ia_css_isp_parameters *params,
			const struct ia_css_ctc_config *config);

void
ia_css_set_aa_config(struct ia_css_isp_parameters *params,
			const struct ia_css_aa_config *config);

void
ia_css_set_yuv2rgb_config(struct ia_css_isp_parameters *params,
			const struct ia_css_cc_config *config);

void
ia_css_set_rgb2yuv_config(struct ia_css_isp_parameters *params,
			const struct ia_css_cc_config *config);

void
ia_css_set_csc_config(struct ia_css_isp_parameters *params,
			const struct ia_css_cc_config *config);

void
ia_css_set_nr_config(struct ia_css_isp_parameters *params,
			const struct ia_css_nr_config *config);

void
ia_css_set_gc_config(struct ia_css_isp_parameters *params,
			const struct ia_css_gc_config *config);

void
ia_css_set_r_gamma_config(struct ia_css_isp_parameters *params,
			const struct ia_css_rgb_gamma_table *config);

void
ia_css_set_g_gamma_config(struct ia_css_isp_parameters *params,
			const struct ia_css_rgb_gamma_table *config);

void
ia_css_set_b_gamma_config(struct ia_css_isp_parameters *params,
			const struct ia_css_rgb_gamma_table *config);

void
ia_css_set_xnr_config(struct ia_css_isp_parameters *params,
			const struct ia_css_xnr_table *config);

void
ia_css_set_s3a_config(struct ia_css_isp_parameters *params,
			const struct ia_css_3a_config *config);

void
ia_css_get_configs(struct ia_css_isp_parameters *params,
		const struct ia_css_isp_config *config)
;
void
ia_css_set_configs(struct ia_css_isp_parameters *params,
		const struct ia_css_isp_config *config)
;
#endif /* IA_CSS_INCLUDE_PARAMETER */

#endif /* _IA_CSS_ISP_PARAM_H */
