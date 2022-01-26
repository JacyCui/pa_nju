#include "cpu/instr.h"
/*
Put the implementations of `pop' instructions here.
*/

uint32_t pop() {
    // read dest
    opr_dest.type = OPR_MEM;
    opr_dest.sreg = SREG_SS;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = data_size;
    // fetch dest
    operand_read(&opr_dest);
    // refresh esp
    cpu.esp += data_size / 8;
    return opr_dest.val;
}

static void instr_execute_1op() 
{
    opr_src.val = pop();
    operand_write(&opr_src);
}

make_instr_impl_1op(pop, r, v);

make_instr_func(popa) {
    cpu.edi = pop();
    cpu.esi = pop();
    cpu.ebp = pop();
    pop();
    cpu.ebx = pop();
    cpu.edx = pop();
    cpu.ecx = pop();
    cpu.eax = pop();
    return 1;
}
