#include "cpu/instr.h"
/*
Put the implementations of 'push' instructions here.
*/

static void instr_execute_1op() {
    printf("esp = %x, eip = %x, ebp = %x\n", cpu.esp, cpu.eip, cpu.ebp)
    
    cpu.esp -= data_size / 8;
    
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = data_size;
    
    operand_read(&opr_src);
    printf("push: opr_src.val = %x = \n ", opr_src.val, cpu.ebp);
    opr_dest.val = opr_src.val;
    operand_write(&opr_dest);
}

make_instr_impl_1op(push, r, v);
