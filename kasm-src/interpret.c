#include "interpret.h"
#include <stdio.h>

int is_valid_number(char *param)
{
	if (!param) return 0;
	
	int i;
	for (i = 0; i < strlen(param); i++) {
		if ((param[i] < 48 || param[i] > 57) &&
			(param[i] != '+' && param[i] != '-'))
			return 0;
	}

	return 1;
}

int ctoi(char c)
{
	return (int)c - 48;
}

int get_register_index(char *param)
{
	if (strlen(param) != 2)
		return -1;

	int r = -1;
	
	if (param[0] == 'r') {
		r = ctoi(param[1]);
		if (r < 0 || r > 7)
			r = -1;
	}

	return r;
}

void strip_comment(StringList *list)
{
	if (!list) return;
	
	int commented = 0;
	int i;

	StrNode *current = list->head;
	
	for (i = 0; i < list->size; i++) {
		if (current->str[0] == '#') {
			commented = 1;
			break;
		}
		current = current->next;
	}

	if (commented) {
		while (list->size > i) {
			string_list_remove_at(list, i);
		}
	}
}

OpCode get_opcode(StringList *list)
{
	if (!list) kasm_exit("Passed null list to opcode interpreter.", 0);
	char *first = list->head->str;

	if (!strcmp(first, "add"))
		return ADD;
	else if (!strcmp(first, "addi"))
		return ADDI;
	else if (!strcmp(first, "and"))
		return AND;
	else if (!strcmp(first, "inv"))
		return INV;
	else if (!strcmp(first, "mult"))
		return MULT;
	else if (!strcmp(first, "div"))
		return DIV;
	else if (!strcmp(first, "mod"))
		return MOD;
	else if (!strcmp(first, "ldi"))
		return LDI;
	else if (!strcmp(first, "blz"))
		return BLZ;
	else if (!strcmp(first, "bez"))
		return BEZ;
	else if (!strcmp(first, "bgz"))
		return BGZ;
	else if (!strcmp(first, "jmp"))
		return JMP;
	else if (!strcmp(first, "jsr"))
		return JSR;
	else if (!strcmp(first, "ret"))
		return RET;
	else if (!strcmp(first, "end"))
		return END;
	else
		return INVALID;
	return INVALID;
}

void verify_instruction(Instruction *inst)
{
	if (!inst) kasm_exit("Passed null instruction list to verify.", 0);
	if (!inst->list)
		kasm_exit("Passed instruction with null string list to verify.", inst->page);

	int correct_size = 0;
	
	switch (inst->op) {
	case ADD:
	case ADDI:
	case AND:
	case MULT:
	case DIV:
	case MOD:
		correct_size = inst->list->size == 4;
		break;
	case INV:
	case BLZ:
	case BEZ:
	case BGZ:
	case JMP:
	case JSR:
		correct_size = inst->list->size == 2;
		break;
	case LDI:
		correct_size = inst->list->size == 3;
		break;
	case RET:
	case END:
		correct_size = inst->list->size == 1;
		break;
	default:
		kasm_exit("Invalid opcode during instruction verification.", inst->page);
	}

	if (!correct_size)
		kasm_exit("Invalid parameters in instruction.", inst->page);
}

void setup_instruction_list(InstructionList *list)
{
	if (!list) kasm_exit("Passed null list to instruction setup function.", 0);
	if (list->size == 0) kasm_exit("No instructions passed to setup function.", 0);
	
	Instruction *current = list->start;
	while (current != NULL) {
		strip_comment(current->list);
		OpCode code = get_opcode(current->list);
		if (code == INVALID) {
			strcpy(current->label, current->list->head->str);
			remove_first(current->list);
			code = get_opcode(current->list);
			if (code == INVALID)
				kasm_exit("Invalid instruction.", current->page);
		}
		current->op = code;
		verify_instruction(current);
		current = current->next;
	}
}

void index_in_range(int index)
{
	if (index < 0 || index > 7)
		kasm_exit("Out of range register index.", 0);
}

#if 0
void kasm_add(int *reg, char *op1, char *op2, char *dest)
{
	if (!reg) kasm_exit("Invalid register file.", 0);

	int src1 = get_register_index(op1);
	int src2 = get_register_index(op2);
	int dst  = get_register_index(dest);
	
	index_in_range(src1);
	index_in_range(src2);
	index_in_range(dst);

	reg[dst] = reg[src1] + reg[src2];
}

void kasm_addi(int *reg, char *op1, char *imm, char *dest)
{
	if (!reg) kasm_exit("Invalid register file.", 0);

	if (!is_valid_number(imm))
		kasm_exit("Invalid immediate value for addi", 0);

	int src1 = get_register_index(op1);
	int dst  = get_register_index(dest);

	int value = atoi(imm);

	index_in_range(src1);
	index_in_range(dst);

	reg[dst] = reg[src1] + value;
}

void kasm_and(int *reg, char *op1, char *op2, char *dest)
{
	if (!reg) kasm_exit("Invalid register file.", 0);

	int src1 = get_register_index(op1);
	int src2 = get_register_index(op2);
	int dst  = get_register_index(dest);

	index_in_range(src1);
	index_in_range(src2);
	index_in_range(dst);

	reg[dst] = reg[src1] & reg[src2];
}
	
void kasm_inv(int *reg, char *op1)
{
	if (!reg) kasm_exit("Invalid register file.", 0);

	int src = get_register_index(op1);
	index_in_range(src);

	reg[src] = 0 - reg[src];
}

void kasm_mult(int *reg, char *op1, char *op2, char *dest)
{
	if (!reg) kasm_exit("Invalid register file.", 0);

	int src1 = get_register_index(op1);
	int src2 = get_register_index(op2);
	int dst  = get_register_index(dest);

	index_in_range(src1);
	index_in_range(src2);
	index_in_range(dst);

	reg[dst] = reg[src1] * reg[src2];
}

void kasm_div(int *reg, char *op1, char *op2, char *dest)
{
	if (!reg) kasm_exit("Invalid register file.", 0);

	int src1 = get_register_index(op1);
	int src2 = get_register_index(op2);
	int dst  = get_register_index(dest);

	index_in_range(src1);
	index_in_range(src2);
	index_in_range(dst);

	reg[dst] = (int)(reg[src1] / reg[src2]);
}

void kasm_mod(int *reg, char *op1, char *op2, char *dest)
{
	if (!reg) kasm_exit("Invalid register file.", 0);

	int src1 = get_register_index(op1);
	int src2 = get_register_index(op2);
	int dst  = get_register_index(dest);

	index_in_range(src1);
	index_in_range(src2);
	index_in_range(dst);
	
	reg[dst] = (int)(reg[src1] % reg[src2]);
}

void kasm_ld(int *reg, char *dest, char *imm)
{
	if (!reg) kasm_exit("Invalid register file.", 0);

	if (!is_valid_number(imm))
		kasm_exit("Invalid immediate value for ld", 0);

	int dst = get_register_index(dest);
	int value = atoi(imm);

	index_in_range(dst);

	reg[dst] = value;
}

int kasm_branch(int *reg, OpCode code, InstructionList *list, char *label)
{
	if (!reg) kasm_exit("Invalid register file.", 0);

	int ret = 0;
	
	if (code == BNZ) {
		if (reg[0] < 0) shift_to_label(list, label);
		else ret = 1;
	} else if (code == BEZ) {
		if (reg[0] == 0) shift_to_label(list, label);
		else ret = 1;
	} else if (code == BGZ) {
		if (reg[0] > 0) shift_to_label(list, label);
		else ret = 1;
	}
	
	return ret;
}

void kasm_jmp(InstructionList *list, char *label)
{
	shift_to_label(list, label);
}
#endif
