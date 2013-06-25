/*
 * Support for Sony IMX camera sensor.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
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

#ifndef __IMX135VB_H__
#define __IMX135VB_H__

#include "common.h"

#define IMX_SC_CMMN_CHIP_ID_H	0x0016
#define IMX_SC_CMMN_CHIP_ID_L	0x0017

/*
 * focal length bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#define IMX_FOCAL_LENGTH_DEFAULT 0x1710064

/*
 * current f-number bits definition:
 * bits 31-16: numerator, bits 15-0: denominator
 */
#define IMX_F_NUMBER_DEFAULT 0x16000a

/*
 * f-number range bits definition:
 * bits 31-24: max f-number numerator
 * bits 23-16: max f-number denominator
 * bits 15-8: min f-number numerator
 * bits 7-0: min f-number denominator
 */
#define IMX_F_NUMBER_RANGE 0x160a160a

#define GROUPED_PARAMETER_HOLD_ENABLE  {IMX_8BIT, 0x0104, 0x1}
#define GROUPED_PARAMETER_HOLD_DISABLE  {IMX_8BIT, 0x0104, 0x0}

/*
 * We use three different MIPI rates for our modes based on the resolution and
 * FPS requirements. So we have three PLL configurationa and these are based
 * on the EMC friendly MIPI values.
 *
 * Maximum clock: Pix clock @ 360.96MHz MIPI @ 451.2MHz 902.4mbps
 * Reduced clock: Pix clock @ 273.00MHz MIPI @ 342.0MHz 684.0mbps
 * Binning modes: Pix clock @ 335.36MHz MIPI @ 209.6MHz 419.2mbps
 * Global Timing registers are based on the data rates and these are part of
 * the below clock definitions.
 */

/* MIPI 451.2MHz 902.4mbps PIXCLK: 360.96MHz */
#define PLL_SETTINGS_FOR_MIPI_451_2MHZ \
	{IMX_8BIT, 0x011e, 0x13}, \
	{IMX_8BIT, 0x011f, 0x33}, \
	{IMX_8BIT, 0x0301, 0x05}, \
	{IMX_8BIT, 0x0303, 0x01}, \
	{IMX_8BIT, 0x0305, 0x0c}, \
	{IMX_8BIT, 0x0309, 0x05}, \
	{IMX_8BIT, 0x030b, 0x01}, \
	{IMX_8BIT, 0x030c, 0x02}, \
	{IMX_8BIT, 0x030d, 0x34}, \
	{IMX_8BIT, 0x030e, 0x01}, \
	{IMX_8BIT, 0x3a06, 0x11}, \
	{IMX_8BIT, 0x0830, 0x87}, \
	{IMX_8BIT, 0x0831, 0x3f}, \
	{IMX_8BIT, 0x0832, 0x67}, \
	{IMX_8BIT, 0x0833, 0x3f}, \
	{IMX_8BIT, 0x0834, 0x3f}, \
	{IMX_8BIT, 0x0835, 0x4f}, \
	{IMX_8BIT, 0x0836, 0xdf}, \
	{IMX_8BIT, 0x0837, 0x47}, \
	{IMX_8BIT, 0x0839, 0x1f}, \
	{IMX_8BIT, 0x083a, 0x17}, \
	{IMX_8BIT, 0x083b, 0x02}

/* MIPI 209.6MHz, 419.2mbps PIXCLK: 335.36 MHz */
#define PLL_SETTINGS_FOR_MIPI_209_6MHZ \
	{IMX_8BIT, 0x011e, 0x13}, \
	{IMX_8BIT, 0x011f, 0x33}, \
	{IMX_8BIT, 0x0301, 0x05}, \
	{IMX_8BIT, 0x0303, 0x01}, \
	{IMX_8BIT, 0x0305, 0x06}, \
	{IMX_8BIT, 0x0309, 0x05}, \
	{IMX_8BIT, 0x030b, 0x02}, \
	{IMX_8BIT, 0x030c, 0x01}, \
	{IMX_8BIT, 0x030d, 0x06}, \
	{IMX_8BIT, 0x030e, 0x01}, \
	{IMX_8BIT, 0x3a06, 0x12}, \
	{IMX_8BIT, 0x0830, 0x67}, \
	{IMX_8BIT, 0x0831, 0x1f}, \
	{IMX_8BIT, 0x0832, 0x47}, \
	{IMX_8BIT, 0x0833, 0x1f}, \
	{IMX_8BIT, 0x0834, 0x1f}, \
	{IMX_8BIT, 0x0835, 0x17}, \
	{IMX_8BIT, 0x0836, 0x77}, \
	{IMX_8BIT, 0x0837, 0x27}, \
	{IMX_8BIT, 0x0839, 0x1f}, \
	{IMX_8BIT, 0x083a, 0x17}, \
	{IMX_8BIT, 0x083b, 0x02}

/* MIPI 342MHz 684mbps PIXCLK: 273.6MHz */
#define PLL_SETTINGS_FOR_MIPI_342MHZ \
	{IMX_8BIT, 0x011e, 0x13}, \
	{IMX_8BIT, 0x011f, 0x33}, \
	{IMX_8BIT, 0x0301, 0x05}, \
	{IMX_8BIT, 0x0303, 0x01}, \
	{IMX_8BIT, 0x0305, 0x08}, \
	{IMX_8BIT, 0x0309, 0x05}, \
	{IMX_8BIT, 0x030b, 0x01}, \
	{IMX_8BIT, 0x030c, 0x01}, \
	{IMX_8BIT, 0x030d, 0x1d}, \
	{IMX_8BIT, 0x030e, 0x01}, \
	{IMX_8BIT, 0x3a06, 0x11}, \
	{IMX_8BIT, 0x0830, 0x77}, \
	{IMX_8BIT, 0x0831, 0x2f}, \
	{IMX_8BIT, 0x0832, 0x4f}, \
	{IMX_8BIT, 0x0833, 0x37}, \
	{IMX_8BIT, 0x0834, 0x2f}, \
	{IMX_8BIT, 0x0835, 0x37}, \
	{IMX_8BIT, 0x0836, 0xaf}, \
	{IMX_8BIT, 0x0837, 0x37}, \
	{IMX_8BIT, 0x0839, 0x1f}, \
	{IMX_8BIT, 0x083a, 0x17}, \
	{IMX_8BIT, 0x083b, 0x02}

/* Basic settings: Applied only once after the sensor power up */
static struct imx_reg const imx135vb_init_settings[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	{ IMX_8BIT, 0x0220, 0x01},
	{ IMX_8BIT, 0x3008, 0xB0},
	{ IMX_8BIT, 0x320A, 0x01},
	{ IMX_8BIT, 0x320D, 0x10},
	{ IMX_8BIT, 0x3216, 0x2E},
	{ IMX_8BIT, 0x3230, 0x0A},
	{ IMX_8BIT, 0x3228, 0x05},
	{ IMX_8BIT, 0x3229, 0x02},
	{ IMX_8BIT, 0x322C, 0x02},
	{ IMX_8BIT, 0x3302, 0x10},
	{ IMX_8BIT, 0x3390, 0x45},
	{ IMX_8BIT, 0x3409, 0x0C},
	{ IMX_8BIT, 0x340B, 0xF5},
	{ IMX_8BIT, 0x340C, 0x2D},
	{ IMX_8BIT, 0x3412, 0x41},
	{ IMX_8BIT, 0x3413, 0xAD},
	{ IMX_8BIT, 0x3414, 0x1E},
	{ IMX_8BIT, 0x3427, 0x04},
	{ IMX_8BIT, 0x3480, 0x1E},
	{ IMX_8BIT, 0x3484, 0x1E},
	{ IMX_8BIT, 0x3488, 0x1E},
	{ IMX_8BIT, 0x348C, 0x1E},
	{ IMX_8BIT, 0x3490, 0x1E},
	{ IMX_8BIT, 0x3494, 0x1E},
	{ IMX_8BIT, 0x349C, 0x38},
	{ IMX_8BIT, 0x34A3, 0x38},
	{ IMX_8BIT, 0x3511, 0x8F},
	{ IMX_8BIT, 0x3518, 0x00},
	{ IMX_8BIT, 0x3519, 0x94},
	{ IMX_8BIT, 0x3833, 0x20},
	{ IMX_8BIT, 0x3893, 0x01},
	{ IMX_8BIT, 0x38C2, 0x08},
	{ IMX_8BIT, 0x38C3, 0x08},
	{ IMX_8BIT, 0x3C09, 0x01},
	{ IMX_8BIT, 0x4000, 0x0E},
	{ IMX_8BIT, 0x4300, 0x00},
	{ IMX_8BIT, 0x4316, 0x12},
	{ IMX_8BIT, 0x4317, 0x22},
	{ IMX_8BIT, 0x4318, 0x00},
	{ IMX_8BIT, 0x4319, 0x00},
	{ IMX_8BIT, 0x431A, 0x00},
	{ IMX_8BIT, 0x4324, 0x03},
	{ IMX_8BIT, 0x4325, 0x20},
	{ IMX_8BIT, 0x4326, 0x03},
	{ IMX_8BIT, 0x4327, 0x84},
	{ IMX_8BIT, 0x4328, 0x03},
	{ IMX_8BIT, 0x4329, 0x20},
	{ IMX_8BIT, 0x432A, 0x03},
	{ IMX_8BIT, 0x432B, 0x84},
	{ IMX_8BIT, 0x432C, 0x01},
	{ IMX_8BIT, 0x4401, 0x3F},
	{ IMX_8BIT, 0x4402, 0xFF},
	{ IMX_8BIT, 0x4412, 0x3F},
	{ IMX_8BIT, 0x4413, 0xFF},
	{ IMX_8BIT, 0x441D, 0x28},
	{ IMX_8BIT, 0x4444, 0x00},
	{ IMX_8BIT, 0x4445, 0x00},
	{ IMX_8BIT, 0x4446, 0x3F},
	{ IMX_8BIT, 0x4447, 0xFF},
	{ IMX_8BIT, 0x4452, 0x00},
	{ IMX_8BIT, 0x4453, 0xA0},
	{ IMX_8BIT, 0x4454, 0x08},
	{ IMX_8BIT, 0x4455, 0x00},
	{ IMX_8BIT, 0x4458, 0x18},
	{ IMX_8BIT, 0x4459, 0x18},
	{ IMX_8BIT, 0x445A, 0x3F},
	{ IMX_8BIT, 0x445B, 0x3A},
	{ IMX_8BIT, 0x4462, 0x00},
	{ IMX_8BIT, 0x4463, 0x00},
	{ IMX_8BIT, 0x4464, 0x00},
	{ IMX_8BIT, 0x4465, 0x00},
	{ IMX_8BIT, 0x446E, 0x01},
	{ IMX_8BIT, 0x4500, 0x1F},
	{ IMX_8BIT, 0x600a, 0x00},
	{ IMX_8BIT, 0x380a, 0x00},
	{ IMX_8BIT, 0x380b, 0x00},
	{ IMX_8BIT, 0x4103, 0x00},
	{ IMX_8BIT, 0x4243, 0x9a},
	{ IMX_8BIT, 0x4330, 0x01},
	{ IMX_8BIT, 0x4331, 0x90},
	{ IMX_8BIT, 0x4332, 0x02},
	{ IMX_8BIT, 0x4333, 0x58},
	{ IMX_8BIT, 0x4334, 0x03},
	{ IMX_8BIT, 0x4335, 0x20},
	{ IMX_8BIT, 0x4336, 0x03},
	{ IMX_8BIT, 0x4337, 0x84},
	{ IMX_8BIT, 0x433C, 0x01},
	{ IMX_8BIT, 0x4340, 0x02},
	{ IMX_8BIT, 0x4341, 0x58},
	{ IMX_8BIT, 0x4342, 0x03},
	{ IMX_8BIT, 0x4343, 0x52},
	{ IMX_8BIT, 0x4364, 0x0b},
	{ IMX_8BIT, 0x4368, 0x00},
	{ IMX_8BIT, 0x4369, 0x0f},
	{ IMX_8BIT, 0x436a, 0x03},
	{ IMX_8BIT, 0x436b, 0xa8},
	{ IMX_8BIT, 0x436c, 0x00},
	{ IMX_8BIT, 0x436d, 0x00},
	{ IMX_8BIT, 0x436e, 0x00},
	{ IMX_8BIT, 0x436f, 0x06},
	{ IMX_8BIT, 0x4281, 0x21},
	{ IMX_8BIT, 0x4282, 0x18},
	{ IMX_8BIT, 0x4283, 0x04},
	{ IMX_8BIT, 0x4284, 0x08},
	{ IMX_8BIT, 0x4287, 0x7f},
	{ IMX_8BIT, 0x4288, 0x08},
	{ IMX_8BIT, 0x428b, 0x7f},
	{ IMX_8BIT, 0x428c, 0x08},
	{ IMX_8BIT, 0x428f, 0x7f},
	{ IMX_8BIT, 0x4297, 0x00},
	{ IMX_8BIT, 0x4298, 0x7E},
	{ IMX_8BIT, 0x4299, 0x7E},
	{ IMX_8BIT, 0x429A, 0x7E},
	{ IMX_8BIT, 0x42A4, 0xFB},
	{ IMX_8BIT, 0x42A5, 0x7E},
	{ IMX_8BIT, 0x42A6, 0xDF},
	{ IMX_8BIT, 0x42A7, 0xB7},
	{ IMX_8BIT, 0x42AF, 0x03},
	{ IMX_8BIT, 0x4207, 0x03},
	{ IMX_8BIT, 0x4216, 0x08},
	{ IMX_8BIT, 0x4217, 0x08},
	{ IMX_8BIT, 0x4218, 0x00},
	{ IMX_8BIT, 0x421B, 0x20},
	{ IMX_8BIT, 0x421F, 0x04},
	{ IMX_8BIT, 0x4222, 0x02},
	{ IMX_8BIT, 0x4223, 0x22},
	{ IMX_8BIT, 0x422E, 0x54},
	{ IMX_8BIT, 0x422F, 0xFB},
	{ IMX_8BIT, 0x4230, 0xFF},
	{ IMX_8BIT, 0x4231, 0xFE},
	{ IMX_8BIT, 0x4232, 0xFF},
	{ IMX_8BIT, 0x4235, 0x58},
	{ IMX_8BIT, 0x4236, 0xF7},
	{ IMX_8BIT, 0x4237, 0xFD},
	{ IMX_8BIT, 0x4239, 0x4E},
	{ IMX_8BIT, 0x423A, 0xFC},
	{ IMX_8BIT, 0x423B, 0xFD},
	{ IMX_8BIT, 0x4300, 0x00},
	{ IMX_8BIT, 0x4316, 0x12},
	{ IMX_8BIT, 0x4317, 0x22},
	{ IMX_8BIT, 0x4318, 0x00},
	{ IMX_8BIT, 0x4319, 0x00},
	{ IMX_8BIT, 0x431A, 0x00},
	{ IMX_8BIT, 0x4324, 0x03},
	{ IMX_8BIT, 0x4325, 0x20},
	{ IMX_8BIT, 0x4326, 0x03},
	{ IMX_8BIT, 0x4327, 0x84},
	{ IMX_8BIT, 0x4328, 0x03},
	{ IMX_8BIT, 0x4329, 0x20},
	{ IMX_8BIT, 0x432A, 0x03},
	{ IMX_8BIT, 0x432B, 0x20},
	{ IMX_8BIT, 0x432C, 0x01},
	{ IMX_8BIT, 0x432D, 0x01},
	{ IMX_8BIT, 0x4338, 0x02},
	{ IMX_8BIT, 0x4339, 0x00},
	{ IMX_8BIT, 0x433A, 0x00},
	{ IMX_8BIT, 0x433B, 0x02},
	{ IMX_8BIT, 0x435A, 0x03},
	{ IMX_8BIT, 0x435B, 0x84},
	{ IMX_8BIT, 0x435E, 0x01},
	{ IMX_8BIT, 0x435F, 0xFF},
	{ IMX_8BIT, 0x4360, 0x01},
	{ IMX_8BIT, 0x4361, 0xF4},
	{ IMX_8BIT, 0x4362, 0x03},
	{ IMX_8BIT, 0x4363, 0x84},
	{ IMX_8BIT, 0x437B, 0x01},
	{ IMX_8BIT, 0x4400, 0x00}, /* STATS off ISP do not support STATS*/
	{ IMX_8BIT, 0x4401, 0x3F},
	{ IMX_8BIT, 0x4402, 0xFF},
	{ IMX_8BIT, 0x4404, 0x13},
	{ IMX_8BIT, 0x4405, 0x26},
	{ IMX_8BIT, 0x4406, 0x07},
	{ IMX_8BIT, 0x4408, 0x20},
	{ IMX_8BIT, 0x4409, 0xE5},
	{ IMX_8BIT, 0x440A, 0xFB},
	{ IMX_8BIT, 0x440C, 0xF6},
	{ IMX_8BIT, 0x440D, 0xEA},
	{ IMX_8BIT, 0x440E, 0x20},
	{ IMX_8BIT, 0x4410, 0x00},
	{ IMX_8BIT, 0x4411, 0x00},
	{ IMX_8BIT, 0x4412, 0x3F},
	{ IMX_8BIT, 0x4413, 0xFF},
	{ IMX_8BIT, 0x4414, 0x1F},
	{ IMX_8BIT, 0x4415, 0xFF},
	{ IMX_8BIT, 0x4416, 0x20},
	{ IMX_8BIT, 0x4417, 0x00},
	{ IMX_8BIT, 0x4418, 0x1F},
	{ IMX_8BIT, 0x4419, 0xFF},
	{ IMX_8BIT, 0x441A, 0x20},
	{ IMX_8BIT, 0x441B, 0x00},
	{ IMX_8BIT, 0x441D, 0x40},
	{ IMX_8BIT, 0x441E, 0x1E},
	{ IMX_8BIT, 0x441F, 0x38},
	{ IMX_8BIT, 0x4420, 0x01},
	{ IMX_8BIT, 0x4444, 0x00},
	{ IMX_8BIT, 0x4445, 0x00},
	{ IMX_8BIT, 0x4446, 0x1D},
	{ IMX_8BIT, 0x4447, 0xF9},
	{ IMX_8BIT, 0x4452, 0x00},
	{ IMX_8BIT, 0x4453, 0xA0},
	{ IMX_8BIT, 0x4454, 0x08},
	{ IMX_8BIT, 0x4455, 0x00},
	{ IMX_8BIT, 0x4456, 0x0F},
	{ IMX_8BIT, 0x4457, 0xFF},
	{ IMX_8BIT, 0x4458, 0x18},
	{ IMX_8BIT, 0x4459, 0x18},
	{ IMX_8BIT, 0x445A, 0x3F},
	{ IMX_8BIT, 0x445B, 0x3A},
	{ IMX_8BIT, 0x445C, 0x00},
	{ IMX_8BIT, 0x445D, 0x28},
	{ IMX_8BIT, 0x445E, 0x01},
	{ IMX_8BIT, 0x445F, 0x90},
	{ IMX_8BIT, 0x4460, 0x00},
	{ IMX_8BIT, 0x4461, 0x60},
	{ IMX_8BIT, 0x4462, 0x00},
	{ IMX_8BIT, 0x4463, 0x00},
	{ IMX_8BIT, 0x4464, 0x00},
	{ IMX_8BIT, 0x4465, 0x00},
	{ IMX_8BIT, 0x446C, 0x00},
	{ IMX_8BIT, 0x446D, 0x00},
	{ IMX_8BIT, 0x446E, 0x00},
	{ IMX_8BIT, 0x452A, 0x02},
	{ IMX_8BIT, 0x0712, 0x01},
	{ IMX_8BIT, 0x0713, 0x00},
	{ IMX_8BIT, 0x0714, 0x01},
	{ IMX_8BIT, 0x0715, 0x00},
	{ IMX_8BIT, 0x0716, 0x01},
	{ IMX_8BIT, 0x0717, 0x00},
	{ IMX_8BIT, 0x0718, 0x01},
	{ IMX_8BIT, 0x0719, 0x00},
	{ IMX_8BIT, 0x4500, 0x1F },
	PLL_SETTINGS_FOR_MIPI_451_2MHZ,
	{ IMX_8BIT, 0x0205, 0x00},
	{ IMX_8BIT, 0x020E, 0x01},
	{ IMX_8BIT, 0x020F, 0x00},
	{ IMX_8BIT, 0x0210, 0x02},
	{ IMX_8BIT, 0x0211, 0x00},
	{ IMX_8BIT, 0x0212, 0x02},
	{ IMX_8BIT, 0x0213, 0x00},
	{ IMX_8BIT, 0x0214, 0x01},
	{ IMX_8BIT, 0x0215, 0x00},
	/* HDR Setting */
	{ IMX_8BIT, 0x0230, 0x00},
	{ IMX_8BIT, 0x0231, 0x00},
	{ IMX_8BIT, 0x0233, 0x00},
	{ IMX_8BIT, 0x0234, 0x00},
	{ IMX_8BIT, 0x0235, 0x40},
	{ IMX_8BIT, 0x0238, 0x00},
	{ IMX_8BIT, 0x0239, 0x04},
	{ IMX_8BIT, 0x023B, 0x00},
	{ IMX_8BIT, 0x023C, 0x01},
	{ IMX_8BIT, 0x33B0, 0x04},
	{ IMX_8BIT, 0x33B1, 0x00},
	{ IMX_8BIT, 0x33B3, 0x00},
	{ IMX_8BIT, 0x33B4, 0x01},
	{ IMX_8BIT, 0x3800, 0x00},
	GROUPED_PARAMETER_HOLD_DISABLE,
	{ IMX_TOK_TERM, 0, 0}
};

/********* Preview, continuous capture and still modes *****************/

static struct imx_reg const imx135vb_13m[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_451_2MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03},
	{IMX_8BIT, 0x0112, 0x0A},
	{IMX_8BIT, 0x0113, 0x0A},
	{IMX_8BIT, 0x0381, 0x01},
	{IMX_8BIT, 0x0383, 0x01},
	{IMX_8BIT, 0x0385, 0x01},
	{IMX_8BIT, 0x0387, 0x01},
	{IMX_8BIT, 0x0390, 0x00},
	{IMX_8BIT, 0x0391, 0x11},
	{IMX_8BIT, 0x0392, 0x00},
	{IMX_8BIT, 0x0401, 0x00},
	{IMX_8BIT, 0x0404, 0x00},
	{IMX_8BIT, 0x0405, 0x10},
	{IMX_8BIT, 0x4082, 0x01},
	{IMX_8BIT, 0x4083, 0x01},
	{IMX_8BIT, 0x4203, 0xFF},
	{IMX_8BIT, 0x7006, 0x04},
	/* Size Setting */
	{IMX_8BIT, 0x0344, 0x00}, /* 0, 0, 4207,3119 4208x3120 */
	{IMX_8BIT, 0x0345, 0x00},
	{IMX_8BIT, 0x0346, 0x00},
	{IMX_8BIT, 0x0347, 0x00},
	{IMX_8BIT, 0x0348, 0x10},
	{IMX_8BIT, 0x0349, 0x6F},
	{IMX_8BIT, 0x034A, 0x0C},
	{IMX_8BIT, 0x034B, 0x2F},
	{IMX_8BIT, 0x034C, 0x10},
	{IMX_8BIT, 0x034D, 0x70},
	{IMX_8BIT, 0x034E, 0x0C},
	{IMX_8BIT, 0x034F, 0x30},
	{IMX_8BIT, 0x0350, 0x00},
	{IMX_8BIT, 0x0351, 0x00},
	{IMX_8BIT, 0x0352, 0x00},
	{IMX_8BIT, 0x0353, 0x00},
	{IMX_8BIT, 0x0354, 0x10}, /* 4208x3120 */
	{IMX_8BIT, 0x0355, 0x70},
	{IMX_8BIT, 0x0356, 0x0C},
	{IMX_8BIT, 0x0357, 0x30},
	{IMX_8BIT, 0x301D, 0x30},
	{IMX_8BIT, 0x3310, 0x10},
	{IMX_8BIT, 0x3311, 0x70},
	{IMX_8BIT, 0x3312, 0x0C},
	{IMX_8BIT, 0x3313, 0x30},
	{IMX_8BIT, 0x331C, 0x00},
	{IMX_8BIT, 0x331D, 0x10},
	{IMX_8BIT, 0x4084, 0x00}, /* If scaling, Fill this */
	{IMX_8BIT, 0x4085, 0x00},
	{IMX_8BIT, 0x4086, 0x00},
	{IMX_8BIT, 0x4087, 0x00},
	{IMX_8BIT, 0x4400, 0x00},
	{IMX_TOK_TERM, 0, 0},
};

/* 13MP reduced pixel clock MIPI 342MHz is EMC friendly*/
static struct imx_reg const imx135vb_13m_for_mipi_342[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_342MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03},
	{IMX_8BIT, 0x0112, 0x0A},
	{IMX_8BIT, 0x0113, 0x0A},
	{IMX_8BIT, 0x0381, 0x01},
	{IMX_8BIT, 0x0383, 0x01},
	{IMX_8BIT, 0x0385, 0x01},
	{IMX_8BIT, 0x0387, 0x01},
	{IMX_8BIT, 0x0390, 0x00},
	{IMX_8BIT, 0x0391, 0x11},
	{IMX_8BIT, 0x0392, 0x00},
	{IMX_8BIT, 0x0401, 0x00},
	{IMX_8BIT, 0x0404, 0x00},
	{IMX_8BIT, 0x0405, 0x10},
	{IMX_8BIT, 0x4082, 0x01},
	{IMX_8BIT, 0x4083, 0x01},
	{IMX_8BIT, 0x4203, 0xFF},
	{IMX_8BIT, 0x7006, 0x04},
	/* Size Setting */
	{IMX_8BIT, 0x0344, 0x00},
	{IMX_8BIT, 0x0345, 0x00},
	{IMX_8BIT, 0x0346, 0x00},
	{IMX_8BIT, 0x0347, 0x00},
	{IMX_8BIT, 0x0348, 0x10},
	{IMX_8BIT, 0x0349, 0x6F},
	{IMX_8BIT, 0x034A, 0x0C},
	{IMX_8BIT, 0x034B, 0x2F},
	{IMX_8BIT, 0x034C, 0x10},
	{IMX_8BIT, 0x034D, 0x70},
	{IMX_8BIT, 0x034E, 0x0C},
	{IMX_8BIT, 0x034F, 0x30},
	{IMX_8BIT, 0x0350, 0x00},
	{IMX_8BIT, 0x0351, 0x00},
	{IMX_8BIT, 0x0352, 0x00},
	{IMX_8BIT, 0x0353, 0x00},
	{IMX_8BIT, 0x0354, 0x10},
	{IMX_8BIT, 0x0355, 0x70},
	{IMX_8BIT, 0x0356, 0x0C},
	{IMX_8BIT, 0x0357, 0x30},
	{IMX_8BIT, 0x301D, 0x30},
	{IMX_8BIT, 0x3310, 0x10},
	{IMX_8BIT, 0x3311, 0x70},
	{IMX_8BIT, 0x3312, 0x0C},
	{IMX_8BIT, 0x3313, 0x30},
	{IMX_8BIT, 0x331C, 0x00},
	{IMX_8BIT, 0x331D, 0x10},
	{IMX_8BIT, 0x4084, 0x00}, /* If scaling, Fill this */
	{IMX_8BIT, 0x4085, 0x00},
	{IMX_8BIT, 0x4086, 0x00},
	{IMX_8BIT, 0x4087, 0x00},
	{IMX_8BIT, 0x4400, 0x00},
	{IMX_TOK_TERM, 0, 0},
};

static struct imx_reg const imx135vb_10m[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_451_2MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03},
	{IMX_8BIT, 0x0112, 0x0A},
	{IMX_8BIT, 0x0113, 0x0A},
	{IMX_8BIT, 0x0381, 0x01},
	{IMX_8BIT, 0x0383, 0x01},
	{IMX_8BIT, 0x0385, 0x01},
	{IMX_8BIT, 0x0387, 0x01},
	{IMX_8BIT, 0x0390, 0x00},
	{IMX_8BIT, 0x0391, 0x11},
	{IMX_8BIT, 0x0392, 0x00},
	{IMX_8BIT, 0x0401, 0x00},
	{IMX_8BIT, 0x0404, 0x00},
	{IMX_8BIT, 0x0405, 0x10},
	{IMX_8BIT, 0x4082, 0x01},
	{IMX_8BIT, 0x4083, 0x01},
	{IMX_8BIT, 0x4203, 0xFF},
	{IMX_8BIT, 0x7006, 0x04},
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00}, /* 0, 376, 4207, 2743 */
	{IMX_8BIT, 0x0345, 0x00},
	{IMX_8BIT, 0x0346, 0x01},
	{IMX_8BIT, 0x0347, 0x78},
	{IMX_8BIT, 0x0348, 0x10},
	{IMX_8BIT, 0x0349, 0x6f},
	{IMX_8BIT, 0x034A, 0x0a},
	{IMX_8BIT, 0x034B, 0xb7},
	{IMX_8BIT, 0x034C, 0x10}, /* 4208x2368 */
	{IMX_8BIT, 0x034D, 0x70},
	{IMX_8BIT, 0x034E, 0x09},
	{IMX_8BIT, 0x034F, 0x40},
	{IMX_8BIT, 0x0350, 0x00},
	{IMX_8BIT, 0x0351, 0x00},
	{IMX_8BIT, 0x0352, 0x00},
	{IMX_8BIT, 0x0353, 0x00},
	{IMX_8BIT, 0x0354, 0x10},
	{IMX_8BIT, 0x0355, 0x70},
	{IMX_8BIT, 0x0356, 0x09},
	{IMX_8BIT, 0x0357, 0x40},
	{IMX_8BIT, 0x301D, 0x30},
	{IMX_8BIT, 0x3310, 0x10},
	{IMX_8BIT, 0x3311, 0x70},
	{IMX_8BIT, 0x3312, 0x09},
	{IMX_8BIT, 0x3313, 0x40},
	{IMX_8BIT, 0x331C, 0x01},
	{IMX_8BIT, 0x331D, 0x68},
	{IMX_8BIT, 0x4084, 0x00},
	{IMX_8BIT, 0x4085, 0x00},
	{IMX_8BIT, 0x4086, 0x00},
	{IMX_8BIT, 0x4087, 0x00},
	{IMX_8BIT, 0x4400, 0x00},
	{IMX_TOK_TERM, 0, 0},
};

static struct imx_reg const imx135vb_10m_for_mipi_342[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_342MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03},
	{IMX_8BIT, 0x0112, 0x0A},
	{IMX_8BIT, 0x0113, 0x0A},
	{IMX_8BIT, 0x0381, 0x01},
	{IMX_8BIT, 0x0383, 0x01},
	{IMX_8BIT, 0x0385, 0x01},
	{IMX_8BIT, 0x0387, 0x01},
	{IMX_8BIT, 0x0390, 0x00},
	{IMX_8BIT, 0x0391, 0x11},
	{IMX_8BIT, 0x0392, 0x00},
	{IMX_8BIT, 0x0401, 0x00},
	{IMX_8BIT, 0x0404, 0x00},
	{IMX_8BIT, 0x0405, 0x10},
	{IMX_8BIT, 0x4082, 0x01},
	{IMX_8BIT, 0x4083, 0x01},
	{IMX_8BIT, 0x4203, 0xFF},
	{IMX_8BIT, 0x7006, 0x04},
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00}, /* 0, 376, 4207, 2743 */
	{IMX_8BIT, 0x0345, 0x00},
	{IMX_8BIT, 0x0346, 0x01},
	{IMX_8BIT, 0x0347, 0x78},
	{IMX_8BIT, 0x0348, 0x10},
	{IMX_8BIT, 0x0349, 0x6f},
	{IMX_8BIT, 0x034A, 0x0a},
	{IMX_8BIT, 0x034B, 0xb7},
	{IMX_8BIT, 0x034C, 0x10}, /* 4208x2368 */
	{IMX_8BIT, 0x034D, 0x70},
	{IMX_8BIT, 0x034E, 0x09},
	{IMX_8BIT, 0x034F, 0x40},
	{IMX_8BIT, 0x0350, 0x00},
	{IMX_8BIT, 0x0351, 0x00},
	{IMX_8BIT, 0x0352, 0x00},
	{IMX_8BIT, 0x0353, 0x00},
	{IMX_8BIT, 0x0354, 0x10},
	{IMX_8BIT, 0x0355, 0x70},
	{IMX_8BIT, 0x0356, 0x09},
	{IMX_8BIT, 0x0357, 0x40},
	{IMX_8BIT, 0x301D, 0x30},
	{IMX_8BIT, 0x3310, 0x10},
	{IMX_8BIT, 0x3311, 0x70},
	{IMX_8BIT, 0x3312, 0x09},
	{IMX_8BIT, 0x3313, 0x40},
	{IMX_8BIT, 0x331C, 0x01},
	{IMX_8BIT, 0x331D, 0x68},
	{IMX_8BIT, 0x4084, 0x00},
	{IMX_8BIT, 0x4085, 0x00},
	{IMX_8BIT, 0x4086, 0x00},
	{IMX_8BIT, 0x4087, 0x00},
	{IMX_8BIT, 0x4400, 0x00},
	{IMX_TOK_TERM, 0, 0},
};

static struct imx_reg const imx135vb_8m_scaled_from_12m[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_451_2MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03},
	{IMX_8BIT, 0x0112, 0x0A},
	{IMX_8BIT, 0x0113, 0x0A},
	{IMX_8BIT, 0x0381, 0x01},
	{IMX_8BIT, 0x0383, 0x01},
	{IMX_8BIT, 0x0385, 0x01},
	{IMX_8BIT, 0x0387, 0x01},
	{IMX_8BIT, 0x0390, 0x00},
	{IMX_8BIT, 0x0391, 0x11},
	{IMX_8BIT, 0x0392, 0x00},
	{IMX_8BIT, 0x0401, 0x02}, /* Scaling */
	{IMX_8BIT, 0x0404, 0x00},
	{IMX_8BIT, 0x0405, 0x14},
	{IMX_8BIT, 0x4082, 0x00},
	{IMX_8BIT, 0x4083, 0x00},
	{IMX_8BIT, 0x4203, 0xFF},
	{IMX_8BIT, 0x7006, 0x04},
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00},
	{IMX_8BIT, 0x0345, 0x36},
	{IMX_8BIT, 0x0346, 0x00},
	{IMX_8BIT, 0x0347, 0x14},
	{IMX_8BIT, 0x0348, 0x10},
	{IMX_8BIT, 0x0349, 0x39},
	{IMX_8BIT, 0x034A, 0x0C},
	{IMX_8BIT, 0x034B, 0x1B},
	{IMX_8BIT, 0x034C, 0x0C}, /* 3280x2464 */
	{IMX_8BIT, 0x034D, 0xD0},
	{IMX_8BIT, 0x034E, 0x09},
	{IMX_8BIT, 0x034F, 0xA0},
	{IMX_8BIT, 0x0350, 0x00}, /* No Dig crop */
	{IMX_8BIT, 0x0351, 0x00},
	{IMX_8BIT, 0x0352, 0x00},
	{IMX_8BIT, 0x0353, 0x00},
	{IMX_8BIT, 0x0354, 0x10}, /* Cut out size same as the size after crop */
	{IMX_8BIT, 0x0355, 0x04},
	{IMX_8BIT, 0x0356, 0x0C},
	{IMX_8BIT, 0x0357, 0x08},
	{IMX_8BIT, 0x301D, 0x30}, /* ?? */
	{IMX_8BIT, 0x3310, 0x0C}, /* Write H and V size  same as output size? */
	{IMX_8BIT, 0x3311, 0xD0},
	{IMX_8BIT, 0x3312, 0x09},
	{IMX_8BIT, 0x3313, 0xA0},
	{IMX_8BIT, 0x331C, 0x02}, /* ?? */
	{IMX_8BIT, 0x331D, 0xA0},
	{IMX_8BIT, 0x4084, 0x0C}, /* Scaling related? */
	{IMX_8BIT, 0x4085, 0xD0},
	{IMX_8BIT, 0x4086, 0x09},
	{IMX_8BIT, 0x4087, 0xA0},
	{IMX_8BIT, 0x4400, 0x00}, /* STATS off */
	{IMX_TOK_TERM, 0, 0},
};

static struct imx_reg const imx135vb_8m_scaled_from_12m_for_mipi342[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_342MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03},
	{IMX_8BIT, 0x0112, 0x0A},
	{IMX_8BIT, 0x0113, 0x0A},
	{IMX_8BIT, 0x0381, 0x01},
	{IMX_8BIT, 0x0383, 0x01},
	{IMX_8BIT, 0x0385, 0x01},
	{IMX_8BIT, 0x0387, 0x01},
	{IMX_8BIT, 0x0390, 0x00},
	{IMX_8BIT, 0x0391, 0x11},
	{IMX_8BIT, 0x0392, 0x00},
	{IMX_8BIT, 0x0401, 0x02}, /* Scaling */
	{IMX_8BIT, 0x0404, 0x00},
	{IMX_8BIT, 0x0405, 0x14},
	{IMX_8BIT, 0x4082, 0x00},
	{IMX_8BIT, 0x4083, 0x00},
	{IMX_8BIT, 0x4203, 0xFF},
	{IMX_8BIT, 0x7006, 0x04},
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00},
	{IMX_8BIT, 0x0345, 0x36},
	{IMX_8BIT, 0x0346, 0x00},
	{IMX_8BIT, 0x0347, 0x14},
	{IMX_8BIT, 0x0348, 0x10},
	{IMX_8BIT, 0x0349, 0x39},
	{IMX_8BIT, 0x034A, 0x0C},
	{IMX_8BIT, 0x034B, 0x1B},
	{IMX_8BIT, 0x034C, 0x0C}, /* 3280x2464 */
	{IMX_8BIT, 0x034D, 0xD0},
	{IMX_8BIT, 0x034E, 0x09},
	{IMX_8BIT, 0x034F, 0xA0},
	{IMX_8BIT, 0x0350, 0x00}, /* No Dig crop */
	{IMX_8BIT, 0x0351, 0x00},
	{IMX_8BIT, 0x0352, 0x00},
	{IMX_8BIT, 0x0353, 0x00},
	{IMX_8BIT, 0x0354, 0x10}, /* Cut out size same as the size after crop */
	{IMX_8BIT, 0x0355, 0x04},
	{IMX_8BIT, 0x0356, 0x0C},
	{IMX_8BIT, 0x0357, 0x08},
	{IMX_8BIT, 0x301D, 0x30}, /* ?? */
	{IMX_8BIT, 0x3310, 0x0C}, /* Write H and V size  same as output size? */
	{IMX_8BIT, 0x3311, 0xD0},
	{IMX_8BIT, 0x3312, 0x09},
	{IMX_8BIT, 0x3313, 0xA0},
	{IMX_8BIT, 0x331C, 0x02}, /* ?? */
	{IMX_8BIT, 0x331D, 0xA0},
	{IMX_8BIT, 0x4084, 0x0C}, /* Resize IMG Hand V size-> Scaling related?*/
	{IMX_8BIT, 0x4085, 0xD0},
	{IMX_8BIT, 0x4086, 0x09},
	{IMX_8BIT, 0x4087, 0xA0},
	{IMX_8BIT, 0x4400, 0x00}, /* STATS off */
	{IMX_TOK_TERM, 0, 0},
};

static struct imx_reg const imx135vb_6m[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_451_2MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03},
	{IMX_8BIT, 0x0112, 0x0A},
	{IMX_8BIT, 0x0113, 0x0A},
	{IMX_8BIT, 0x0381, 0x01},
	{IMX_8BIT, 0x0383, 0x01},
	{IMX_8BIT, 0x0385, 0x01},
	{IMX_8BIT, 0x0387, 0x01},
	{IMX_8BIT, 0x0390, 0x00},
	{IMX_8BIT, 0x0391, 0x11},
	{IMX_8BIT, 0x0392, 0x00},
	{IMX_8BIT, 0x0401, 0x02},
	{IMX_8BIT, 0x0404, 0x00},
	{IMX_8BIT, 0x0405, 0x14},
	{IMX_8BIT, 0x4082, 0x00},
	{IMX_8BIT, 0x4083, 0x00},
	{IMX_8BIT, 0x4203, 0xFF},
	{IMX_8BIT, 0x7006, 0x04},
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00}, /* 36, 194, 1039, a9f 4100x2316 */
	{IMX_8BIT, 0x0345, 0x36},
	{IMX_8BIT, 0x0346, 0x01},
	{IMX_8BIT, 0x0347, 0x94},
	{IMX_8BIT, 0x0348, 0x10},
	{IMX_8BIT, 0x0349, 0x39},
	{IMX_8BIT, 0x034A, 0x0A},
	{IMX_8BIT, 0x034B, 0x9F},
	{IMX_8BIT, 0x034C, 0x0C}, /* 3280x1852 */
	{IMX_8BIT, 0x034D, 0xD0},
	{IMX_8BIT, 0x034E, 0x07},
	{IMX_8BIT, 0x034F, 0x3C},
	{IMX_8BIT, 0x0350, 0x00},
	{IMX_8BIT, 0x0351, 0x00},
	{IMX_8BIT, 0x0352, 0x00},
	{IMX_8BIT, 0x0353, 0x00},
	{IMX_8BIT, 0x0354, 0x10}, /* 4100x2316 */
	{IMX_8BIT, 0x0355, 0x04},
	{IMX_8BIT, 0x0356, 0x09},
	{IMX_8BIT, 0x0357, 0x0C},
	{IMX_8BIT, 0x301D, 0x30},
	{IMX_8BIT, 0x3310, 0x0C},
	{IMX_8BIT, 0x3311, 0xD0},
	{IMX_8BIT, 0x3312, 0x07},
	{IMX_8BIT, 0x3313, 0x3C},
	{IMX_8BIT, 0x331C, 0x02},
	{IMX_8BIT, 0x331D, 0xA0},
	{IMX_8BIT, 0x4084, 0x0C},
	{IMX_8BIT, 0x4085, 0xD0},
	{IMX_8BIT, 0x4086, 0x07},
	{IMX_8BIT, 0x4087, 0x3C},
	{IMX_8BIT, 0x4400, 0x00},
	{IMX_TOK_TERM, 0, 0},
};

static struct imx_reg const imx135vb_6m_for_mipi_342[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_342MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03},
	{IMX_8BIT, 0x0112, 0x0A},
	{IMX_8BIT, 0x0113, 0x0A},
	{IMX_8BIT, 0x0381, 0x01},
	{IMX_8BIT, 0x0383, 0x01},
	{IMX_8BIT, 0x0385, 0x01},
	{IMX_8BIT, 0x0387, 0x01},
	{IMX_8BIT, 0x0390, 0x00},
	{IMX_8BIT, 0x0391, 0x11},
	{IMX_8BIT, 0x0392, 0x00},
	{IMX_8BIT, 0x0401, 0x02},
	{IMX_8BIT, 0x0404, 0x00},
	{IMX_8BIT, 0x0405, 0x14},
	{IMX_8BIT, 0x4082, 0x00},
	{IMX_8BIT, 0x4083, 0x00},
	{IMX_8BIT, 0x4203, 0xFF},
	{IMX_8BIT, 0x7006, 0x04},
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00}, /* 36, 194, 1039, a9f 4100x2316 */
	{IMX_8BIT, 0x0345, 0x36},
	{IMX_8BIT, 0x0346, 0x01},
	{IMX_8BIT, 0x0347, 0x94},
	{IMX_8BIT, 0x0348, 0x10},
	{IMX_8BIT, 0x0349, 0x39},
	{IMX_8BIT, 0x034A, 0x0A},
	{IMX_8BIT, 0x034B, 0x9F},
	{IMX_8BIT, 0x034C, 0x0C}, /* 3280x1852 */
	{IMX_8BIT, 0x034D, 0xD0},
	{IMX_8BIT, 0x034E, 0x07},
	{IMX_8BIT, 0x034F, 0x3C},
	{IMX_8BIT, 0x0350, 0x00},
	{IMX_8BIT, 0x0351, 0x00},
	{IMX_8BIT, 0x0352, 0x00},
	{IMX_8BIT, 0x0353, 0x00},
	{IMX_8BIT, 0x0354, 0x10}, /* 4100x2316 */
	{IMX_8BIT, 0x0355, 0x04},
	{IMX_8BIT, 0x0356, 0x09},
	{IMX_8BIT, 0x0357, 0x0C},
	{IMX_8BIT, 0x301D, 0x30},
	{IMX_8BIT, 0x3310, 0x0C},
	{IMX_8BIT, 0x3311, 0xD0},
	{IMX_8BIT, 0x3312, 0x07},
	{IMX_8BIT, 0x3313, 0x3C},
	{IMX_8BIT, 0x331C, 0x02},
	{IMX_8BIT, 0x331D, 0xA0},
	{IMX_8BIT, 0x4084, 0x0C},
	{IMX_8BIT, 0x4085, 0xD0},
	{IMX_8BIT, 0x4086, 0x07},
	{IMX_8BIT, 0x4087, 0x3C},
	{IMX_8BIT, 0x4400, 0x00},
	{IMX_TOK_TERM, 0, 0},
};

static struct imx_reg const imx135vb_3m_binning[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_209_6MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03},
	{IMX_8BIT, 0x0112, 0x0A},
	{IMX_8BIT, 0x0113, 0x0A},
	{IMX_8BIT, 0x0381, 0x01},
	{IMX_8BIT, 0x0383, 0x01},
	{IMX_8BIT, 0x0385, 0x01},
	{IMX_8BIT, 0x0387, 0x01},
	{IMX_8BIT, 0x0390, 0x01}, /* Binning */
	{IMX_8BIT, 0x0391, 0x22}, /* 2x2 binning */
	{IMX_8BIT, 0x0392, 0x00}, /* average */
	{IMX_8BIT, 0x0401, 0x00},
	{IMX_8BIT, 0x0404, 0x00},
	{IMX_8BIT, 0x0405, 0x10},
	{IMX_8BIT, 0x4082, 0x01},
	{IMX_8BIT, 0x4083, 0x01},
	{IMX_8BIT, 0x4203, 0xFF},
	{IMX_8BIT, 0x7006, 0x04},
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00},
	{IMX_8BIT, 0x0345, 0x28},
	{IMX_8BIT, 0x0346, 0x00},
	{IMX_8BIT, 0x0347, 0x08},
	{IMX_8BIT, 0x0348, 0x10},
	{IMX_8BIT, 0x0349, 0x47},
	{IMX_8BIT, 0x034A, 0x0C},
	{IMX_8BIT, 0x034B, 0x27},
	{IMX_8BIT, 0x034C, 0x08},
	{IMX_8BIT, 0x034D, 0x10},
	{IMX_8BIT, 0x034E, 0x06},
	{IMX_8BIT, 0x034F, 0x10},
	{IMX_8BIT, 0x0350, 0x00},
	{IMX_8BIT, 0x0351, 0x00},
	{IMX_8BIT, 0x0352, 0x00},
	{IMX_8BIT, 0x0353, 0x00},
	{IMX_8BIT, 0x0354, 0x08},
	{IMX_8BIT, 0x0355, 0x10},
	{IMX_8BIT, 0x0356, 0x06},
	{IMX_8BIT, 0x0357, 0x10},
	{IMX_8BIT, 0x301D, 0x30},
	{IMX_8BIT, 0x3310, 0x08},
	{IMX_8BIT, 0x3311, 0x10},
	{IMX_8BIT, 0x3312, 0x06},
	{IMX_8BIT, 0x3313, 0x10},
	{IMX_8BIT, 0x331C, 0x00},
	{IMX_8BIT, 0x331D, 0xAA},
	{IMX_8BIT, 0x4084, 0x00},
	{IMX_8BIT, 0x4085, 0x00},
	{IMX_8BIT, 0x4086, 0x00},
	{IMX_8BIT, 0x4087, 0x00},
	{IMX_8BIT, 0x4400, 0x00},
	{IMX_TOK_TERM, 0, 0},
};

/* 1080P 1936x1104 */
static struct imx_reg const imx135vb_1080p_binning[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_209_6MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03},
	{IMX_8BIT, 0x0112, 0x0A},
	{IMX_8BIT, 0x0113, 0x0A},
	{IMX_8BIT, 0x0381, 0x01},
	{IMX_8BIT, 0x0383, 0x01},
	{IMX_8BIT, 0x0385, 0x01},
	{IMX_8BIT, 0x0387, 0x01},
	{IMX_8BIT, 0x0390, 0x01},
	{IMX_8BIT, 0x0391, 0x22},
	{IMX_8BIT, 0x0392, 0x00},
	{IMX_8BIT, 0x0401, 0x02},
	{IMX_8BIT, 0x0404, 0x00},
	{IMX_8BIT, 0x0405, 0x11},
	{IMX_8BIT, 0x4082, 0x00},
	{IMX_8BIT, 0x4083, 0x00},
	{IMX_8BIT, 0x7006, 0x04},
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00},
	{IMX_8BIT, 0x0345, 0x2E},
	{IMX_8BIT, 0x0346, 0x01},
	{IMX_8BIT, 0x0347, 0x84},
	{IMX_8BIT, 0x0348, 0x10},
	{IMX_8BIT, 0x0349, 0x41},
	{IMX_8BIT, 0x034A, 0x0A},
	{IMX_8BIT, 0x034B, 0xAF},
	{IMX_8BIT, 0x034C, 0x07},
	{IMX_8BIT, 0x034D, 0x90},
	{IMX_8BIT, 0x034E, 0x04},
	{IMX_8BIT, 0x034F, 0x50},
	{IMX_8BIT, 0x0350, 0x00},
	{IMX_8BIT, 0x0351, 0x00},
	{IMX_8BIT, 0x0352, 0x00},
	{IMX_8BIT, 0x0353, 0x00},
	{IMX_8BIT, 0x0354, 0x08},
	{IMX_8BIT, 0x0355, 0x0A},
	{IMX_8BIT, 0x0356, 0x04},
	{IMX_8BIT, 0x0357, 0x96},
	{IMX_8BIT, 0x301D, 0x30},
	{IMX_8BIT, 0x3310, 0x07},
	{IMX_8BIT, 0x3311, 0x90},
	{IMX_8BIT, 0x3312, 0x04},
	{IMX_8BIT, 0x3313, 0x50},
	{IMX_8BIT, 0x331C, 0x01},
	{IMX_8BIT, 0x331D, 0x00},
	{IMX_8BIT, 0x4084, 0x07},
	{IMX_8BIT, 0x4085, 0x90},
	{IMX_8BIT, 0x4086, 0x04},
	{IMX_8BIT, 0x4087, 0x50},
	{IMX_8BIT, 0x4400, 0x00},
	{IMX_TOK_TERM, 0, 0},
};

/******************* Video Modes ******************/

/* 1080P DVS 2336x1320 */
static const struct imx_reg imx135vb_2336x1320_max_clock[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_451_2MHZ,
	/* mode setting */
	{ IMX_8BIT, 0x0108, 0x03 },
	{ IMX_8BIT, 0x0112, 0x0A },
	{ IMX_8BIT, 0x0113, 0x0A },
	{ IMX_8BIT, 0x0381, 0x01 },
	{ IMX_8BIT, 0x0383, 0x01 },
	{ IMX_8BIT, 0x0385, 0x01 },
	{ IMX_8BIT, 0x0387, 0x01 },
	{ IMX_8BIT, 0x0390, 0x00 },
	{ IMX_8BIT, 0x0391, 0x11 },
	{ IMX_8BIT, 0x0392, 0x00 },
	{ IMX_8BIT, 0x0401, 0x02 },
	{ IMX_8BIT, 0x0404, 0x00 },
	{ IMX_8BIT, 0x0405, 0x1C },
	{ IMX_8BIT, 0x4082, 0x00 },
	{ IMX_8BIT, 0x4083, 0x00 },
	{ IMX_8BIT, 0x7006, 0x04 },
	/* size setting */
	{ IMX_8BIT, 0x0344, 0x00 }, /* 60,404,4147,2715: 4088x2312 */
	{ IMX_8BIT, 0x0345, 0x3C },
	{ IMX_8BIT, 0x0346, 0x01 },
	{ IMX_8BIT, 0x0347, 0x94 },
	{ IMX_8BIT, 0x0348, 0x10 },
	{ IMX_8BIT, 0x0349, 0x33 },
	{ IMX_8BIT, 0x034A, 0x0A },
	{ IMX_8BIT, 0x034B, 0x9B },
	{ IMX_8BIT, 0x034C, 0x09 }, /*2336 x 1320 */
	{ IMX_8BIT, 0x034D, 0x20 },
	{ IMX_8BIT, 0x034E, 0x05 },
	{ IMX_8BIT, 0x034F, 0x28 },
	{ IMX_8BIT, 0x0350, 0x00 },
	{ IMX_8BIT, 0x0351, 0x00 },
	{ IMX_8BIT, 0x0352, 0x00 },
	{ IMX_8BIT, 0x0353, 0x00 },
	{ IMX_8BIT, 0x0354, 0x0F }, /* 4088x2312 */
	{ IMX_8BIT, 0x0355, 0xF8 },
	{ IMX_8BIT, 0x0356, 0x09 },
	{ IMX_8BIT, 0x0357, 0x08 },
	{ IMX_8BIT, 0x301D, 0x30 },
	{ IMX_8BIT, 0x3310, 0x09 },
	{ IMX_8BIT, 0x3311, 0x20 },
	{ IMX_8BIT, 0x3312, 0x05 },
	{ IMX_8BIT, 0x3313, 0x28 },
	{ IMX_8BIT, 0x331C, 0x04 },
	{ IMX_8BIT, 0x331D, 0xE2 },
	{ IMX_8BIT, 0x4084, 0x09 },
	{ IMX_8BIT, 0x4085, 0x20 },
	{ IMX_8BIT, 0x4086, 0x05 },
	{ IMX_8BIT, 0x4087, 0x28 },
	{ IMX_8BIT, 0x4400, 0x00 },
	{ IMX_TOK_TERM, 0, 0}
};

/* 720P DVS 1568 x 880 */
static const struct imx_reg imx135vb_720p_dvs_binning[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_209_6MHZ,
	/* mode setting */
	{ IMX_8BIT, 0x0108, 0x03 },
	{ IMX_8BIT, 0x0112, 0x0A },
	{ IMX_8BIT, 0x0113, 0x0A },
	{ IMX_8BIT, 0x0381, 0x01 },
	{ IMX_8BIT, 0x0383, 0x01 },
	{ IMX_8BIT, 0x0385, 0x01 },
	{ IMX_8BIT, 0x0387, 0x01 },
	{ IMX_8BIT, 0x0390, 0x01 },
	{ IMX_8BIT, 0x0391, 0x22 },
	{ IMX_8BIT, 0x0392, 0x00 },
	{ IMX_8BIT, 0x0401, 0x02 },
	{ IMX_8BIT, 0x0404, 0x00 },
	{ IMX_8BIT, 0x0405, 0x15 },
	{ IMX_8BIT, 0x4082, 0x00 },
	{ IMX_8BIT, 0x4083, 0x00 },
	{ IMX_8BIT, 0x7006, 0x04 },
	/* size setting */
	{ IMX_8BIT, 0x0344, 0x00 }, /* 46,404,4161,2715: 4116x2312 */
	{ IMX_8BIT, 0x0345, 0x2e },
	{ IMX_8BIT, 0x0346, 0x01 },
	{ IMX_8BIT, 0x0347, 0x94 },
	{ IMX_8BIT, 0x0348, 0x10 },
	{ IMX_8BIT, 0x0349, 0x41 },
	{ IMX_8BIT, 0x034A, 0x0A },
	{ IMX_8BIT, 0x034B, 0x9B },
	{ IMX_8BIT, 0x034C, 0x06 }, /*1568 x 880 */
	{ IMX_8BIT, 0x034D, 0x20 },
	{ IMX_8BIT, 0x034E, 0x03 },
	{ IMX_8BIT, 0x034F, 0x70 },
	{ IMX_8BIT, 0x0350, 0x00 },
	{ IMX_8BIT, 0x0351, 0x00 },
	{ IMX_8BIT, 0x0352, 0x00 },
	{ IMX_8BIT, 0x0353, 0x00 },
	{ IMX_8BIT, 0x0354, 0x08 }, /* 2058x1156 */
	{ IMX_8BIT, 0x0355, 0x0a },
	{ IMX_8BIT, 0x0356, 0x04 },
	{ IMX_8BIT, 0x0357, 0x84 },
	{ IMX_8BIT, 0x301D, 0x30 }, /* TODO! */
	{ IMX_8BIT, 0x3310, 0x06 },
	{ IMX_8BIT, 0x3311, 0x20 },
	{ IMX_8BIT, 0x3312, 0x03 },
	{ IMX_8BIT, 0x3313, 0x70 },
	{ IMX_8BIT, 0x331C, 0x01 }, /* TODO! */
	{ IMX_8BIT, 0x331D, 0xd6 }, /* TODO! */
	{ IMX_8BIT, 0x4084, 0x06 },
	{ IMX_8BIT, 0x4085, 0x20 },
	{ IMX_8BIT, 0x4086, 0x03 },
	{ IMX_8BIT, 0x4087, 0x70 },
	{ IMX_8BIT, 0x4400, 0x00 },
	{ IMX_TOK_TERM, 0, 0}
};

/* wvga: H : 1640 V : 1024 */
static const struct imx_reg imx135vb_wvga_dvs_binning[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_209_6MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03 },
	{IMX_8BIT, 0x0112, 0x0A },
	{IMX_8BIT, 0x0113, 0x0A },
	{IMX_8BIT, 0x0381, 0x01 },
	{IMX_8BIT, 0x0383, 0x01 },
	{IMX_8BIT, 0x0385, 0x01 },
	{IMX_8BIT, 0x0387, 0x01 },
	{IMX_8BIT, 0x0390, 0x01 },
	{IMX_8BIT, 0x0391, 0x22 },
	{IMX_8BIT, 0x0392, 0x00 },
	{IMX_8BIT, 0x0401, 0x02 },
	{IMX_8BIT, 0x0404, 0x00 },
	{IMX_8BIT, 0x0405, 0x14 },
	{IMX_8BIT, 0x4082, 0x00 },
	{IMX_8BIT, 0x4083, 0x00 },
	{IMX_8BIT, 0x7006, 0x04 },
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00 },
	{IMX_8BIT, 0x0345, 0x36 },
	{IMX_8BIT, 0x0346, 0x01 },
	{IMX_8BIT, 0x0347, 0x18 },
	{IMX_8BIT, 0x0348, 0x10 },
	{IMX_8BIT, 0x0349, 0x39 },
	{IMX_8BIT, 0x034A, 0x0B },
	{IMX_8BIT, 0x034B, 0x17 },
	{IMX_8BIT, 0x034C, 0x06 },
	{IMX_8BIT, 0x034D, 0x68 },
	{IMX_8BIT, 0x034E, 0x04 },
	{IMX_8BIT, 0x034F, 0x00 },
	{IMX_8BIT, 0x0350, 0x00 },
	{IMX_8BIT, 0x0351, 0x00 },
	{IMX_8BIT, 0x0352, 0x00 },
	{IMX_8BIT, 0x0353, 0x00 },
	{IMX_8BIT, 0x0354, 0x08 },
	{IMX_8BIT, 0x0355, 0x02 },
	{IMX_8BIT, 0x0356, 0x05 },
	{IMX_8BIT, 0x0357, 0x00 },
	{IMX_8BIT, 0x301D, 0x30 },
	{IMX_8BIT, 0x3310, 0x06 },
	{IMX_8BIT, 0x3311, 0x68 },
	{IMX_8BIT, 0x3312, 0x04 },
	{IMX_8BIT, 0x3313, 0x00 },
	{IMX_8BIT, 0x331C, 0x01 },
	{IMX_8BIT, 0x331D, 0xBD },
	{IMX_8BIT, 0x4084, 0x06 },
	{IMX_8BIT, 0x4085, 0x68 },
	{IMX_8BIT, 0x4086, 0x04 },
	{IMX_8BIT, 0x4087, 0x00 },
	{IMX_8BIT, 0x4400, 0x00 },
	{IMX_TOK_TERM, 0, 0}
};

/* 480P DVS 936 x 602 */
static const struct imx_reg imx135vb_480p_dvs_binning[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_209_6MHZ,
	/* mode setting */
	{ IMX_8BIT, 0x0108, 0x03 },
	{ IMX_8BIT, 0x0112, 0x0A },
	{ IMX_8BIT, 0x0113, 0x0A },
	{ IMX_8BIT, 0x0381, 0x01 },
	{ IMX_8BIT, 0x0383, 0x01 },
	{ IMX_8BIT, 0x0385, 0x01 },
	{ IMX_8BIT, 0x0387, 0x01 },
	{ IMX_8BIT, 0x0390, 0x01 },
	{ IMX_8BIT, 0x0391, 0x22 },
	{ IMX_8BIT, 0x0392, 0x00 },
	{ IMX_8BIT, 0x0401, 0x02 },
	{ IMX_8BIT, 0x0404, 0x00 },
	{ IMX_8BIT, 0x0405, 0x23 },
	{ IMX_8BIT, 0x4082, 0x00 },
	{ IMX_8BIT, 0x4083, 0x00 },
	{ IMX_8BIT, 0x7006, 0x04 },
	/* size setting */
	{ IMX_8BIT, 0x0344, 0x00 }, /* 56,244,4151,2877: 4096x2634 */
	{ IMX_8BIT, 0x0345, 0x38 },
	{ IMX_8BIT, 0x0346, 0x00 },
	{ IMX_8BIT, 0x0347, 0xf4 },
	{ IMX_8BIT, 0x0348, 0x10 },
	{ IMX_8BIT, 0x0349, 0x37 },
	{ IMX_8BIT, 0x034A, 0x0b },
	{ IMX_8BIT, 0x034B, 0x3d },
	{ IMX_8BIT, 0x034C, 0x03 }, /* 936 x 602 */
	{ IMX_8BIT, 0x034D, 0xa8 },
	{ IMX_8BIT, 0x034E, 0x02 },
	{ IMX_8BIT, 0x034F, 0x5a },
	{ IMX_8BIT, 0x0350, 0x00 },
	{ IMX_8BIT, 0x0351, 0x00 },
	{ IMX_8BIT, 0x0352, 0x00 },
	{ IMX_8BIT, 0x0353, 0x00 },
	{ IMX_8BIT, 0x0354, 0x08 }, /* 2058x1156 */
	{ IMX_8BIT, 0x0355, 0x00 },
	{ IMX_8BIT, 0x0356, 0x05 },
	{ IMX_8BIT, 0x0357, 0x25 },
	{ IMX_8BIT, 0x301D, 0x30 }, /* TODO! */
	{ IMX_8BIT, 0x3310, 0x03 },
	{ IMX_8BIT, 0x3311, 0xa8 },
	{ IMX_8BIT, 0x3312, 0x02 },
	{ IMX_8BIT, 0x3313, 0x5a },
	{ IMX_8BIT, 0x331C, 0x01 }, /* TODO! */
	{ IMX_8BIT, 0x331D, 0xd6 },
	{ IMX_8BIT, 0x4084, 0x03 },
	{ IMX_8BIT, 0x4085, 0xa8 },
	{ IMX_8BIT, 0x4086, 0x02 },
	{ IMX_8BIT, 0x4087, 0x5a },
	{ IMX_8BIT, 0x4400, 0x00 },
	{ IMX_TOK_TERM, 0, 0}
};

/* VGA: H : 820 V : 616 */
static const struct imx_reg imx135vb_vga_dvs_binning[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_209_6MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03 },
	{IMX_8BIT, 0x0112, 0x0A },
	{IMX_8BIT, 0x0113, 0x0A },
	{IMX_8BIT, 0x0381, 0x01 },
	{IMX_8BIT, 0x0383, 0x01 },
	{IMX_8BIT, 0x0385, 0x01 },
	{IMX_8BIT, 0x0387, 0x01 },
	{IMX_8BIT, 0x0390, 0x01 },
	{IMX_8BIT, 0x0391, 0x44 },
	{IMX_8BIT, 0x0392, 0x00 },
	{IMX_8BIT, 0x0401, 0x02 },
	{IMX_8BIT, 0x0404, 0x00 },
	{IMX_8BIT, 0x0405, 0x14 },
	{IMX_8BIT, 0x4082, 0x00 },
	{IMX_8BIT, 0x4083, 0x00 },
	{IMX_8BIT, 0x7006, 0x04 },
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00 }, /* 52,20,4155, 3099 4104x3080*/
	{IMX_8BIT, 0x0345, 0x34 },
	{IMX_8BIT, 0x0346, 0x00 },
	{IMX_8BIT, 0x0347, 0x14 },
	{IMX_8BIT, 0x0348, 0x10 },
	{IMX_8BIT, 0x0349, 0x3B },
	{IMX_8BIT, 0x034A, 0x0C },
	{IMX_8BIT, 0x034B, 0x1B },
	{IMX_8BIT, 0x034C, 0x03 }, /* 820x616 */
	{IMX_8BIT, 0x034D, 0x34 },
	{IMX_8BIT, 0x034E, 0x02 },
	{IMX_8BIT, 0x034F, 0x68 },
	{IMX_8BIT, 0x0350, 0x00 },
	{IMX_8BIT, 0x0351, 0x00 },
	{IMX_8BIT, 0x0352, 0x00 },
	{IMX_8BIT, 0x0353, 0x00 },
	{IMX_8BIT, 0x0354, 0x04 }, /* 1026x770 */
	{IMX_8BIT, 0x0355, 0x02 },
	{IMX_8BIT, 0x0356, 0x03 },
	{IMX_8BIT, 0x0357, 0x02 },
	{IMX_8BIT, 0x301D, 0x30 },
	{IMX_8BIT, 0x3310, 0x03 },
	{IMX_8BIT, 0x3311, 0x34 },
	{IMX_8BIT, 0x3312, 0x02 },
	{IMX_8BIT, 0x3313, 0x68 },
	{IMX_8BIT, 0x331C, 0x02 },
	{IMX_8BIT, 0x331D, 0x21 },
	{IMX_8BIT, 0x4084, 0x03 },
	{IMX_8BIT, 0x4085, 0x34 },
	{IMX_8BIT, 0x4086, 0x02 },
	{IMX_8BIT, 0x4087, 0x68 },
	{IMX_8BIT, 0x4400, 0x00 },
	{IMX_TOK_TERM, 0, 0}
};

/* QVGA: H : 408 V : 308 */
static const struct imx_reg imx135vb_qvga__dvs_binning[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_209_6MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03 },
	{IMX_8BIT, 0x0112, 0x0A },
	{IMX_8BIT, 0x0113, 0x0A },
	{IMX_8BIT, 0x0381, 0x01 },
	{IMX_8BIT, 0x0383, 0x01 },
	{IMX_8BIT, 0x0385, 0x01 },
	{IMX_8BIT, 0x0387, 0x01 },
	{IMX_8BIT, 0x0390, 0x01 },
	{IMX_8BIT, 0x0391, 0x44 },
	{IMX_8BIT, 0x0392, 0x00 },
	{IMX_8BIT, 0x0401, 0x02 },
	{IMX_8BIT, 0x0404, 0x00 },
	{IMX_8BIT, 0x0405, 0x28 },
	{IMX_8BIT, 0x4082, 0x00 },
	{IMX_8BIT, 0x4083, 0x00 },
	{IMX_8BIT, 0x7006, 0x04 },
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00 }, /* 64,20,4143,3099 4080x3080 */
	{IMX_8BIT, 0x0345, 0x40 },
	{IMX_8BIT, 0x0346, 0x00 },
	{IMX_8BIT, 0x0347, 0x14 },
	{IMX_8BIT, 0x0348, 0x10 },
	{IMX_8BIT, 0x0349, 0x2F },
	{IMX_8BIT, 0x034A, 0x0C },
	{IMX_8BIT, 0x034B, 0x1B },
	{IMX_8BIT, 0x034C, 0x01 }, /* 408x308 */
	{IMX_8BIT, 0x034D, 0x98 },
	{IMX_8BIT, 0x034E, 0x01 },
	{IMX_8BIT, 0x034F, 0x34 },
	{IMX_8BIT, 0x0350, 0x00 },
	{IMX_8BIT, 0x0351, 0x00 },
	{IMX_8BIT, 0x0352, 0x00 },
	{IMX_8BIT, 0x0353, 0x00 },
	{IMX_8BIT, 0x0354, 0x03 }, /* 1020x770 */
	{IMX_8BIT, 0x0355, 0xFC },
	{IMX_8BIT, 0x0356, 0x03 },
	{IMX_8BIT, 0x0357, 0x02 },
	{IMX_8BIT, 0x301D, 0x30 },
	{IMX_8BIT, 0x3310, 0x01 },
	{IMX_8BIT, 0x3311, 0x98 },
	{IMX_8BIT, 0x3312, 0x01 },
	{IMX_8BIT, 0x3313, 0x34 },
	{IMX_8BIT, 0x331C, 0x01 },
	{IMX_8BIT, 0x331D, 0x68 },
	{IMX_8BIT, 0x4084, 0x01 },
	{IMX_8BIT, 0x4085, 0x98 },
	{IMX_8BIT, 0x4086, 0x01 },
	{IMX_8BIT, 0x4087, 0x34 },
	{IMX_8BIT, 0x4400, 0x00 },
	{IMX_TOK_TERM, 0, 0}
};

/* CIF H : 368 V : 304 */
static const struct imx_reg imx135vb_cif_binning[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_209_6MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03 },
	{IMX_8BIT, 0x0112, 0x0A },
	{IMX_8BIT, 0x0113, 0x0A },
	{IMX_8BIT, 0x0381, 0x01 },
	{IMX_8BIT, 0x0383, 0x01 },
	{IMX_8BIT, 0x0385, 0x01 },
	{IMX_8BIT, 0x0387, 0x01 },
	{IMX_8BIT, 0x0390, 0x01 },
	{IMX_8BIT, 0x0391, 0x44 },
	{IMX_8BIT, 0x0392, 0x00 },
	{IMX_8BIT, 0x0401, 0x02 },
	{IMX_8BIT, 0x0404, 0x00 },
	{IMX_8BIT, 0x0405, 0x28 },
	{IMX_8BIT, 0x4082, 0x00 },
	{IMX_8BIT, 0x4083, 0x00 },
	{IMX_8BIT, 0x7006, 0x04 },
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x01 }, /* 264,42,3943,3081 3680x3040 */
	{IMX_8BIT, 0x0345, 0x08 },
	{IMX_8BIT, 0x0346, 0x00 },
	{IMX_8BIT, 0x0347, 0x2a },
	{IMX_8BIT, 0x0348, 0x0F },
	{IMX_8BIT, 0x0349, 0x67 },
	{IMX_8BIT, 0x034A, 0x0c },
	{IMX_8BIT, 0x034B, 0x09 },
	{IMX_8BIT, 0x034C, 0x01 }, /* 368x304 */
	{IMX_8BIT, 0x034D, 0x70 },
	{IMX_8BIT, 0x034E, 0x01 },
	{IMX_8BIT, 0x034F, 0x30 },
	{IMX_8BIT, 0x0350, 0x00 },
	{IMX_8BIT, 0x0351, 0x00 },
	{IMX_8BIT, 0x0352, 0x00 },
	{IMX_8BIT, 0x0353, 0x00 },
	{IMX_8BIT, 0x0354, 0x03 }, /* 920x760 */
	{IMX_8BIT, 0x0355, 0x98 },
	{IMX_8BIT, 0x0356, 0x02 },
	{IMX_8BIT, 0x0357, 0xf8 },
	{IMX_8BIT, 0x301D, 0x30 },
	{IMX_8BIT, 0x3310, 0x01 },
	{IMX_8BIT, 0x3311, 0x70 },
	{IMX_8BIT, 0x3312, 0x01 },
	{IMX_8BIT, 0x3313, 0x30 },
	{IMX_8BIT, 0x331C, 0x02 }, /* TODO! binning 4x4 must be 021c? */
	{IMX_8BIT, 0x331D, 0x1C },
	{IMX_8BIT, 0x4084, 0x01 },
	{IMX_8BIT, 0x4085, 0x70 },
	{IMX_8BIT, 0x4086, 0x01 },
	{IMX_8BIT, 0x4087, 0x30 },
	{IMX_8BIT, 0x4400, 0x00 },
	{IMX_TOK_TERM, 0, 0}
};

/* QCIF H : 216 V : 176 */
static const struct imx_reg imx135vb_qcif_dvs_binning[] = {
	GROUPED_PARAMETER_HOLD_ENABLE,
	PLL_SETTINGS_FOR_MIPI_209_6MHZ,
	/* Mode setting */
	{IMX_8BIT, 0x0108, 0x03 },
	{IMX_8BIT, 0x0112, 0x0A },
	{IMX_8BIT, 0x0113, 0x0A },
	{IMX_8BIT, 0x0381, 0x01 },
	{IMX_8BIT, 0x0383, 0x01 },
	{IMX_8BIT, 0x0385, 0x01 },
	{IMX_8BIT, 0x0387, 0x01 },
	{IMX_8BIT, 0x0390, 0x01 },
	{IMX_8BIT, 0x0391, 0x44 },
	{IMX_8BIT, 0x0392, 0x00 },
	{IMX_8BIT, 0x0401, 0x02 },
	{IMX_8BIT, 0x0404, 0x00 },
	{IMX_8BIT, 0x0405, 0x46 },
	{IMX_8BIT, 0x4082, 0x00 },
	{IMX_8BIT, 0x4083, 0x00 },
	{IMX_8BIT, 0x7006, 0x04 },
	/* Size setting */
	{IMX_8BIT, 0x0344, 0x00 }, /* 212,20,3995,3099 3784x3080 */
	{IMX_8BIT, 0x0345, 0xD4 },
	{IMX_8BIT, 0x0346, 0x00 },
	{IMX_8BIT, 0x0347, 0x14 },
	{IMX_8BIT, 0x0348, 0x0F },
	{IMX_8BIT, 0x0349, 0x9B },
	{IMX_8BIT, 0x034A, 0x0C },
	{IMX_8BIT, 0x034B, 0x1B },
	{IMX_8BIT, 0x034C, 0x00 }, /* 216x176 */
	{IMX_8BIT, 0x034D, 0xD8 },
	{IMX_8BIT, 0x034E, 0x00 },
	{IMX_8BIT, 0x034F, 0xB0 },
	{IMX_8BIT, 0x0350, 0x00 },
	{IMX_8BIT, 0x0351, 0x00 },
	{IMX_8BIT, 0x0352, 0x00 },
	{IMX_8BIT, 0x0353, 0x00 },
	{IMX_8BIT, 0x0354, 0x03 }, /* 946x770 */
	{IMX_8BIT, 0x0355, 0xB2 },
	{IMX_8BIT, 0x0356, 0x03 },
	{IMX_8BIT, 0x0357, 0x02 },
	{IMX_8BIT, 0x301D, 0x30 },
	{IMX_8BIT, 0x3310, 0x00 },
	{IMX_8BIT, 0x3311, 0xD8 },
	{IMX_8BIT, 0x3312, 0x00 },
	{IMX_8BIT, 0x3313, 0xB0 },
	{IMX_8BIT, 0x331C, 0x02 }, /* TODO! binning 4x4 must be 021c */
	{IMX_8BIT, 0x331D, 0x1C },
	{IMX_8BIT, 0x4084, 0x00 },
	{IMX_8BIT, 0x4085, 0xD8 },
	{IMX_8BIT, 0x4086, 0x00 },
	{IMX_8BIT, 0x4087, 0xB0 },
	{IMX_8BIT, 0x4400, 0x00 },
	{IMX_TOK_TERM, 0, 0}
};

/*
 * ISP Scaling is now supported in offine capture use cases. Because of that
 * we need only few modes to cover the different aspect ratios from the
 * sensor and the ISP will scale it based on the requested resolution from HAL.
 *
 * There is a performance impact when continuous view finder option is chose
 * for resolutions above 8MP. So 8MP and 6MP resolution are kept, so that lower
 * than these take 8MP or 6MP espectively for down scaling based on the
 * aspect ratio.
 */
struct imx_resolution imx135vb_res_preview[] = {
	{
		.desc = "imx135vb_cif_binning_preview",
		.regs = imx135vb_cif_binning,
		.width = 368,
		.height = 304,
		.fps = 30,
		.pixels_per_line = 9114, /* Binning Pixel clock: 335.36MHz */
		.lines_per_frame = 1226,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
	},
	{
		 .desc = "imx135vb_480p_binning_preview",
		 .regs = imx135vb_480p_dvs_binning,
		 .width = 936,
		 .height = 602,
		 .fps = 30,
		 .pixels_per_line = 5464, /* Binning Pixel clock: 335.36MHz */
		 .lines_per_frame = 2046,
		 .bin_factor_x = 1,
		 .bin_factor_y = 1,
	},
	{
		.desc = "imx135vb_1080p_binning_preview",
		.regs = imx135vb_1080p_binning,
		.width = 1936,
		.height = 1104,
		.fps = 30,
		.pixels_per_line = 5464, /* Binning Pixel clock: 335.36MHz */
		.lines_per_frame = 2046,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.used = 0,
	},
	{
		.desc = "imx135vb_3m__cont_cap",
		.regs = imx135vb_3m_binning,
		.width = 2064,
		.height = 1552,
		.fps = 30,
		.pixels_per_line = 5464, /* Binning Pixel clock: 335.36MHz */
		.lines_per_frame = 2046,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.used = 0,
	},
	{
		.desc = "imx135vb_6m_cont_cap",
		.regs = imx135vb_6m,
		.width = 3280,
		.height = 1852,
		.fps = 30,
		.pixels_per_line = 4572, /* Pixel Clock : 360.96 MHz */
		.lines_per_frame = 2624,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.used = 0,
	},
	{
		.desc = "imx135vb_8m_scaled_from_12m__cont_cap",
		.regs = imx135vb_8m_scaled_from_12m,
		.width = 3280,
		.height = 2464,
		.fps = 24,
		.pixels_per_line = 4572, /* Pixel Clock : 360.96 MHz */
		.lines_per_frame = 3280,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.used = 0,
	},
	{
		.desc = "imx135vb_10m__cont_cap",
		.regs = imx135vb_10m,
		.width = 4208,
		.height = 2368,
		.fps = 30,
		.pixels_per_line = 4572, /* Pixel Clock : 360.96 MHz */
		.lines_per_frame = 2632,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.used = 0,
	},
	{
		.desc = "imx135vb_13m__cont_cap",
		.regs = imx135vb_13m,
		.width = 4208,
		.height = 3120,
		.fps = 24,
		.pixels_per_line = 4572, /* Pixel Clock : 360.96 MHz */
		.lines_per_frame = 3290,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.used = 0,
	},
};

/*
 * ISP Scaling is now supported in online capture use cases. Because of that
 * we need only few modes to cover the different aspect ratios from the
 * sensor and the ISP will scale it based on the requested resolution from HAL.
 *
 * There is a performance impact when continuous view finder option is chose
 * for resolutions above 8MP. So 8MP and 6MP resolution are kept, so that lower
 * than these take 8MP or 6MP espectively for down scaling based on the
 * aspect ratio.
 */
struct imx_resolution imx135vb_res_still[] = {
	{
		.desc = "imx135vb_cif_binning_preview",
		.regs = imx135vb_cif_binning,
		.width = 368,
		.height = 304,
		.fps = 30,
		.pixels_per_line = 9114, /* Binning Pixel clock: 335.36MHz */
		.lines_per_frame = 1226,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
	},
	{
		 .desc = "imx135vb_480p_binning_still",
		 .regs = imx135vb_480p_dvs_binning,
		 .width = 936,
		 .height = 602,
		 .fps = 30,
		 .pixels_per_line = 9114, /* Binning Pixel clock: 335.36MHz */
		 .lines_per_frame = 2453,
		 .bin_factor_x = 1,
		 .bin_factor_y = 1,
	},
	{
		.desc = "imx135vb_1080p_binning_still",
		.regs = imx135vb_1080p_binning,
		.width = 1936,
		.height = 1104,
		.fps = 15,
		.pixels_per_line = 9114, /* Binning Pixel clock: 335.36MHz */
		.lines_per_frame = 2453,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.used = 0,
	},
	{
		.desc = "imx135vb_3m__still",
		.regs = imx135vb_3m_binning,
		.width = 2064,
		.height = 1552,
		.fps = 15,
		.pixels_per_line = 9114, /* Binning Pixel clock: 335.36MHz */
		.lines_per_frame = 2453,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
		.used = 0,
	},
	{
		.desc = "imx135vb_6m_for_mipi_342_still",
		.regs = imx135vb_6m_for_mipi_342,
		.width = 3280,
		.height = 1852,
		.fps = 11,
		.pixels_per_line = 9144, /* pixel clock @ 273.6MHz */
		.lines_per_frame = 2664,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.used = 0,
	},
	{
		.desc = "imx135vb_8m_scaled_from_12m_for_mipi342_still",
		.regs = imx135vb_8m_scaled_from_12m_for_mipi342,
		.width = 3280,
		.height = 2464,
		.fps = 15,
		.pixels_per_line = 5500, /* pixel clock @ 273.6MHz */
		.lines_per_frame = 3314,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.used = 0,
	},
	{
		.desc = "imx135vb_10m_for_mipi_342_still",
		.regs = imx135vb_10m_for_mipi_342,
		.width = 4208,
		.height = 2368,
		.fps = 11,
		.pixels_per_line = 9144, /* pixel clock @ 273.6MHz */
		.lines_per_frame = 2664,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.used = 0,
	},
	{
		.desc = "imx135vb_13m_still",
		.regs = imx135vb_13m_for_mipi_342,
		.width = 4208,
		.height = 3120,
		.fps = 9,
		.pixels_per_line = 9144, /* pixel clock @ 273.6MHz */
		.lines_per_frame = 3328,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
		.used = 0,
	},
};

/*
 * ISP scaling is not supported in case of video modes. So we need to have
 * separate sensor mode for video use cases
 */
struct imx_resolution imx135vb_res_video[] = {
	/* For binning modes pix clock is 335.36 MHz. */
	{
		.desc = "imx135vb_qcif_dvs_binning_video",
		.regs = imx135vb_qcif_dvs_binning,
		.width = 216,
		.height = 176,
		.fps = 30,
		.pixels_per_line = 9114,
		.lines_per_frame = 1226,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
	},
	{
		.desc = "imx135vb_cif_binning_video",
		.regs = imx135vb_cif_binning,
		.width = 368,
		.height = 304,
		.fps = 30,
		.pixels_per_line = 9114,
		.lines_per_frame = 1226,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
	},
	{
		.desc = "imx135vb_qvga__dvs_binning_video",
		.regs = imx135vb_qvga__dvs_binning,
		.width = 408,
		.height = 308,
		.fps = 30,
		.pixels_per_line = 9114,
		.lines_per_frame = 1226,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
	},
	{
		.desc = "imx135vb_vga_dvs_binning_video",
		.regs = imx135vb_vga_dvs_binning,
		.width = 820,
		.height = 616,
		.fps = 30,
		.pixels_per_line = 9114,
		.lines_per_frame = 1226,
		.bin_factor_x = 2,
		.bin_factor_y = 2,
	},
	{
		.desc = "imx135vb_480p_dvs_binning_video",
		.regs = imx135vb_480p_dvs_binning,
		.width = 936,
		.height = 602,
		.fps = 30,
		.pixels_per_line = 5464,
		.lines_per_frame = 2046,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
	},
	{
		.desc = "imx135vb_720p_dvs_binning_video",
		.regs = imx135vb_720p_dvs_binning,
		.width = 1568,
		.height = 880,
		.fps = 30,
		.pixels_per_line = 5464,
		.lines_per_frame = 2046,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
	},
	{
		.desc = "imx135_wvga_dvs_binning_video",
		.regs = imx135vb_wvga_dvs_binning,
		.width = 1640,
		.height = 1024,
		.fps = 30,
		.pixels_per_line = 5464,
		.lines_per_frame = 2046,
		.bin_factor_x = 1,
		.bin_factor_y = 1,
	},
	{
		.desc = "imx135vb_1080P_dvs_video",
		.regs = imx135vb_2336x1320_max_clock,
		.width = 2336,
		.height = 1320,
		.fps = 30,
		.pixels_per_line = 4572, /* Pixel Clock : 360.96 MHz */
		.lines_per_frame = 2632,
		.bin_factor_x = 0,
		.bin_factor_y = 0,
	},
};

#endif
