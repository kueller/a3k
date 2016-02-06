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
	 */
	int current_pc();

	/*
	 * Resets the PC to 0 for a new program.
	 */
	void reset_pc();

	/*
	 * Executes the next instruction given the instruction and data registers
	 * passed in as parameters. The PC is locally stored.
	 * Returns 1 if the program is still active.
	 * Returns 0 if the program has finished (END) or hasn't started.
	 * Please do not change any of the registers mid-execution, obviously.
	 */
	int execute_next(uint16_t *, int *);
	
#ifdef __cplusplus
}
#endif

#endif
