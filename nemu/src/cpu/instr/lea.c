#include "cpu/instr.h"
/*
Put the implementations of `lea' instructions here.
*/

static void instr_execute_2op() 
{
	opr_dest.val = resize(opr_src.addr, min(opr_src.data_size, opr_dest.data_size));
	printf("lea: ecx: %x, eax: %x, a:%x \n", cpu.ecx, cpu.eax, opr_dest.val);
	operand_write(&opr_dest);
}

make_instr_impl_2op(lea, rm, r, v)
