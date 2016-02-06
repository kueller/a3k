#ifndef __INTERPRET_H__
#define __INTERPRET_H__

#include "instructions.h"
#include "kasm.h"

/*
 * Determines if the passed string has no non-digit representing characters.
 */
int is_valid_number(char *);

/*
 * Converts a given string (R#) into the register number (0-7).
 */
int get_register_index(char *);

/*
 * Checks if register value is between 0 and 7, inclusive.
 * Does not return, function exits program as failure if value is out of range.
 */
void index_in_range(int);

/*
 * Gets the numerical opcode for the instruction (see instructions.h).
 * If there is a label, it will parse the label into the label variable in
 * the Instruction struct.
 * Finally, verifies the instruction has the right number of tokens.
 */
void setup_instruction_list(InstructionList *);
#if 0
void kasm_add(int *, char *, char *, char *);
void kasm_addi(int *, char *, char *, char *);
void kasm_and(int *, char *, char *, char *);
void kasm_inv(int *, char *);
void kasm_mult(int *, char *, char *, char *);
void kasm_div(int *, char *, char *, char *);
void kasm_mod(int *, char *, char *, char *);
void kasm_ld(int *, char *, char *);
int kasm_branch(int *, OpCode, InstructionList *, char *);
void kasm_jmp(InstructionList *, char *);
#endif
#endif
