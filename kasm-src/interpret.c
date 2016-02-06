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

