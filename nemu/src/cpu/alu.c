#include "cpu/cpu.h"

void set_flags(uint32_t result, uint32_t src, uint32_t dest, size_t data_size, Operation op)
{
	set_CF(result, src, dest, data_size, op);
	set_OF(result, src, dest, data_size, op);
	set_PF(result);
	set_ZF(result, data_size);
	set_SF(result, data_size);
}

void set_CF(uint32_t result, uint32_t src, uint32_t dest, size_t data_size, Operation op)
{
    result = sign_ext(resize(result, data_size), data_size);
    src = sign_ext(resize(src, data_size), data_size);
    dest = sign_ext(resize(dest, data_size), data_size);
    switch (op) 
    {
        case ADC: cpu.eflags.CF = result < src || (cpu.eflags.CF && result == src); break;
        case SBB: cpu.eflags.CF = result > dest || (cpu.eflags.CF && result == dest); break; 
        case AND: case OR: case XOR: cpu.eflags.CF = 0; break;
        case SHL: cpu.eflags.CF = (dest >> (data_size - src)) & 0x1; break;
        case SHR: case SAR: cpu.eflags.CF = (dest >> (src - 1)) & 0x1; break;
        default: break;
    }
}

void set_OF(uint32_t result, uint32_t src, uint32_t dest, size_t data_size, Operation op)
{
    result = sign_ext(resize(result, data_size), data_size);
    src = sign_ext(resize(src, data_size), data_size);
    dest = sign_ext(resize(dest, data_size), data_size);
    switch (op) 
    {
        case ADC: cpu.eflags.OF = (sign(src) == sign(dest)) && (sign(src) != sign(result)); break;
        case SBB: cpu.eflags.OF = (sign(src) != sign(dest)) && (sign(dest) != sign(result)); break;
        case AND: case OR: case XOR: cpu.eflags.OF = 0; break;
        default: break;
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
    uint32_t ones = 0;
    for (int i = 0; i < 8; i++) 
    {
        ones = (result & 0x1) ^ ones;
        result = result >> 1;
    }
    cpu.eflags.PF = ones ^ 0x1;
}

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
	cpu.eflags.CF = 0;
	return alu_adc(src, dest, data_size);
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
	uint32_t res = dest + src + cpu.eflags.CF; // Calculate the Result
	set_flags(res, src, dest, data_size, ADC); // set flags
	return resize(res, data_size);
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
    cpu.eflags.CF = 0;
	return alu_sbb(src, dest, data_size);
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
    uint32_t res = dest - src - cpu.eflags.CF; // Calculate the Result
	set_flags(res, src, dest, data_size, SBB); // set flags
	return resize(res, data_size);
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	uint64_t res = (uint64_t)src * (uint64_t)dest;
	cpu.eflags.OF = cpu.eflags.CF = res >> data_size != 0;
	return res;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	int64_t res = (int64_t)src * (int64_t)dest;
	cpu.eflags.OF = cpu.eflags.CF = res >> data_size != -1 && res >> data_size != 0;
	return res;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	return resize(dest / src, data_size);
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	return resize(dest / src, data_size);
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	return dest % src;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	return dest % src;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
    uint32_t res = dest & src; // Calculate the Result
	set_flags(res, src, dest, data_size, AND); // set flags
	return resize(res, data_size);
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	uint32_t res = dest ^ src; // Calculate the Result
	set_flags(res, src, dest, data_size, XOR); // set flags
	return resize(res, data_size);
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	uint32_t res = dest | src; // Calculate the Result
	set_flags(res, src, dest, data_size, OR); // set flags
	return resize(res, data_size);
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	uint32_t res = resize(dest, data_size) << src; // Calculate the Result
	set_flags(res, src, dest, data_size, SHL); // set flags
	return resize(res, data_size);
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	uint32_t res = resize(dest, data_size) >> src; // Calculate the Result
	set_flags(res, src, dest, data_size, SHR); // set flags
	return resize(res, data_size);
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	uint32_t res = (int32_t)sign_ext(dest, data_size) >> src; // Calculate the Result
	set_flags(res, src, dest, data_size, SAR); // set flags
	return resize(res, data_size);
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	return alu_shl(src, dest, data_size);
#endif
}
