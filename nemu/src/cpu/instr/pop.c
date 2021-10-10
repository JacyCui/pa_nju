#include "cpu/instr.h"
/*
Put the implementations of `pop' instructions here.
*/

static void instr_execute_1op() 
{
    // read dest
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = data_size;
    // dest to src
    operand_read(&opr_dest);
    opr_src.val = sign_ext(opr_dest.val, dest.data_size);
    operand_write(&opr_src);
    // refresh esp
    cpu.esp += data_size / 8;
}

make_instr_impl_1op(pop, r, v);
