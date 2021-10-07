#include "cpu/instr.h"
/*
Put the implementations of 'push' instructions here.
*/

static void instr_execute_1op() 
{
    // refresh esp
    cpu.esp -= opr_src.data_size / 8;
    // fetch dest
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = opr_src.data_size;
    // src to dest
    operand_read(&opr_src);
    opr_dest.val = sign_ext(opr_src.val, opr_src.data_size);
    operand_write(&opr_dest);
}

make_instr_impl_1op(push, i, b);
make_instr_impl_1op(push, r, v);
make_instr_impl_1op(push, rm, v);
