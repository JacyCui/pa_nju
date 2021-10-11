#include "cpu/instr.h"
/*
Put the implementations of `neg' instructions here.
*/

static void instr_execute_1op() 
{
    operand_read(&opr_src);
    opr_src.val = sign_ext(opr_src.val, opr_src.data_size);
    opr_src.val = alu_sub(opr_src.val, 0, opr_src.data_size);
    cpu.eflags.CF = (opr_src.val != 0);
    operand_write(&opr_src);
}

make_instr_impl_1op(neg, rm, b)
make_instr_impl_1op(neg, rm, v)
