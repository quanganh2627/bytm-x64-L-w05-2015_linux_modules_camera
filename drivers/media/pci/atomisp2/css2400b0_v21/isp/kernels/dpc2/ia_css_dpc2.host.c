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

#include "ia_css_dpc2.host.h"
#include "assert_support.h"

#define METRIC1_ONE_FP	(1<<12)
#define METRIC2_ONE_FP	(1<<5)
#define METRIC3_ONE_FP	(1<<12)
#define WBGAIN_ONE_FP	(1<<9)

void
ia_css_dpc2_encode(
	struct ia_css_isp_dpc2_params *to,
	const struct ia_css_dpc2_config *from,
	size_t size)
{
	(void)size;

	assert ((from->metric1 >= 0) && (from->metric1 <= METRIC1_ONE_FP));
	assert ((from->metric3 >= 0) && (from->metric3 <= METRIC3_ONE_FP));
	assert ((from->metric2 >= METRIC2_ONE_FP) &&
			(from->metric2 < 256*METRIC2_ONE_FP));
	assert ((from->wb_gain_gr > 0) && (from->wb_gain_gr < 16*WBGAIN_ONE_FP));
	assert ((from->wb_gain_r  > 0) && (from->wb_gain_r  < 16*WBGAIN_ONE_FP));
	assert ((from->wb_gain_b  > 0) && (from->wb_gain_b  < 16*WBGAIN_ONE_FP));
	assert ((from->wb_gain_gb > 0) && (from->wb_gain_gb < 16*WBGAIN_ONE_FP));

	/* TODO: BBBs */
	to->one_plus_metric1  = METRIC1_ONE_FP + from->metric1;
	to->one_minus_metric1 = METRIC1_ONE_FP - from->metric1;
	to->one_plus_metric3  = METRIC3_ONE_FP + from->metric3;

	to->wb_gain_gr = from->wb_gain_gr;
	to->wb_gain_r  = from->wb_gain_r;
	to->wb_gain_b  = from->wb_gain_b;
	to->wb_gain_gb = from->wb_gain_gb;

	/* TODO: Double-check the precision here by MUL and SHIFT operation */
	to->wb_gain_gr_scaled_by_metric2 = (from->wb_gain_gr * from->metric2) >> 13;
	to->wb_gain_r_scaled_by_metric2  = (from->wb_gain_r  * from->metric2) >> 13;
	to->wb_gain_b_scaled_by_metric2  = (from->wb_gain_b  * from->metric2) >> 13;
	to->wb_gain_gb_scaled_by_metric2 = (from->wb_gain_gb * from->metric2) >> 13;
}

