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

int is_valid_hex(char *param)
{
	if (!param) return 0;

	int i;
	for (i = 2; i < strlen(param); i++) {
		if ((param[i] < 48 || param[i] > 57) &&
			(param[i] < 97 || param[i] > 102))
			return 0;
	}

	return 1;
}

int ctoi(char c)
{
	return (int)c - 48;
}

int immediate_convert(char *imm, int line)
{
	int imm_value = 0;
	
	if (!strncmp(imm, "0x", 2)) {
		if (!is_valid_hex(imm))
			kasm_exit("Invalid immediate value.", line);
		imm_value = (int)strtol(imm, NULL, 0);
	} else {
		if (!is_valid_number(imm))
			kasm_exit("Invalid immediate value.", line);
		imm_value = (int)strtol(imm, NULL, 0);
	}

	return imm_value;
}

int get_register_index(char *param)
{
	if (strlen(param) < 2 || strlen(param) > 3)
		return -1;

	int r = -1;
	
	if (param[0] == 'r') {
		if (strlen(param) == 2) {
			if (IS_A_NUMBER(param[1]))
				r = ctoi(param[1]);
		} else if (strlen(param) == 3) {
			char rval[3] = {param[1], param[2], '\0'};
			if (is_valid_number(rval))
				r = atoi(rval);
		}
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

void get_opcodes(Instruction *i)
{
	if (!i)
		kasm_exit("Passed null instruction to opcode interpreter.", i->page);
	char *first = i->list->head->str;

	if (!strcmp(first, "add")) {
		i->op1 = ARITHMETIC;
		i->op2 = OP2_0;
	} else if (!strcmp(first, "addi")) {
		i->op1 = ARITHMETIC;
		i->op2 = OP2_1;
	} else if (!strcmp(first, "sub")) {
		i->op1 = ARITHMETIC;
		i->op2 = OP2_2;
	} else if (!strcmp(first, "subi")) {
		i->op1 = ARITHMETIC;
		i->op2 = OP2_3;
	} else if (!strcmp(first, "mult")) {
		i->op1 = ARITHMETIC;
		i->op2 = OP2_4;
	} else if (!strcmp(first, "div")) {
		i->op1 = ARITHMETIC;
		i->op2 = OP2_5;
	} else if (!strcmp(first, "mod")) {
		i->op1 = ARITHMETIC;
		i->op2 = OP2_6;
	} else if (!strcmp(first, "and")) {
		i->op1 = BITWISE;
		i->op2 = OP2_0;
	} else if (!strcmp(first, "andi")) {
		i->op1 = BITWISE;
		i->op2 = OP2_1;
	} else if (!strcmp(first, "or")) {
		i->op1 = BITWISE;
		i->op2 = OP2_2;
	} else if (!strcmp(first, "ori")) {
		i->op1 = BITWISE;
		i->op2 = OP2_3;
	} else if (!strcmp(first, "xor")) {
		i->op1 = BITWISE;
		i->op2 = OP2_4;
	} else if (!strcmp(first, "xori")) {
		i->op1 = BITWISE;
		i->op2 = OP2_5;
	} else if (!strcmp(first, "ldi")) {
		i->op1 = MEM;
		i->op2 = OP2_0;
	} else if (!strcmp(first, "ld")) {
		i->op1 = MEM;
		i->op2 = OP2_1;
	} else if (!strcmp(first, "st")) {
		i->op1 = MEM;
		i->op2 = OP2_2;
	} else if (!strcmp(first, "lpc")) {
		i->op1 = MEM;
		i->op2 = OP2_3;
	} else if (!strcmp(first, "str")) {
		i->op1 = MEM;
		i->op2 = OP2_4;
	} else if (!strcmp(first, "ldr")) {
		i->op1 = MEM;
		i->op2 = OP2_5;
	} else if (!strcmp(first, "sl")) {
		i->op1 = SHIFT;
		i->op2 = OP2_0;
	} else if (!strcmp(first, "sli")) {
		i->op1 = SHIFT;
		i->op2 = OP2_1;
	} else if (!strcmp(first, "sr")) {
		i->op1 = SHIFT;
		i->op2 = OP2_2;
	} else if (!strcmp(first, "sri")) {
		i->op1 = SHIFT;
		i->op2 = OP2_3;
	} else if (!strcmp(first, "j")) {
		i->op1 = JUMP;
		i->op2 = OP2_0;
	} else if (!strcmp(first, "jr")) {
		i->op1 = JUMP;
		i->op2 = OP2_1;
	} else if (!strcmp(first, "jsr")) {
		i->op1 = JUMP;
		i->op2 = OP2_2;
	} else if (!strcmp(first, "ret")) {
		i->op1 = JUMP;
		i->op2 = OP2_3;
	} else if (!strcmp(first, "blz")) {
		i->op1 = JUMP;
		i->op2 = OP2_4;
	} else if (!strcmp(first, "bez")) {
		i->op1 = JUMP;
		i->op2 = OP2_5;
	} else if (!strcmp(first, "bgz")) {
		i->op1 = JUMP;
		i->op2 = OP2_6;
	} else if (!strcmp(first, "end")) {
		i->op1 = END;
	} else {
		i->op1 = INVALID;
	}
}

void verify_instruction(Instruction *inst)
{
	if (!inst) kasm_exit("Passed null instruction list to verify.", 0);
	if (!inst->list)
		kasm_exit("Passed instruction with null string list to verify.", inst->page);

	int correct_size = 0;

	if (inst->op1 == ARITHMETIC) {
		correct_size = inst->list->size == 4;
	} else if (inst->op1 == BITWISE) {
		correct_size = inst->list->size == 4;
	} else if (inst->op1 == MEM) {
		if (inst->op2 == OP2_3) {
			correct_size = inst->list->size == 2;
		} else {
			correct_size = inst->list->size == 3;
		}
	} else if (inst->op1 == SHIFT) {
		correct_size = inst->list->size == 4;
	} else if (inst->op1 == JUMP) {
		if (inst->op2 == OP2_3) {
			correct_size = inst->list->size == 1;
		} else {
			correct_size = inst->list->size == 2;
		}
	} else if (inst->op1 == END) {
		correct_size = 1;
	} else {
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
		get_opcodes(current);
		if (current->op1 == INVALID) {
			strcpy(current->label, current->list->head->str);
			remove_first(current->list);
			if (current->list->size == 0)
				kasm_exit("Labels on their own lines not allowed.", current->page);
			get_opcodes(current);
			if (current->op1 == INVALID)
				kasm_exit("Invalid instruction.", current->page);
		}
		verify_instruction(current);
		current = current->next;
	}
}

void index_in_range(int index, int line)
{
	if (index < 0 || index > 31)
		kasm_exit("Out of range register index.", line);
}

