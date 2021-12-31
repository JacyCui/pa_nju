#include "cpu/instr.h"
/*
Put the implementations of `iret' instructions here.
*/

make_instr_func(iret) {
    // restore: pop eflags, CS,  eip
    // cpu.eip = pop();
    cpu.cs.val = pop();
    cpu.eflags.val = pop();
    // reload CS with load_sreg()
    load_sreg(1);
    return 0;
}
