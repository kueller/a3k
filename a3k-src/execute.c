#include "execute.h"

static int pc = 0;

int current_pc()
{
	return pc;
}

void reset_pc()
{
	pc = 0;
}

int16_t extend_imm(uint16_t imm, int len)
{
	int16_t ret;

	switch(len)
	case 6: {
		if ((imm >> 5) & 0x1)
			ret = imm | IMM6_EXT;
		else
			ret = imm;
		break;
	case 9:
		if ((imm >> 8) & 0x1)
			ret = imm | IMM9_EXT;
		else
			ret = imm;
		break;
	case 12:
		if ((imm >> 11) & 0x1)
			ret = imm | IMM12_EXT;
		else
			ret = imm;
		break;
	default:
		ret = 0;
	}

	return ret;
}

int execute_next(uint16_t *isr, int *reg)
{
	if (!isr || !reg) return IDLE;
	if (pc >= isr_length()) return IDLE;
	
	uint16_t insn = isr[pc];

	int status = IDLE;

	int src1 = 0;
	int src2 = 0;
	int dest = 0;

	int16_t imm = 0;

	switch (insn & OP_MASK) {
	case ADD:
		src1 = (insn >> 7) & REG_MASK;
		src2 = (insn >> 4) & REG_MASK;
		dest = (insn >> 10) & REG_MASK;

		reg[dest] = reg[src1] + reg[src2];
		status = RUNNING;
		pc++;
		break;
	case ADDI:
		src1 = (insn >> 4) & REG_MASK;
		dest = (insn >> 7) & REG_MASK;

		imm = extend_imm(insn >> 10, 6);

		reg[dest] = reg[src1] + imm;
		status = RUNNING;
		pc++;
		break;
	case AND:
		src1 = (insn >> 7) & REG_MASK;
		src2 = (insn >> 4) & REG_MASK;
		dest = (insn >> 10) & REG_MASK;

		reg[dest] = reg[src1] & reg[src2];
		status = RUNNING;
		pc++;
		break;
	case INV:
		src1 = (insn >> 4) & REG_MASK;
		reg[src1] = reg[src1] * -1;

		status = RUNNING;
		pc++;
		break;
	case MULT:
		src1 = (insn >> 7) & REG_MASK;
		src2 = (insn >> 4) & REG_MASK;
		dest = (insn >> 10) & REG_MASK;

		reg[dest] = reg[src1] * reg[src2];
		status = RUNNING;
		pc++;
		break;
	case DIV:
		src1 = (insn >> 7) & REG_MASK;
		src2 = (insn >> 4) & REG_MASK;
		dest = (insn >> 10) & REG_MASK;

		reg[dest] = reg[src1] / reg[src2];
		status = RUNNING;
		pc++;
		break;
	case MOD:
		src1 = (insn >> 7) & REG_MASK;
		src2 = (insn >> 4) & REG_MASK;
		dest = (insn >> 10) & REG_MASK;

		reg[dest] = reg[src1] % reg[src2];
		status = RUNNING;
		pc++;
		break;
	case LDI:
		dest = (insn >> 4) & REG_MASK;
		imm = extend_imm(insn >> 7, 9);

		reg[dest] = imm;
		status = RUNNING;
		pc++;
		break;
	case BLZ:
		if (reg[0] < 0) {
			imm = extend_imm(insn >> 4, 12);
			pc = pc + imm;
		} else {
			pc++;
		}
		status = RUNNING;
		break;
	case BEZ:
		if (reg[0] == 0) {
			imm = extend_imm(insn >> 4, 12);
			pc = pc + imm;
		} else {
			pc++;
		}
		status = RUNNING;
		break;
	case BGZ:
		if (reg[0] > 0) {
			imm = extend_imm(insn >> 4, 12);
			pc = pc + imm;
		} else {
			pc++;
		}
		status = RUNNING;
		break;
	case JMP:
		imm = extend_imm(insn >> 4, 12);
		pc = pc + imm;
		status = RUNNING;
		break;
	case JSR:
		imm = extend_imm(insn >> 4, 12);
		reg[8] = pc + 1;
		pc = pc + imm;
		status = RUNNING;
		break;
	case RET:
		pc = reg[8];
		status = RUNNING;
		break;
	case END:
		status = IDLE;
		break;
	default:
		status = IDLE;
	}

	return status;
}

