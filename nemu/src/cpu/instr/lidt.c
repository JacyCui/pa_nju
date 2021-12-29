#include "cpu/instr.h"
/*
Put the implementations of `lidt' instructions here.
*/

make_instr_func(lidt) {
    int len = 1;
    decode_operand_rm
    
    // get limit
    opr_src.data_size = 16;
    operand_read(&opr_src);
    cpu.idtr.limit = opr_src.val;
    
    // get base
    opr_src.addr += 2;
    opr_src.data_size = 32;
    operand_read(&opr_src);
    uint32_t raw_base = opr_src.val;
    cpu.idtr.base = data_size == 32 ? raw_base : raw_base & 0x00ffffff;
    
    print_asm_1("lidt", "l", len, &opr_src);
    return len;
}
