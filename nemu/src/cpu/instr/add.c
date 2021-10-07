#include "cpu/instr.h"
/*
Put the implementations of `add' instructions here.
*/

static void instr_execute_2op() 
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
	opr_dest.val = alu_add(opr_src.val, opr_dest.val, opr_dest.data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(add, i, r, v)
make_instr_impl_2op(add, i, rm, v)
make_instr_impl_2op(add, i, rm, bv)

make_instr_impl_2op(add, r, rm, v)
