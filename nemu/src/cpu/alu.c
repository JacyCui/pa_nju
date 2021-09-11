#include "cpu/cpu.h"

void set_CF(uint32_t result, uint32_t src, uint32_t dest, size_t data_size, Operation op)
{
    result = sign_ext(resize(result, data_size), data_size);
    src = sign_ext(resize(src, data_size), data_size);
    switch (op)
    {
        case ADD:
            cpu.eflags.CF = result < src; break;
        case ADC:
            cpu.eflags.CF = result < src || (cpu.eflags.CF && result == src); break;
        case SUB:
            cpu.eflags.CF = result >= src; break;
        default:
            break;
    }
}

void set_OF(uint32_t result, uint32_t src, uint32_t dest, size_t data_size, Operation op)
{
    result = sign_ext(resize(result, data_size), data_size);
    src = sign_ext(resize(src, data_size), data_size);
    dest = sign_ext(resize(dest, data_size), data_size);
    switch (op)
    {
        case ADD: 
        case ADC:
            cpu.eflags.OF = (sign(src) == sign(dest)) && (sign(src) != sign(result)); break;
        case SUB:
            set_OF(result, -src, dest, data_size, ADD); break;
        default: 
            break;
    }
}

void set_ZF(uint32_t result, size_t data_size)
{
    result = resize(result, data_size);
    cpu.eflags.ZF = result == 0;
}

void set_SF(uint32_t result, size_t data_size)
{
    result = sign_ext(resize(result, data_size), data_size);
    cpu.eflags.SF = sign(result);
}

void set_PF(uint32_t result)
{
    int ones = 0;
    for (int i = 0; i < 8; i++) 
    {
        if (result % 2 == 1) 
            ones += 1;
        result = result >> 1;
    }
    cpu.eflags.PF = ones % 2 == 0;
}



uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
	uint32_t res = dest + src; // Calculate the Result
	// set flags
	set_PF(res);
	set_CF(res, src, dest, data_size, ADD);
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF(res, src, dest, data_size, ADD);
	return resize(res, data_size);
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
	uint32_t res = dest + src + cpu.eflags.CF; // Calculate the Result
	// set flags
	set_PF(res);
	set_CF(res, src, dest, data_size, ADC);
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF(res, src, dest, data_size, ADC);
	return resize(res, data_size);
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
	uint32_t res = dest - src; // Calculate the Result
	// set flags
	set_PF(res);
	set_CF(res, src, dest, data_size, SUB);
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF(res, src, dest, data_size, SUB);
	return resize(res, data_size);
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}
