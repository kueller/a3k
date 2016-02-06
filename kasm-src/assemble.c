#include <stdio.h>
#include "assemble.h"

/*
 * Creates the 16 bit instruction for each Instruction struct passed.
 * See documentation for how bit strings are organized.
 */
int instruction_code_create(Instruction *i)
{
	int iline = 0;
	switch (i->op) {
	case ADD:
	case AND:
	case MULT:
	case DIV:
	case MOD:
	{
		StrNode *n = i->list->head;
		n = n->next;
		int dest = get_register_index(n->str);
		n = n->next;
		int op1 = get_register_index(n->str);
		n = n->next;
		int op2 = get_register_index(n->str);

		index_in_range(dest);
		index_in_range(op1);
		index_in_range(op2);

		iline = i->op | op2 << 4 | op1 << 7 | dest << 10;
		break;
	}
	case ADDI:
	{
		StrNode *n = i->list->head;
		n = n->next;
		int dest = get_register_index(n->str);
		n = n->next;
		int op1 = get_register_index(n->str);
		n = n->next;
		is_valid_number(n->str);
		int imm = atoi(n->str);

		index_in_range(dest);
		index_in_range(op1);

		iline = ADDI | op1 << 4 | dest << 7 | imm << 10;
		break;
	}
	case INV:
	{
		StrNode *n = i->list->head;
		int op = get_register_index(n->next->str);
		index_in_range(op);

		iline = INV | op << 4;
		break;
	}
	case LDI:
	{
		StrNode *n = i->list->head;
		n = n->next;
		int dest = get_register_index(n->str);
		n = n->next;
		is_valid_number(n->str);
		int imm = atoi(n->str);

		index_in_range(dest);

		iline = LDI | dest << 4 | imm << 7;
		break;
	}
	case BLZ:
	case BEZ:
	case BGZ:
	case JMP:
	case JSR:
	{
		StrNode *n = i->list->head;
		char *label = n->next->str;
		iline = i->op | offset_to_label(i, label) << 4;
		break;
	}
	case RET:
	case END:
		iline = i->op;
	default:
		iline = i->op;
	}

	return iline;
}

void assemble(InstructionList *list, char *outfile)
{
	FILE *fp;
	if (outfile != NULL) {
		fp = fopen(outfile, "wb");
	} else {
		fp = fopen("kasm.out", "wb");
	}

	if (!fp) kasm_exit("Creating output file.", 0);

	Instruction *current = list->start;
	while (current) {
		int insn = instruction_code_create(current);
		fwrite(&insn, 1, 2, fp);
		current = current->next;
	}
	
	fclose(fp);
}
