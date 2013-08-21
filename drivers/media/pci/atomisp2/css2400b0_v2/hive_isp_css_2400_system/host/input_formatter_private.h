/* Release Version: ci_master_byt_20130820_2200 */
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

#ifndef __INPUT_FORMATTER_PRIVATE_H_INCLUDED__
#define __INPUT_FORMATTER_PRIVATE_H_INCLUDED__

#include "input_formatter_public.h"

#include "device_access.h"

#include "assert_support.h"

STORAGE_CLASS_INPUT_FORMATTER_C void input_formatter_reg_store(
	const input_formatter_ID_t		ID,
	const hrt_address			reg_addr,
	const hrt_data				value)
{
assert(ID < N_INPUT_FORMATTER_ID);
assert(INPUT_FORMATTER_BASE[ID] != (hrt_address)-1);
assert((reg_addr % sizeof(hrt_data)) == 0);
	device_store_uint32(INPUT_FORMATTER_BASE[ID] + reg_addr, value);
return;
}

STORAGE_CLASS_INPUT_FORMATTER_C hrt_data input_formatter_reg_load(
	const input_formatter_ID_t	ID,
	const unsigned int			reg_addr)
{
assert(ID < N_INPUT_FORMATTER_ID);
assert(INPUT_FORMATTER_BASE[ID] != (hrt_address)-1);
assert((reg_addr % sizeof(hrt_data)) == 0);
return device_load_uint32(INPUT_FORMATTER_BASE[ID] + reg_addr);
}

#endif /* __INPUT_FORMATTER_PRIVATE_H_INCLUDED__ */
