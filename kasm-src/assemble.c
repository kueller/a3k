#include <stdio.h>
#include "assemble.h"

#define SHIFT_MASK 0x7fffff

static int data_offset = 0;

uint32_t insn_register_computation(Instruction *i)
{
	StrNode *n = i->list->head;
	n = n->next;
	int dest = get_register_index(n->str);
	n = n->next;
	int src1 = get_register_index(n->str);
	n = n->next;
	int src2 = get_register_index(n->str);

	index_in_range(dest, i->page);
	index_in_range(src1, i->page);
	index_in_range(src2, i->page);

	return i->op1 | i->op2 << 5 | dest << 8 | src1 << 13 | src2 << 18;
}

uint32_t insn_immediate14(Instruction *i)
{
	StrNode *n = i->list->head;
	n = n->next;
	int dest = get_register_index(n->str);
	n = n->next;
	int src1 = get_register_index(n->str);
	n = n->next;

	int imm = immediate_convert(n->str, i->page);

	index_in_range(dest, i->page);
	index_in_range(src1, i->page);

	return i->op1 | i->op2 << 5 | dest << 8 | src1 << 13 | imm << 18;
}

uint32_t insn_addr19(Instruction *i, VarList *vlist)
{
	StrNode *n = i->list->head;
	n = n->next;
	int dest = get_register_index(n->str);
	n = n->next;

	int imm = 0;
	if (IS_A_NUMBER(n->str[0])) {
		imm = immediate_convert(n->str, i->page);
	} else if (IS_A_LETTER(n->str[0])) {
		int addr = link_var_name_to_address(vlist, n->str);
		if (addr == -1)
			kasm_exit("Invalid variable label.", i->page);
		imm = addr + data_offset;
	}

	index_in_range(dest, i->page);

	return i->op1 | i->op2 << 5 | dest << 8 | imm << 13;
}

uint32_t insn_lpc(Instruction *i)
{
	StrNode *n = i->list->head;
	n = n->next;
	int dest = get_register_index(n->str);

	index_in_range(dest, i->page);

	return i->op1 | i->op2 << 5 | dest << 8;
}

uint32_t insn_reg_mem(Instruction *i)
{
	StrNode *n = i->list->head;
	n = n->next;
	int dest = get_register_index(n->str);
	n = n->next;
	int src1 = get_register_index(n->str);

	index_in_range(dest, i->page);
	index_in_range(src1, i->page);

	return i->op1 | i->op2 << 5 | dest << 8 | src1 << 13;
}

uint32_t insn_offset24(Instruction *i)
{
	StrNode *n = i->list->head;
	char *label = n->next->str;
	
	return i->op1 | i->op2 << 5 | offset_to_label(i, label) << 8;
}

/*
 * Writes the data variable header. Sequence is as follows:
 *      32 bit value of 0
 *      -----------------
 *      32 bit data type (0b01 or 0b10 for data or array respectively)
 *      32 bit value/array size
 *      32 bit relative address
 *      (repeated for as many variables as needed, if any
 *      -----------------
 *      closing 32 bit value of 0 again
 */
void write_data_header(FILE *fp, VarList *vlist)
{
	uint32_t tmp = 0;
	fwrite(&tmp, 1, 4, fp);

	if (vlist->size > 0) {
		Var *current = vlist->head;

		while (current) {
			fwrite(&current->type, 1, 4, fp);
			fwrite(&current->value, 1, 4, fp);
			fwrite(&current->addr, 1, 4, fp);
			current = current->next;
		}
	}

	fwrite(&tmp, 1, 4, fp);
}

/*
 * Creates the 16 bit instruction for each Instruction struct passed.
 * See documentation for how the bit strings are organized.
 */
int instruction_code_create(Instruction *i, VarList *vlist)
{
	uint32_t iline = 0;

	if (i->op1 == ARITHMETIC) {
		switch (i->op2) {
		case OP2_0:
		case OP2_2:
		case OP2_4:
		case OP2_5:
		case OP2_6:
			iline = insn_register_computation(i);
			break;
		case OP2_1:
		case OP2_3:
			iline = insn_immediate14(i);
			break;
		default:
			iline = i->op1;
		}
	} else if (i->op1 == BITWISE) {
		switch (i->op2) {
		case OP2_0:
		case OP2_2:
		case OP2_4:
			iline = insn_register_computation(i);
			break;
		case OP2_1:
		case OP2_3:
		case OP2_5:
			iline = insn_immediate14(i);
			break;
		default:
			iline = i->op1;
		}
	} else if (i->op1 == MEM) {
		switch (i->op2) {
		case OP2_0:
		case OP2_1:
		case OP2_2:
			iline = insn_addr19(i, vlist);
			break;
		case OP2_3:
			iline = insn_lpc(i);
			break;
		case OP2_4:
		case OP2_5:
			iline = insn_reg_mem(i);
			break;
		default:
			iline = i->op1;
		}
	} else if (i->op1 == SHIFT) {
		switch (i->op2) {
		case OP2_0:
		case OP2_2:
			iline = insn_register_computation(i);
			break;
		case OP2_1:
		case OP2_3:
			iline = insn_immediate14(i) & SHIFT_MASK;
			break;
		default:
			iline = i->op1;
		}
	} else if (i->op1 == JUMP) {
		switch (i->op2) {
		case OP2_0:
		case OP2_2:
		case OP2_4:
		case OP2_5:
		case OP2_6:
			iline = insn_offset24(i);
			break;
		case OP2_1:
			iline = insn_lpc(i);
			break;
		case OP2_3:
			iline = i->op1 | i->op2 << 5;
			break;
		default:
			iline = i->op1;
		}
	} else if (i->op1 == END) {
		iline = i->op1;
	}

	return iline;
}

void assemble(InstructionList *ilist, VarList *vlist, char *outfile)
{
	FILE *fp;
	if (outfile != NULL) {
		fp = fopen(outfile, "wb");
	} else {
		fp = fopen("kasm.out", "wb");
	}

	if (!fp) kasm_exit("Creating output file.", 0);

	// Begin with a zero, then write the file size
	int tmp = 0;
	fwrite(&tmp, 1, 4, fp);
	fwrite(&ilist->size, 1, 4, fp);

	data_offset = ilist->size + 1;

	write_data_header(fp, vlist);

	Instruction *current = ilist->start;
	while (current) {
		uint32_t insn = instruction_code_create(current, vlist);
		fwrite(&insn, 1, 4, fp);
		current = current->next;
	}
	
	fclose(fp);
}
