#include "cpu/instr.h"
#include "device/port_io.h"
/*
Put the implementations of `in' instructions here.
*/

make_instr_func(in_b) {
    uint32_t port = pio_read(cpu.edx & 0xffff, 1);
    cpu.eax = (cpu.eax & 0xffffff00) + (port & 0xff);
    return 1;
}

make_instr_func(in_v) {
    uint32_t port = pio_read(cpu.edx & 0xffff, data_size / 8);
    cpu.eax = (cpu.eax & (0xffffffff << data_size)) + (port & (0xffffffff << (32 - data_size)));
    return 1;
}
