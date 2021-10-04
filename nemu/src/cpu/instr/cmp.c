#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/

static void instr_execute_2op() 
{
    alu_sub(opr_src.val, opr_dest.val, data_size);
}

make_instr_impl_2op(cmp, i, rm, bv);
