#include "cpu/instr.h"
/*
Put the implementations of 'push' instructions here.
*/

static void instr_execute_1op() {
    operand_read(&opr_src);
    opr_src.val -= datasize / 8;
    operand_write(&opr_src);
}

make_instr_impl_1op(push, r, v);
