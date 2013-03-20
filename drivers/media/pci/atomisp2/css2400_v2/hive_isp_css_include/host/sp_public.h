#ifndef __SP_PUBLIC_H_INCLUDED__
#define __SP_PUBLIC_H_INCLUDED__

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#include "stddef.h"			/* size_t */
#include "stdbool.h"		/* bool */
#endif

#include "system_types.h"

typedef struct sp_state_s		sp_state_t;
typedef struct sp_stall_s		sp_stall_t;

/*! Enable or disable the program complete irq signal of SP[ID]
 
 \param	ID[in]				SP identifier
 \param	cnd[in]				predicate

 \return none, if(cnd) enable(SP[ID].irq) else disable(SP[ID].irq)
 */
extern void cnd_sp_irq_enable(
	const sp_ID_t		ID,
	const bool			cnd);

/*! Read the state of cell SP[ID]
 
 \param	ID[in]				SP identifier
 \param	state[out]			sp state structure
 \param	stall[out]			isp stall conditions

 \return none, state = SP[ID].state, stall = SP[ID].stall
 */
extern void sp_get_state(
	const sp_ID_t		ID,
	sp_state_t			*state,
	sp_stall_t			*stall);

/*! Write to the status and control register of SP[ID]

 \param	ID[in]				SP identifier
 \param	reg[in]				register index
 \param value[in]			The data to be written

 \return none, SP[ID].sc[reg] = value
 */
STORAGE_CLASS_SP_H void sp_ctrl_store(
	const sp_ID_t		ID,
	const unsigned int	reg,
	const hrt_data		value);

/*! Read from the status and control register of SP[ID]

 \param	ID[in]				SP identifier
 \param	reg[in]				register index
 \param value[in]			The data to be written

 \return SP[ID].sc[reg]
 */
STORAGE_CLASS_SP_H hrt_data sp_ctrl_load(
	const sp_ID_t		ID,
	const unsigned int	reg);

/*! Get the status of a bitfield in the control register of SP[ID]

 \param	ID[in]				SP identifier
 \param	reg[in]				register index
 \param bit[in]				The bit index to be checked

 \return  (SP[ID].sc[reg] & (1<<bit)) != 0
 */
STORAGE_CLASS_SP_H bool sp_ctrl_getbit(
	const sp_ID_t		ID,
	const unsigned int	reg,
	const unsigned int	bit);

/*! Set a bitfield in the control register of SP[ID]

 \param	ID[in]				SP identifier
 \param	reg[in]				register index
 \param bit[in]				The bit index to be set

 \return none, SP[ID].sc[reg] |= (1<<bit)
 */
STORAGE_CLASS_SP_H void sp_ctrl_setbit(
	const sp_ID_t		ID,
	const unsigned int	reg,
	const unsigned int	bit);

/*! Clear a bitfield in the control register of SP[ID]

 \param	ID[in]				SP identifier
 \param	reg[in]				register index
 \param bit[in]				The bit index to be set

 \return none, SP[ID].sc[reg] &= ~(1<<bit)
 */
STORAGE_CLASS_SP_H void sp_ctrl_clearbit(
	const sp_ID_t		ID,
	const unsigned int	reg,
	const unsigned int	bit);

/*! Write to the DMEM of SP[ID]

 \param	ID[in]				SP identifier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be written
 \param size[in]			The size(in bytes) of the data to be written

 \return none, SP[ID].dmem[addr...addr+size-1] = data
 */
STORAGE_CLASS_SP_H void sp_dmem_store(
	const sp_ID_t		ID,
	unsigned int		addr,
	const void			*data,
	const size_t		size);

/*! Read from the DMEM of SP[ID]

 \param	ID[in]				SP identifier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be read
 \param size[in]			The size(in bytes) of the data to be read

 \return none, data = SP[ID].dmem[addr...addr+size-1]
 */
STORAGE_CLASS_SP_H void sp_dmem_load(
	const sp_ID_t		ID,
	const unsigned int	addr,
	void				*data,
	const size_t		size);

/*! Write a 8-bit datum to the DMEM of SP[ID]

 \param	ID[in]				SP identifier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be written
 \param size[in]			The size(in bytes) of the data to be written

 \return none, SP[ID].dmem[addr...addr+size-1] = data
 */
STORAGE_CLASS_SP_H void sp_dmem_store_uint8(
	const sp_ID_t		ID,
	unsigned int		addr,
	const uint8_t		data);

/*! Write a 16-bit datum to the DMEM of SP[ID]

 \param	ID[in]				SP identifier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be written
 \param size[in]			The size(in bytes) of the data to be written

 \return none, SP[ID].dmem[addr...addr+size-1] = data
 */
STORAGE_CLASS_SP_H void sp_dmem_store_uint16(
	const sp_ID_t		ID,
	unsigned int		addr,
	const uint16_t		data);

/*! Write a 32-bit datum to the DMEM of SP[ID]

 \param	ID[in]				SP identifier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be written
 \param size[in]			The size(in bytes) of the data to be written

 \return none, SP[ID].dmem[addr...addr+size-1] = data
 */
STORAGE_CLASS_SP_H void sp_dmem_store_uint32(
	const sp_ID_t		ID,
	unsigned int		addr,
	const uint32_t		data);

/*! Load a 8-bit datum from the DMEM of SP[ID]

 \param	ID[in]				SP identifier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be read
 \param size[in]			The size(in bytes) of the data to be read

 \return none, data = SP[ID].dmem[addr...addr+size-1]
 */
STORAGE_CLASS_SP_H uint8_t sp_dmem_load_uint8(
	const sp_ID_t		ID,
	const unsigned int	addr);

/*! Load a 16-bit datum from the DMEM of SP[ID]

 \param	ID[in]				SP identifier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be read
 \param size[in]			The size(in bytes) of the data to be read

 \return none, data = SP[ID].dmem[addr...addr+size-1]
 */
STORAGE_CLASS_SP_H uint16_t sp_dmem_load_uint16(
	const sp_ID_t		ID,
	const unsigned int	addr);

/*! Load a 32-bit datum from the DMEM of SP[ID]

 \param	ID[in]				SP identifier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be read
 \param size[in]			The size(in bytes) of the data to be read

 \return none, data = SP[ID].dmem[addr...addr+size-1]
 */
STORAGE_CLASS_SP_H uint32_t sp_dmem_load_uint32(
	const sp_ID_t		ID,
	const unsigned int	addr);

#endif /* __SP_PUBLIC_H_INCLUDED__ */
