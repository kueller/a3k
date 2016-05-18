#ifndef __EXECUTE_H__
#define __EXECUTE_H__

#include "a3ksetup.h"

#define RUNNING 1
#define IDLE    0

#ifdef __cplusplus
extern "C" {
#endif

	/*
	 * Returns the current position (value) of the program counter.
	 * Returns 0 if the program hasn't started.
	 * 0 is also a valid running value.
	 */
	uint32_t current_pc();

	/*
	 * Resets the PC to 0 for a new program.
	 */
	void reset_pc();

	/*
	 * Executes the next instruction given the instruction and data registers
	 * passed in as parameters. The PC is locally stored.
	 * Returns 1 if the program is still active.
	 * Returns 0 if the program has finished (END) or hasn't started.
	 * Returns MEM_ERR for uninitialized memory or register files.
	 * Returns OUT_OF_RANGE for out of range memory addresses.
	 * Returns IO_ERR for syntax errors in the file encoding.
	 * Returns DIVIDE_BY_ZERO for the obvious.
	 * Please do not change any of the registers mid-execution, obviously.
	 */
    int execute_next(uint32_t *, uint32_t *);
	
#ifdef __cplusplus
}
#endif

#endif
