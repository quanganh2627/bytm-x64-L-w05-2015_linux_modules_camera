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

#include "input_system.h"

#ifdef HAS_INPUT_SYSTEM_VERSION_2
#include "ia_css_isys.h"

#ifdef __KERNEL__
#include <linux/string.h>
#else
#include <string.h>
#endif

#if defined(USE_INPUT_SYSTEM_VERSION_2)
input_system_error_t ia_css_isys_init(void)
{
	backend_channel_cfg_t backend_ch0;
	backend_channel_cfg_t backend_ch1;
	target_cfg2400_t targetB;
	target_cfg2400_t targetC;
	uint32_t acq_mem_region_size = 24;
	uint32_t acq_nof_mem_regions = 2;
	input_system_error_t error = INPUT_SYSTEM_ERR_NO_ERROR;

	memset(&backend_ch0, 0, sizeof(backend_channel_cfg_t));
	memset(&backend_ch1, 0, sizeof(backend_channel_cfg_t));
	memset(&targetB, 0, sizeof(targetB));
	memset(&targetC, 0, sizeof(targetC));

	error = input_system_configuration_reset();
	if (error != INPUT_SYSTEM_ERR_NO_ERROR)
		return error;

	error = input_system_csi_xmem_channel_cfg(
			0,			/*ch_id                 */
			INPUT_SYSTEM_PORT_A,	/*port                  */
			backend_ch0,		/*backend_ch            */
			32,			/*mem_region_size       */
			6,			/*nof_mem_regions       */
			acq_mem_region_size,	/*acq_mem_region_size   */
			acq_nof_mem_regions,	/*acq_nof_mem_regions   */
			targetB,		/*target                */
			3);			/*nof_xmem_buffers      */
	if (error != INPUT_SYSTEM_ERR_NO_ERROR)
		return error;

	error = input_system_csi_xmem_channel_cfg(
			1,			/*ch_id                 */
			INPUT_SYSTEM_PORT_B,	/*port                  */
			backend_ch0,		/*backend_ch            */
			16,			/*mem_region_size       */
			3,			/*nof_mem_regions       */
			acq_mem_region_size,	/*acq_mem_region_size   */
			acq_nof_mem_regions,	/*acq_nof_mem_regions   */
			targetB,		/*target                */
			3);			/*nof_xmem_buffers      */
	if (error != INPUT_SYSTEM_ERR_NO_ERROR)
		return error;

	error = input_system_csi_xmem_channel_cfg(
			2,			/*ch_id                 */
			INPUT_SYSTEM_PORT_C,	/*port                  */
			backend_ch1,		/*backend_ch            */
			32,			/*mem_region_size       */
			3,			/*nof_mem_regions       */
			acq_mem_region_size,	/*acq_mem_region_size   */
			acq_nof_mem_regions,	/*acq_nof_mem_regions   */
			targetC,		/*target                */
			2);			/*nof_xmem_buffers      */
	if (error != INPUT_SYSTEM_ERR_NO_ERROR)
		return error;

	error = input_system_configuration_commit();

	return error;
}
#elif defined(USE_INPUT_SYSTEM_VERSION_2401)
input_system_error_t ia_css_isys_init(void)
{
	input_system_error_t error = INPUT_SYSTEM_ERR_NO_ERROR;

	ia_css_isys_csi_rx_lut_rmgr_init();
	ia_css_isys_ibuf_rmgr_init();
	ia_css_isys_dma_channel_rmgr_init();
	ia_css_isys_stream2mmio_sid_rmgr_init();

	return error;
}
#endif

#if defined(USE_INPUT_SYSTEM_VERSION_2)
void ia_css_isys_uninit(void)
{
}
#elif defined(USE_INPUT_SYSTEM_VERSION_2401)
void ia_css_isys_uninit(void)
{
	ia_css_isys_csi_rx_lut_rmgr_uninit();
	ia_css_isys_ibuf_rmgr_uninit();
	ia_css_isys_dma_channel_rmgr_uninit();
	ia_css_isys_stream2mmio_sid_rmgr_uninit();
}
#endif

#endif
