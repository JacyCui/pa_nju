#include "cpu/instr.h"
/*
Put the implementations of 'push' instructions here.
*/

void push(uint32_t val) {
    // refresh esp
    cpu.esp -= data_size / 8;
    // fetch dest
    opr_dest.type = OPR_MEM;
    opr_dest.sreg = SREG_SS;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = data_size;
    // val to dest
    opr_dest.val = val;
    operand_write(&opr_dest);
}

static void instr_execute_1op() 
{
    // src to dest
    operand_read(&opr_src);
    push(sign_ext(opr_src.val, opr_src.data_size));
}

make_instr_impl_1op(push, i, b);
make_instr_impl_1op(push, i, v);

make_instr_impl_1op(push, r, v);
make_instr_impl_1op(push, rm, v);

make_instr_func(pusha) {
    uint32_t temp = cpu.esp;
    push(cpu.eax);
    push(cpu.ecx);
    push(cpu.edx);
    push(cpu.ebx);
    push(temp);
    push(cpu.ebp);
    push(cpu.esi);
    push(cpu.edi);
    return 1;
}





