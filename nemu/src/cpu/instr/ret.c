#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/

make_instr_func(ret_near) {
    // eip <- pop()
    opr_src.type = OPR_MEM;
    opr_src.addr = cpu.esp;
    opr_src.data_size = data_size;
    operand_read(&opr_src);
    cpu.esp += data_size / 8;
    cpu.eip = opr_src.val;
    printf("ret: eip = %x, esp = %x \n", cpu.eip, cpu.esp);
    return 1;
}
