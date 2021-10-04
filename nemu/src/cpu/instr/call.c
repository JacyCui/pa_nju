#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/

static void instr_execute_1op() {
    // push eip
    cpu.esp -= data_size / 8;
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = data_size;
    opr_dest.val = cpu.eip;
    operand_write(&opr_dest);
    
    // call
    operand_read(&opr_src);
    cpu.eip += opr_src.val;
}

make_instr_impl_1op(call, i, near);
