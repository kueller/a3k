#ifndef __FILEREAD_H__
#define __FILEREAD_H__

#include "kasm.h"
#include "instructions.h"
#include "interpret.h"

/*
 * Reads the assembly program file and creates the parsing structures.
 * Exits on standard I/O errors.
 */
InstructionList *create_instructions_from_file(char *);

#endif
