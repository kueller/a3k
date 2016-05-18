#ifndef __INTERPRET_H__
#define __INTERPRET_H__

#include "instructions.h"
#include "kasm.h"

#define IS_A_LETTER(x) ((x >= 65 && x <= 90) || (x >= 97 && x <= 122))
#define IS_A_NUMBER(x) (x >= 48 && x <= 57)

/*
 * Determines if the passed string has no non-digit representing characters.
 */
int is_valid_number(char *);

/*
 * Converts the immediate value strings to an integer.
 * Uses strtol, so strings starting with 0x will be converted as hex.
 * Strings starting with 0 will be treated as octal, and the rest will
 * be treated as decimal. Takes the immediate string and line number.
 */
int immediate_convert(char *, int);

/*
 * Converts a given string (R#) into the register number (0-31).
 */
int get_register_index(char *);

/*
 * Checks if register value is between 0 and 31, inclusive.
 * Does not return, function exits program as failure if value is out of range.
 */
void index_in_range(int, int);

/*
 * Gets the numerical opcode for the instruction (see instructions.h).
 * If there is a label, it will parse the label into the label variable in
 * the Instruction struct.
 * Finally, verifies the instruction has the right number of tokens.
 */
void setup_instruction_list(InstructionList *);

#endif
