#ifndef __ASSEMBLE_H__
#define __ASSEMBLE_H__

#include <stdint.h>

#include "interpret.h"
#include "variables.h"

/*
 * Writes the bit string instructions to the output file.
 * If no output file is specified it writes "kasm.out".
 * Does no checks to see if the file exists.
 */
void assemble(InstructionList *, VarList *, char *);

#endif
