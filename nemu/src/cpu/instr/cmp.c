#include "cpu/instr.h"
#include <stdio.h>
/*
Put the implementations of `cmp' instructions here.
*/

static void instr_execute_2op() 
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    alu_sub(opr_src.val, opr_dest.val, opr_dest.data_size);
}

make_instr_impl_2op(cmp, i, rm, bv)
make_instr_impl_2op(cmp, r, rm, v)
