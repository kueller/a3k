#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#include "kasm.h"
#include "instructions.h"

typedef enum _vardata_ {
	NONE  = 0,
	DATA  = 0b01,
	ARRAY = 0b10
} DataType;

typedef struct _var_ {
	DataType type;
	char *name;
	int value;
	int addr;

	struct _var_ *prev;
	struct _var_ *next;
} Var;

typedef struct _varlist_ {
	Var *head;
	Var *tail;

	int size;
} VarList;

/*
 * Destructor function for the variable list.
 * Does not free the "name" value in the Var structs, since this
 * is not allocated in the constructor function.
 */
void varlist_free(VarList *);

/*
 * This is the variable linker. It will be given a label/name,
 * and search for it in the variable list. 
 * Function return the addr value for the variable. If no variable
 * matches the label, -1 is returned.
 */
int link_var_name_to_address(VarList *, char *);

/*
 * Will search the instruction list for variable declarations.
 * If found, it will create a variable structure and then remove
 * that entry from the instruction list (as these are not valid instructions.)
 * Returns the resulting variable list. List may be empty.
 */
VarList *setup_variables(InstructionList *);

#endif
