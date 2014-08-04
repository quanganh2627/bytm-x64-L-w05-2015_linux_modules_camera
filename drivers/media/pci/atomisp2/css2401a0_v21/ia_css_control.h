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

#ifndef __IA_CSS_CONTROL_H
#define __IA_CSS_CONTROL_H

/** @file
 * This file contains functionality for starting and controlling CSS
 */

#include <type_support.h>
#include <ia_css_env.h>
#include <ia_css_firmware.h>
#include <ia_css_irq.h>

/** @brief Initialize the CSS API.
 * @param[in]	env		Environment, provides functions to access the
 *				environment in which the CSS code runs. This is
 *				used for host side memory access and message
 *				printing. May not be NULL.
 * @param[in]	fw		Firmware package containing the firmware for all
 *				predefined ISP binaries.
 *				if fw is NULL the firmware must be loaded before
 *				through a call of ia_css_load_firmware
 * @param[in]	l1_base         Base index (isp2400)
 *                              of the L1 page table. This is a physical
 *                              address or index.
 * @param[in]	irq_type	The type of interrupt to be used (edge or level)
 * @return				Returns IA_CSS_ERR_INTERNAL_ERROR in case of any
 *				errors and IA_CSS_SUCCESS otherwise.
 *
 * This function initializes the API which includes allocating and initializing
 * internal data structures. This also interprets the firmware package. All
 * contents of this firmware package are copied into local data structures, so
 * the fw pointer could be freed after this function completes.
 */
enum ia_css_err ia_css_init(
	const struct ia_css_env *env,
	const struct ia_css_fw  *fw,
	uint32_t                 l1_base,
	enum ia_css_irq_type     irq_type);

/** @brief Un-initialize the CSS API.
 * @return	None
 *
 * This function deallocates all memory that has been allocated by the CSS API
 * Exception: if you explicitly loaded firmware through ia_css_load_firmware
 * you need to call ia_css_unload_firmware to deallocate the memory reserved
 * for the firmware.
 * After this function is called, no other CSS functions should be called
 * with the exception of ia_css_init which will re-initialize the CSS code,
 * ia_css_unload_firmware to unload the firmware or ia_css_load_firmware
 * to load new firmware
 */
void
ia_css_uninit(void);

/** @brief Suspend CSS API for power down
 * @return	success or faulure code
 *
 * suspend shuts down the system by:
 *  unloading all the streams
 *  stopping SP
 *  performing uninit
 *
 *  Currently stream memory is deallocated because of rmmgr issues.
 *  Need to come up with a bypass that will leave the streams intact.
 */
enum ia_css_err
ia_css_suspend(void);

/** @brief Resume CSS API from power down
 * @return	success or failure code
 *
 * After a power cycle, this function will bring the CSS API back into
 * a state where it can be started.
 * This will re-initialize the hardware and all the streams.
 * Call this function only after ia_css_suspend() has been called.
 */
enum ia_css_err
ia_css_resume(void);

/** @brief Enable use of a separate queue for ISYS events.
 *
 * @param[in]	enable: enable or disable use of separate ISYS event queues.
 * @return		error if called when SP is running.
 *
 * @deprecated{This is a temporary function that allows drivers to migrate to
 * the use of the separate ISYS event queue. Once all drivers supports this, it
 * will be made the default and this function will be removed.
 * This function should only be called when the SP is not running, calling it
 * when the SP is running will result in an error value being returned. }
 */
enum ia_css_err
ia_css_enable_isys_event_queue(bool enable);

/** @brief Test whether the ISP has started.
 *
 * @return	Boolean flag true if the ISP has started or false otherwise.
 *
 * Temporary function to poll whether the ISP has been started. Once it has,
 * the sensor can also be started. */
bool
ia_css_isp_has_started(void);

/** @brief Test whether the SP has initialized.
 *
 * @return	Boolean flag true if the SP has initialized or false otherwise.
 *
 * Temporary function to poll whether the SP has been initialized. Once it has,
 * we can enqueue buffers. */
bool
ia_css_sp_has_initialized(void);

/** @brief Test whether the SP has terminated.
 *
 * @return	Boolean flag true if the SP has terminated or false otherwise.
 *
 * Temporary function to poll whether the SP has been terminated. Once it has,
 * we can switch mode. */
bool
ia_css_sp_has_terminated(void);

#if defined(C_ENABLE_SP1)
/** @brief start SP1 hardware
 *
 * @return			IA_CSS_SUCCESS or error code upon error.
 *
 * It will boot the SP hardware and start multi-threading infrastructure.
 * All threads will be started and blocked by semaphore. This function should
 * be called before any ia_css_stream_start().
 */
void
ia_css_start_sp1(void);
#endif

/** @brief start SP hardware
 *
 * @return			IA_CSS_SUCCESS or error code upon error.
 *
 * It will boot the SP hardware and start multi-threading infrastructure.
 * All threads will be started and blocked by semaphore. This function should
 * be called before any ia_css_stream_start().
 */
enum ia_css_err
ia_css_start_sp(void);

#if defined(C_ENABLE_SP1)
/** @brief stop SP1 hardware
 *
 * @return			IA_CSS_SUCCESS or error code upon error.
 *
 * This function will shut down SP1.
 */
enum ia_css_err
ia_css_stop_sp1(void);
#endif

/** @brief stop SP hardware
 *
 * @return			IA_CSS_SUCCESS or error code upon error.
 *
 * This function will terminate all threads and shut down SP. It should be
 * called after all ia_css_stream_stop().
 */
enum ia_css_err
ia_css_stop_sp(void);

#endif /* __IA_CSS_CONTROL_H */
