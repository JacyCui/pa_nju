#include "cpu/instr.h"
#include "device/port_io.h"
/*
Put the implementations of `out' instructions here.
*/

make_instr_func(out_b) {
    decode_operand_a
    decode_data_size_b
    pio_write(cpu.edx & 0xffff, 1, operand_read(&opr_src));
    return 1;
}

make_instr_func(out_v) {
    decode_operand_a
    decode_data_size_v
    pio_write(cpu.edx & 0xffff, data_size / 8, operand_read(&opr_src));
    return 1;
}
