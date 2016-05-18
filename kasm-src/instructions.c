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

	new->var_list = NULL;

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

void instruction_list_remove(InstructionList *list, int index)
{
	if (!list) kasm_exit("Passed null instruction list to remove.", 0);
	if (index < 0 || index > (list->size - 1))
		kasm_exit("Out of range index for instruction remove.", 0);

	if (!list->start) return;

	if (list->size == 1) {
		instruction_free(list->start);
		list->start = NULL;
		list->end = NULL;
		list->size--;
	} else {
		if (index == 0) {
			Instruction *tmp = list->start;
			list->start->next->prev = NULL;
			list->start = list->start->next;
			instruction_free(tmp);
			list->size--;
		} else if (index == (list->size - 1)) {
			Instruction *tmp = list->end;
			list->end->prev->next = NULL;
			list->end = list->end->prev;
			instruction_free(tmp);
			list->size--;
		} else {
			Instruction *current = list->start;
			int scroll;
			for (scroll = 0; scroll < index; scroll++)
				current = current->next;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			instruction_free(current);
			list->size--;
		}
	}

	Instruction *current = list->start;
	while (current) {
		current->index--;
		current = current->next;
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
