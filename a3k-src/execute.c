#include "execute.h"

static uint32_t pc = 0;

uint32_t current_pc()
{
	return pc;
}

void reset_pc()
{
	pc = 0;
}

int32_t extend_imm(int imm, int len)
{
	int32_t ret;

	switch(len) {
	case 14: 
		if ((imm >> 13) & 0x1)
			ret = imm | IMM_EXT14;
		else
			ret = imm;
		break;
	case 19:
		if ((imm >> 18) & 0x1)
			ret = imm | IMM_EXT19;
		else
			ret = imm;
		break;
	case 24:
		if ((imm >> 23) & 0x1)
			ret = imm | IMM_EXT24;
		else
			ret = imm;
		break;
	default:
		ret = 0;
	}

	return ret;
}

int execute_next(uint32_t *mem, uint32_t *reg)
{
	if (!mem || !reg) return A3K_MEM_ERR;
	if (pc >= current_mem_size()) return A3K_OUT_OF_RANGE;
	
	uint32_t insn = mem[pc];

	int status = A3K_IDLE;

	int dest = (insn >> 8) & REG_MASK;
	int src1 = (insn >> 13) & REG_MASK;
	int src2 = (insn >> 18) & REG_MASK;

	int32_t imm14 = extend_imm((insn >> 18), 14);
	int32_t imm19 = extend_imm((insn >> 13), 19);

	uint32_t imm_addr = insn >> 13;

	int32_t imm_offset = extend_imm((insn >> 8), 24);

	int op1 = insn & OP_MASK;
	int op2 = (insn >> 5) & OP2_MASK;

	if (op1 == ARITHMETIC) {
		switch (op2) {
		case OP2_0: // ADD
			reg[dest] = (int32_t)reg[src1] + (int32_t)reg[src2];
			status = A3K_RUNNING;
			break;
		case OP2_1: // ADDI
			reg[dest] = reg[src1] + (int32_t)imm14;
			status = A3K_RUNNING;
			break;
		case OP2_2: // SUB
			reg[dest] = (int32_t)reg[src1] - (int32_t)reg[src2];
			status = A3K_RUNNING;
			break;
		case OP2_3: // SUBI
			reg[dest] = reg[src1] - (int32_t)imm14;
			status = A3K_RUNNING;
			break;
		case OP2_4: // MULT
			reg[dest] = (int32_t)reg[src1] * (int32_t)reg[src2];
			status = A3K_RUNNING;
			break;
		case OP2_5: // DIV
		{
			if (reg[src2] == 0) {
				status = A3K_DIVIDE_BY_ZERO;
			} else {
				reg[dest] = (int32_t)reg[src1] / (int32_t)reg[src2];
				status = A3K_RUNNING;
			}
			break;
		}
		case OP2_6: // MOD
			reg[dest] = (int32_t)reg[src1] % (int32_t)reg[src2];
			status = A3K_RUNNING;
			break;
		default:
			status = A3K_IO_ERR;
		}
		pc++;
		
	} else if (op1 == BITWISE) {
		switch (op2) {
		case OP2_0: // AND
			reg[dest] = (int32_t)reg[src1] & (int32_t)reg[src2];
			status = A3K_RUNNING;
			break;
		case OP2_1: // ANDI
			reg[dest] = (int32_t)reg[src1] & imm14;
			status = A3K_RUNNING;
			break;
		case OP2_2: // OR
			reg[dest] = (int32_t)reg[src1] | (int32_t)reg[src2];
			status = A3K_RUNNING;
			break;
		case OP2_3: // ORI
			reg[dest] = (int32_t)reg[src1] | imm14;
			status = A3K_RUNNING;
			break;
		case OP2_4: // XOR
			reg[dest] = (int32_t)reg[src1] ^ (int32_t)reg[src2];
			status = A3K_RUNNING;
			break;
		case OP2_5: // XORI
			reg[dest] = (int32_t)reg[src1] ^ imm14;
			status = A3K_RUNNING;
			break;
		default:
			status = A3K_IO_ERR;
		}
		pc++;
		
	} else if (op1 == MEM) {
		switch (op2) {
		case OP2_0: // LDI
			reg[dest] = imm19;
			status = A3K_RUNNING;
			break;
		case OP2_1: // LD
			if (imm_addr < current_mem_size()) {
				reg[dest] = mem[imm_addr];
				status = A3K_RUNNING;
			} else {
				status = A3K_OUT_OF_RANGE;
			}
			break;
		case OP2_2: // ST
			if (imm_addr < current_mem_size()) {
				mem[imm_addr] = reg[dest];
				status = A3K_RUNNING;
			} else {
				status = A3K_OUT_OF_RANGE;
			}
			break;
		case OP2_3: // LPC
			reg[dest] = pc;
			status = A3K_RUNNING;
			break;
		case OP2_4: // STR
			if (reg[src1] < current_mem_size()) {
				mem[reg[src1]] = reg[dest];
				status = A3K_RUNNING;
			} else {
				status = A3K_OUT_OF_RANGE;
			}
			break;
		case OP2_5: // LDR
			if (reg[src1] < current_mem_size()) {
				reg[dest] = mem[reg[src1]];
				status = A3K_RUNNING;
			} else {
				status = A3K_OUT_OF_RANGE;
			}
			break;
		default:
			status = A3K_IO_ERR;
		}
		pc++;

	} else if (op1 == SHIFT) {
		switch (op2) {
		case OP2_0: // SL
			reg[dest] = reg[src1] >> (reg[src2] & IMM_SHIFT_MASK);
			status = A3K_RUNNING;
			break;
		case OP2_1: // SLI
			reg[dest] = reg[src1] >> (imm14 & IMM_SHIFT_MASK);
			status = A3K_RUNNING;
			break;
		case OP2_2: // SR
			reg[dest] = reg[src1] << (reg[src2] & IMM_SHIFT_MASK);
			status = A3K_RUNNING;
			break;
		case OP2_3: // SRI
			reg[dest] = reg[src1] << (imm14 & IMM_SHIFT_MASK);
			status = A3K_RUNNING;
			break;
		default:
			status = A3K_IO_ERR;
		}
		pc++;
		
	} else if (op1 == JUMP) {
		switch (op2) {
		case OP2_0: // J
			pc = pc + (int32_t)imm_offset;
			status = A3K_RUNNING;
			break;
		case OP2_1: // JR
			pc = (int32_t)reg[dest];
			status = A3K_RUNNING;
			break;
		case OP2_2: // JSR
			reg[31] = pc + 1;
			pc = pc + (int32_t)imm_offset;
			status = A3K_RUNNING;
			break;
		case OP2_3: // RET
			pc = reg[31];
			status = A3K_RUNNING;
			break;
		case OP2_4: // BLZ
			if ((int32_t)reg[0] < 0)
				pc = pc + (int32_t)imm_offset;
			else
				pc++;
			status = A3K_RUNNING;
			break;
		case OP2_5: // BEZ
			if (reg[0] == 0)
				pc = pc + (int32_t)imm_offset;
			else
				pc++;
			status = A3K_RUNNING;
			break;
		case OP2_6: // BGZ
			if ((int32_t)reg[0] > 0)
				pc = pc + (int32_t)imm_offset;
			else
				pc++;
			status = A3K_RUNNING;
			break;
		default:
			status = A3K_IO_ERR;
		}
	} else if (op1 == END) {
		status = A3K_IDLE;
	} else {
		status = A3K_IO_ERR;
	}

	return status;
}

