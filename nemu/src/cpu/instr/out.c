#include "cpu/instr.h"
#include "device/port_io.h"
/*
Put the implementations of `out' instructions here.
*/

make_instr_func(out_b) {
    decode_operand_a
    decode_data_size_b
    operand_read(&opr_src);
    pio_write(cpu.edx & 0xffff, 1, opr_src.val);
    return 1;
}

make_instr_func(out_v) {
    decode_operand_a
    decode_data_size_v
    operand_read(&opr_src);
    pio_write(cpu.edx & 0xffff, data_size / 8, opr_src.val);
    return 1;
}
