#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/

make_instr_func(ret_near) 
{
    // eip <- pop()
    opr_src.type = OPR_MEM;
    opr_src.addr = cpu.esp;
    opr_src.data_size = data_size;
    operand_read(&opr_src);
    cpu.esp += data_size / 8;
    cpu.eip = sign_ext(opr_src.val, opr_src.data_size);
    return 0;
}
