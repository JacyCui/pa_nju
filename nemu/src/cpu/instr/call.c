#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/

static void instr_execute_1op() {
    operand_read(&opr_src);
    cpu.eip += opr_src.val;
}

make_instr_impl_1op(call, i, near);
