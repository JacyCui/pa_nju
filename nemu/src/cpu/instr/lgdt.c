#include "cpu/instr.h"
/*
Put the implementations of `lgdt' instructions here.
*/

make_instr_func(lgdt) {
    int len = 1;
    decode_operand_rm
    decode_data_size_v
    operand_read(opr_src);
    
    cpu.gdtr.limit = paddr_read(opr_src.val, 2);
    print_asm_1("lgdt", "l", len, &opr_src);
    uint32_t raw_base = paddr_read(opr_src.val + 2, 4);
    cpu.gdtr.base = data_size == 32 ? raw_base : raw_base & 0x00ffffff;
    
    return len;
}
