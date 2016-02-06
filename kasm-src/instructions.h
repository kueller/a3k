#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "split.h"
#include "kasm.h"

typedef enum _OpCode_ {
	INVALID = -1,
	ADD = 0b0001,
	ADDI = 0b0010,
	AND = 0b0011,
	INV = 0b0100,
	MULT = 0b0101,
	DIV = 0b0110,
	MOD = 0b0111,
	LDI = 0b1000,
	BLZ = 0b1001,
	BEZ = 0b1010,
	BGZ = 0b1011,
	JMP = 0b1100,
	JSR = 0b1101,
	RET = 0b1110,
	END = 0b1111
} OpCode;


typedef struct _inst_ {
	OpCode op;           // The bitwise opcode for the instruction
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

	int size;
} InstructionList;

// Instruction and Instruction List functions. Straightforward.
Instruction *new_instruction();
InstructionList *new_instruction_list();
void instruction_list_free(InstructionList *);
void instruction_append(InstructionList *, Instruction *);

/*
 * Finds the relative offset from the given instruction to the 
 * instruction with the label passed as a second parameter.
 */
int offset_to_label(Instruction *, char *);

#endif
