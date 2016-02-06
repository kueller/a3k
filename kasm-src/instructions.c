#include "instructions.h"

Instruction *new_instruction()
{
	Instruction *new = (Instruction *)malloc(sizeof(Instruction));
	if (!new) kasm_exit("Memory error creating type Instruction.", 0);

	new->label = (char *)calloc(100, sizeof(char));
	if (!new->label) kasm_exit("Memory error creating type Instruction.", 0);

	new->list = NULL;

	new->prev = NULL;
	new->next = NULL;

	new->index = 0;

	return new;
}

InstructionList *new_instruction_list()
{
	InstructionList *new = (InstructionList *)malloc(sizeof(InstructionList));
	if (!new) kasm_exit("Memory error creating type InstructionList.", 0);
	
	new->start = NULL;
	new->end = NULL;
	new->pc = NULL;

	new->size = 0;

	return new;
}

void instruction_free(Instruction *inst)
{
	if (inst) {
		if (inst->label) free(inst->label);
		if (inst->list) string_list_free(inst->list);
		free(inst);
	}
}

void instruction_list_free(InstructionList *list)
{
	if (list) {
		Instruction *current = list->start;
		while (current != NULL) {
			Instruction *tmp = current;
			current = current->next;
			free(tmp);
		}

		free(list);
	}
}

void instruction_append(InstructionList *list, Instruction *inst)
{
	if (!list) kasm_exit("Passed null list to instruction append function.", 0);
	if (!inst) kasm_exit("Passed null instruction to append function.", 0);

	if (list->size == 0) {
		list->start = inst;
		list->end = inst;
		inst->index = 0;
	} else {
		list->end->next = inst;
		inst->prev = list->end;
		list->end = inst;
		inst->index = list->size;
	}

	list->size++;
}

int offset_to_label(Instruction *i, char *label)
{
	if (!i) kasm_exit("Passed invalid instruction.", i->page);

	Instruction *current = i;
	int offset = 0;
	while (current) {
		if (!strcmp(label, current->label))
			return offset;
		current = current->prev;
		offset--;
	}

	current = i;
	offset = 0;
	while (current) {
		if (!strcmp(label, current->label))
			return offset;
		current = current->next;
		offset++;
	}
		
	kasm_exit("Label not found for control offset instruction.", i->page);
	return offset;
}
