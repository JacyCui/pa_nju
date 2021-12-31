#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/

make_instr_func(ret_near) 
{
    // eip <- pop()
    cpu.eip = pop();
    print_asm_0("ret", "_near", 0);
    return 0;
}

make_instr_func(ret_near_imm16) 
{
    // eip <- pop()
    cpu.eip = pop();
    print_asm_0("ret", "_near_imm16", 0);
    
    // esp += imm16
    opr_dest.type = OPR_IMM;
	opr_dest.sreg = SREG_CS;
	opr_dest.addr = eip + 1;
	opr_dest.data_size = 16;
	
    operand_read(&opr_dest);
    cpu.esp += opr_dest.val;
    
    return 0;
}




