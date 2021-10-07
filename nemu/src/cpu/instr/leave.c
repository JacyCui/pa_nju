#include "cpu/instr.h"
/*
Put the implementations of `leave' instructions here.
*/

make_instr_func(leave) 
{
    // esp <- sbp
    cpu.esp = cpu.ebp;
    // ebp <- pop()
    opr_src.type = OPR_MEM;
    opr_src.addr = cpu.esp;
    opr_src.data_size = data_size;
    operand_read(&opr_src);
    cpu.esp += data_size / 8;
    cpu.ebp = opr_src.val;
    return 1;
}

