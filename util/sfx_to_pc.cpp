#include "sfx_to_pc.h"

//thank you asar
uint32_t
lorom_to_pc(uint32_t addr)
{
	if ((addr & 0xFE0000) == 0x7E0000 ||	//wram
	    (addr & 0x408000) == 0x000000 ||	//hardware regs, ram mirrors, other strange junk
	    (addr & 0x708000) == 0x700000)	//sram (low parts of banks 70-7D)
                                return -1;
                return ((addr & 0x7F0000)>>1 | (addr & 0x7FFF));
	return addr;
}
uint32_t
sfx_to_pc(uint32_t addr)
{
	// Asar emulates GSU1, because apparently emulators don't support the extra ROM data from GSU2
	if ((addr & 0x600000) == 0x600000 ||	//wram, sram, open bus
	   (addr & 0x408000)  == 0x000000 ||	//hardware regs, ram mirrors, rom mirrors, other strange junk
	   (addr & 0x800000)  == 0x800000){	//fastrom isn't valid either in superfx
		return -1;
	}
	if (addr & 0x400000) { return addr & 0x3FFFFF; }
	return (addr & 0x7F0000) >> 1 | (addr & 0x7FFF);
}
