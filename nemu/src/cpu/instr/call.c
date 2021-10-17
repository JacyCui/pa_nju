#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/

make_instr_func(call_i_near) 
{
    int len = 1;
    decode_data_size_near
	decode_operand_i
	
	// push(eip)
    cpu.esp -= opr_dest.data_size / 8;
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.val = cpu.eip + len;
    operand_write(&opr_dest);
    
    // call
    operand_read(&opr_src);
    print_asm_1("call", "_near", len, &opr_src);
    cpu.eip = cpu.eip + opr_src.val;
    
	return len;                                                                                                             
}

make_instr_func(call_near_indirect) {
    int len = 1;
    decode_data_size_near
    decode_operand_rm
    
    // push(eip)
    cpu.esp -= opr_dest.data_size / 8;
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.val = cpu.eip + len;
    operand_write(&opr_dest);
    
    // call
    operand_read(&opr_src);
    print_asm_1("call", "_near_indirect", len, &opr_src);
    cpu.eip = opr_src.val;
    
    return 0;
}

