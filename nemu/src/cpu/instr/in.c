#include "cpu/instr.h"
#include "device/port_io.h"
/*
Put the implementations of `in' instructions here.
*/

make_instr_func(in_b) {
    decode_operand_a
    decode_data_size_b
    opr_src.val = pio_read(cpu.edx & 0xffff, 1);
    operand_write(&opr_src);
    return 1;
}

make_instr_func(in_v) {
    decode_operand_a
    decode_data_size_v
    opr_src.val = pio_read(cpu.edx & 0xffff, data_size / 8);
    operand_write(&opr_src);
    return 1;
}
