#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
// 	printf("Please implement raise_intr()\n");
// 	fflush(stdout);
// 	assert(0);

    // reserve: push eflags, CS,  eip
    push(cpu.eflags.val);
    push(cpu.cs.val);
    push(cpu.eip);
    
    // Find the IDT entry using 'intr_no'
	paddr_t paddr;
    if (cpu.cr0.pg) {
        paddr = page_translate(cpu.idtr.base);
    }
    else {
        paddr = cpu.idtr.base;
    }
	GateDesc* idt = (GateDesc*)(hw_mem + paddr) + intr_no;
    
    // Clear IF if it is an interrupt
    if (idt->type == 0xe) {
        cpu.eflags.IF = 0;
    }
    
    // Set CS:EIP to the entry of the interrupt handler
    cpu.cs.val = idt->selector;
    cpu.eip = (idt->offset_31_16 << 16) + idt->offset_15_0;
    
    // reload CS with load_sreg()
    load_sreg(1);
    
#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
