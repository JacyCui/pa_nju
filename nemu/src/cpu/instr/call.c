#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/

make_instr_func(call_i_near) 
{
    //printf("debug0: eip = 0x%x \n", cpu.eip);
    int len = 1;
    concat(decode_data_size_, near)
	concat3(decode_operand, _, i)
	
	//printf("debug1: eip = 0x%x \n", cpu.eip);
	
	// push(eip)
    cpu.esp -= opr_dest.data_size / 8;
    //printf("debug2: eip = 0x%x \n", cpu.eip);
    opr_dest.type = OPR_MEM;
    //printf("debug3: eip = 0x%x \n", cpu.eip);
    opr_dest.addr = cpu.esp;
    //printf("debug4: eip = 0x%x \n", cpu.eip);
    opr_dest.val = cpu.eip + len;
    //printf("debug5: eip = 0x%x \n", cpu.eip);
    operand_write(&opr_dest);
    
    //printf("debug6: eip = 0x%x \n", cpu.eip);
    
    // call
    operand_read(&opr_src);
    cpu.eip = resize(cpu.eip + opr_src.val, data_size);
    //printf("opr_src.val = 0x%x eip = 0x%x\n", opr_src.val, cpu.eip);
	                                                                                                    \
	return len;                                                                                                             
}
