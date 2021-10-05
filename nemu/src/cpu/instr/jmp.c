#include "cpu/instr.h"

make_instr_func(jmp_near)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

        return 1 + data_size / 8;
}

static void instr_execute_1op() 
{
    operand_read(&opr_src);
    cpu.eip += sign_ext(opr_src.val, opr_src.data_size);
}

make_instr_impl_1op(jmp, i, near)
make_instr_impl_1op(jmp, i, short_)

