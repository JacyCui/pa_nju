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
    cpu.eip = opr_src.val;
    
    // esp += imm16
    opr_src.type = OPR_IMM;
	opr_src.sreg = SREG_CS;
	opr_src.addr = eip + 1;
	opr_src.data_size = 16 / 8;
	
    operand_read(&opr_src);
    cpu.esp += opr_src.val;
    
    return 0;
}




