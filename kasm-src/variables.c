#include "variables.h"
#include "interpret.h"

VarList *varlist_create()
{
	VarList *v = malloc(sizeof(VarList));
	if (!v) kasm_exit("Memory error creating variable list.", 0);

	v->head = NULL;
	v->tail = NULL;
	v->size = 0;

	return v;
}

Var *var_create(char *name)
{
	Var *v = malloc(sizeof(Var));
	if (!v) kasm_exit("Memory error creating variable structure.", 0);

	char *dup = strdup(name);
	if (!dup) kasm_exit("Memory error creating type Var.", 0);

	v->type = NONE;
	v->name = dup;
	v->value = 0;
	v->addr = 0;

	v->prev = NULL;
	v->next = NULL;

	return v;
}

void var_free(Var *v)
{
	if (v->name) free(v->name);
	if (v) free(v);
}

void varlist_free(VarList *list)
{
	if (!list) return;

	Var *current = list->head;

	while (current) {
		Var *tmp = current;
		current = current->next;
		var_free(tmp);
	}

	free(list);
}

void verify_variable_name(char *name, int line)
{
	if (!IS_A_LETTER(name[0]))
		kasm_exit("Variable name must start with a letter.", line);
	
	int i;
	for (i = 1; name[i]; i++) {
		// This many parentheses aren't needed but the compiler wanted them.
		if ((!IS_A_LETTER(name[i])) && (!IS_A_NUMBER(name[i])) && (name[i] != '_'))
			kasm_exit("Only alphanumeric characters and underscores allowed "
					  "for variable name.", line);
	}
}

int link_var_name_to_address(VarList *list, char *name)
{
	if (!list)
		kasm_exit("Invalid variable list to link function.", 0);
	if (!name)
		return -1;

	Var *current = list->head;
	while(current) {
		if (!strcmp(name, current->name))
			return current->addr;
		current = current->next;
	}

	return -1;
}

int variable_append(VarList *list, Instruction *i, int addr)
{
	if (!i) kasm_exit("Null instruction in variable structure.", 0);
	if (!list) kasm_exit("Invalid variable list for var.", i->page);

	if (i->list->size < 3)
		kasm_exit("Variable syntax error.", i->page);

	int next_addr;
	
	StrNode *data_type = i->list->head;
	StrNode *name = data_type->next;
	StrNode *value_tok = name->next;

	verify_variable_name(name->str, i->page);

	int value = immediate_convert(value_tok->str, i->page);
	Var *v = NULL;

	if (!strcmp(".data", data_type->str)) {
		v = var_create(name->str);
		v->type = DATA;
		v->value = value;
		v->addr = addr;
		next_addr = addr + 1;
	} else if (!strcmp(".array", data_type->str)) {
		v = var_create(name->str);
		v->type = ARRAY;
		v->value = value;
		v->addr = addr;
		next_addr = addr + value;
	} else {
		kasm_exit("Invalid data type.", i->page);
	}

	// Hack solution using the link function to check for duplicates
	if (link_var_name_to_address(list, v->name) != -1)
		kasm_exit("Duplicate variable name found.", i->page);

	if (list->size == 0) {
		list->head = v;
		list->tail = v;
	} else {
		v->prev = list->tail;
		list->tail->next = v;
		list->tail = v;
	}

	list->size++;
	return next_addr;
}

VarList *setup_variables(InstructionList *list)
{
	if (!list) kasm_exit("Passed null list to variable pass.", 0);
	if (list->size == 0) return NULL;

	VarList *v = varlist_create();

	int local_addr = 0;
	
	Instruction *current = list->start;
	while(current) {
		int index = current->index;
		StrNode *n = current->list->head;
		
		if (n->str[0] == '.') {
			local_addr = variable_append(v, current, local_addr);
			current = current->next;
			instruction_list_remove(list, index);
		} else {
			current = current->next;
		}
	}

	return v;
}

