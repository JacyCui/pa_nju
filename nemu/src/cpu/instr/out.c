#include "cpu/instr.h"
#include "device/port_io.h"
/*
Put the implementations of `out' instructions here.
*/

make_instr_func(out_b) {
    pio_read(cpu.edx & 0xffff, 8, cpu.eax & 0xff);
    return 1;
}

make_instr_func(out_v) {
    pio_read(cpu.edx & 0xffff, data_size, cpu.eax & (0xffffffff >> (32 - data_size)));
    return 1;
}
