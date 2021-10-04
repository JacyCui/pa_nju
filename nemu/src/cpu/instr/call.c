#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/

make_instr_func(call_i_near) {
    int len = 1;
    concat(decode_data_size_, near)
	concat3(decode_operand, _, i)
	
	// push(eip)
    cpu.esp -= data_size / 8;
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = data_size;
    opr_dest.val = cpu.eip + len - 1;
    operand_write(&opr_dest);
    
    // call
    operand_read(&opr_src);
    cpu.eip += opr_src.val;
	                                                                                                    \
	return len;                                                                                                             
}
