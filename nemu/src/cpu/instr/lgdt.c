#include "cpu/instr.h"
/*
Put the implementations of `lgdt' instructions here.
*/

make_instr_func(lgdt) {
    int len = 1;
    decode_operand_rm
    
    // get limit
    opr_src.data_size = 16;
    operand_read(&opr_src);
    cpu.gdtr.limit = opr_src.val;
    
    // get base
    opr_src.addr += 2;
    opr_src.data_size = 32;
    operand_read(&opr_src);
    uint32_t raw_base = opr_src.val;
    cpu.gdtr.base = data_size == 32 ? raw_base : raw_base & 0x00ffffff;
    
    print_asm_1("lgdt", "l", len, &opr_src);
    return len;
}
