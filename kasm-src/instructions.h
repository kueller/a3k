#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "split.h"
#include "kasm.h"

typedef enum _OpCode1_ {
	INVALID    = -1,
	ARITHMETIC = 0b00000,
	BITWISE    = 0b00001,
	MEM        = 0b00010,
	SHIFT      = 0b00011,
	JUMP       = 0b00100,
	END        = 0b11111
} OpCode_1;

typedef enum _OpCode2_ {
	OP2_0 = 0b000,
	OP2_1 = 0b001,
	OP2_2 = 0b010,
	OP2_3 = 0b011,
	OP2_4 = 0b100,
	OP2_5 = 0b101,
	OP2_6 = 0b110,
	OP2_7 = 0b111
} OpCode_2;


typedef struct _inst_ {
	OpCode_1 op1;        // The bitwise opcode for the instruction
	OpCode_2 op2;        // The 2nd part of the opcode
	char *label;         // Separated label for jump instructions.
	StringList *list;    // Tokenized split string for the instruction line

	int index;           // Index in the instruction list. Will be the "address"
	int page;            // Line number of the file, used for errors.

	struct _inst_ *prev;
	struct _inst_ *next;
} Instruction;

typedef struct _inst_list_ {
	Instruction *start;
	Instruction *end;
	Instruction *pc;

	StringList *var_list;

	int size;
} InstructionList;

// Instruction and Instruction List functions. Straightforward.
Instruction *new_instruction();
InstructionList *new_instruction_list();
void instruction_list_remove(InstructionList *, int index);
void instruction_list_free(InstructionList *);
void instruction_append(InstructionList *, Instruction *);

/*
 * Finds the relative offset from the given instruction to the 
 * instruction with the label passed as a second parameter.
 */
int offset_to_label(Instruction *, char *);

#endif
