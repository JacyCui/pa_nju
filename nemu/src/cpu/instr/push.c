#include "cpu/instr.h"
/*
Put the implementations of 'push' instructions here.
*/

static void instr_execute_1op() 
{
    // refresh esp
    cpu.esp -= data_size / 8;
    // fetch dest
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = data_size;
    // src to dest
    operand_read(&opr_src);
    opr_dest.val = opr_src.val;
    operand_write(&opr_dest);
}

make_instr_impl_1op(push, r, v);
