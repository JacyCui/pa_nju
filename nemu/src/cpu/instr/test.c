#include "cpu/instr.h"
/*
Put the implementations of `test' instructions here.
*/

static void instr_execute_2op() 
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
	alu_and(opr_src.val, opr_dest.val, opr_dest.data_size);
}

make_instr_impl_2op(test, r, rm, b)
make_instr_impl_2op(test, r, rm, v)
