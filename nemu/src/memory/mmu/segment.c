#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	return cpu.segReg[sreg].base + offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	if (!cpu.segReg[sreg].ti) { // for gdt
	    printf("here10\n");
	    SegDesc* gdt = (SegDesc*)(cpu.gdtr.base) + cpu.segReg[sreg].index;
	    printf("here11\n");
	    cpu.segReg[sreg].base = (gdt->base_31_24 << 24) + (gdt->base_23_16 << 16) + gdt->base_15_0;
	    printf("here12\n");
	    cpu.segReg[sreg].limit = (gdt->limit_19_16 << 16) + gdt->limit_15_0;
	    printf("here13\n");
	    cpu.segReg[sreg].soft_use = gdt->soft_use;
	    printf("here14\n");
	    cpu.segReg[sreg].type = (gdt->segment_type << 4) + gdt->type;
	    printf("here15\n");
	    cpu.segReg[sreg].privilege_level = gdt->privilege_level;
	    printf("here16\n");
	}
}
