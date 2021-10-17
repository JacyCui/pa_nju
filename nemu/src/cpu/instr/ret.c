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
    print_asm_0("ret", "_near", 0);
    cpu.eip = opr_src.val;
    return 0;
}

make_instr_func(ret_near_imm16) 
{
    // eip <- pop()
    opr_src.type = OPR_MEM;
    opr_src.addr = cpu.esp;
    opr_src.data_size = data_size;
    operand_read(&opr_src);
    cpu.esp += data_size / 8;
    print_asm_0("ret", "_near_imm16", 0);
    cpu.eip = opr_src.val;
    
    // esp += imm16
    opr_dest.type = OPR_IMM;
	opr_dest.sreg = SREG_CS;
	opr_dest.addr = eip + 1;
	opr_dest.data_size = 16;
	
    operand_read(&opr_dest);
    cpu.esp += opr_dest.val;
    
    return 0;
}




