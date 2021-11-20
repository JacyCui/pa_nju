#include "cpu/instr.h"

/*
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
}*/

static void instr_execute_1op() 
{
    operand_read(&opr_src);
    cpu.eip += sign_ext(opr_src.val, opr_src.data_size);
}

make_instr_impl_1op(jmp, i, near)
make_instr_impl_1op(jmp, i, short_)

make_instr_func(jmp_near_indirect) {
    int len = 1;
    decode_data_size_near
    decode_operand_rm
    operand_read(&opr_src);
    cpu.eip = opr_src.val;
    return 0;
}

make_instr_func(ljmp) {
    opr_src.type = OPR_IMM;
	opr_src.sreg = SREG_CS;
	opr_src.addr = eip + 1;
	opr_src.data_size = data_size;
	
	opr_dest.type = OPR_IMM;
	opr_dest.sreg = SREG_CS;
	opr_dest.addr = eip + 1 + data_size / 8;
	opr_dest.data_size = 16;
	
	operand_read(&opr_src);
	operand_read(&opr_dest);
	
	print_asm_2("ljmp", "", 3 + data_size / 8, &opr_dest, &opr_src);
	
	cpu.eip = opr_src.val;
	cpu.cs.val = opr_dest.val;

    return 0;
}


