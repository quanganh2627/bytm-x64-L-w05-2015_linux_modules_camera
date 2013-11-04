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


#include "ia_css_types.h"
#include "sh_css_defs.h"
#include "ia_css_debug.h"
#include "sh_css_frac.h"
#include "assert_support.h"

#include "ia_css_wb.host.h"

const struct ia_css_wb_config default_wb_config = {
	1,
	32768,
	32768,
	32768,
	32768
};

void
ia_css_wb_encode(struct sh_css_isp_wb_params *to,
		 const struct ia_css_wb_config *from)
{
	to->gain_shift =
	    uISP_REG_BIT - from->integer_bits;
	to->gain_gr =
	    uDIGIT_FITTING(from->gr, 16 - from->integer_bits,
			   to->gain_shift);
	to->gain_r =
	    uDIGIT_FITTING(from->r, 16 - from->integer_bits,
			   to->gain_shift);
	to->gain_b =
	    uDIGIT_FITTING(from->b, 16 - from->integer_bits,
			   to->gain_shift);
	to->gain_gb =
	    uDIGIT_FITTING(from->gb, 16 - from->integer_bits,
			   to->gain_shift);
}

void
ia_css_wb_dump(const struct sh_css_isp_wb_params *wb, unsigned level)
{
	ia_css_debug_dtrace(level, "White Balance:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"wb_gain_shift", wb->gain_shift);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"wb_gain_gr", wb->gain_gr);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"wb_gain_r", wb->gain_r);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"wb_gain_b", wb->gain_b);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"wb_gain_gb", wb->gain_gb);
}

void
ia_css_wb_debug_dtrace(const struct ia_css_wb_config *config, unsigned level)
{
	ia_css_debug_dtrace(level,
		"config.integer_bits=%d, "
		"config.gr=%d, config.r=%d, "
		"config.b=%d, config.gb=%d\n",
		config->integer_bits,
		config->gr, config->r,
		config->b, config->gb);
}
