#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
// 	printf("Please implement raise_intr()\n");
// 	fflush(stdout);
// 	assert(0);

    // push eflags
    cpu.esp -= 4;
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = 32;
    opr_dest.val = cpu.eflags.val;
    operand_write(&opr_dest);
	// push CS
    cpu.esp -= 4;
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = 32;
    opr_dest.val = cpu.cs.val;
    operand_write(&opr_dest);
    // push eip
    cpu.esp -= 4;
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = 32;
    opr_dest.val = cpu.eip;
    operand_write(&opr_dest);
    
    // Find the IDT entry using 'intr_no'
	GateDesc* idt = (GateDesc*)(hw_mem + cpu.idtr.base) + intr_no;
    
    // Clear IF if it is an interrupt
    if (idt->type == 0xe) {
        cpu.eflags.IF = 0;
    }    
    
    // Set CS:EIP to the entry of the interrupt handler
    cpu.cs.val = idt->selector;
    cpu.eip = idt->offset_31_16 << 16 + offset_15_0;
    
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
