#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/

make_instr_func(call_i_near) 
{
    int len = 1;
    concat(decode_data_size_, near)
	concat3(decode_operand, _, i)
	
	// push(eip)
    cpu.esp -= opr_dest.data_size / 8;
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.val = cpu.eip + len;
    operand_write(&opr_dest);
    
    // call
    operand_read(&opr_src);
    printf("debug: eip = 0x%x ", cpu.eip);
    cpu.eip = resize(cpu.eip + opr_src.val, data_size);
    printf("opr_src.val = 0x%x eip = 0x%x\n", opr_src.val, cpu.eip);
	                                                                                                    \
	return len;                                                                                                             
}
