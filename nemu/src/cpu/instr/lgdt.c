#include "cpu/instr.h"
/*
Put the implementations of `lgdt' instructions here.
*/

static void instr_execute_1op() 
{
    operand_read(&opr_src);
    cpu.gdtr.limit = paddr_read(opr_src.val, 2);
    printf("debug: %x\n", opr_src.val);
    uint32_t raw_base = paddr_read(opr_src.val + 2, 4);
    cpu.gdtr.base = data_size == 32 ? raw_base : raw_base & 0x00ffffff;
}

make_instr_impl_1op(lgdt, i, near)
