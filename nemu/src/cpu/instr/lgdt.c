#include "cpu/instr.h"
/*
Put the implementations of `lgdt' instructions here.
*/

make_instr_func(lgdt) {
    int len = 2;
    opr_src.type = OPR_IMM;
    opr_src.sreg = SREG_CS;
    opr_src.data_size = data_size;
    opr_src.addr = eip + 2;
    len += data_size / 8;
    operand_read(&opr_src);
    
    cpu.gdtr.limit = paddr_read(opr_src.val, 2);
    // printf("debug: %x\n", opr_src.val);
    uint32_t raw_base = paddr_read(opr_src.val + 2, 4);
    cpu.gdtr.base = data_size == 32 ? raw_base : raw_base & 0x00ffffff;
    
    return len;
}
