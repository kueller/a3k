#ifndef __A3KSETUP_H__
#define __A3KSETUP_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TYPE_DATA  0b01
#define TYPE_ARRAY 0b10

#define ARITHMETIC 0b00000
#define BITWISE    0b00001
#define MEM        0b00010
#define SHIFT      0b00011
#define JUMP       0b00100
#define END        0b11111

#define	OP2_0 0b000
#define	OP2_1 0b001
#define	OP2_2 0b010
#define	OP2_3 0b011
#define	OP2_4 0b100
#define	OP2_5 0b101
#define	OP2_6 0b110
#define	OP2_7 0b111

#define OP_MASK  0x0000001f
#define OP2_MASK 0x00000007
#define REG_MASK 0x0000001f

#define IMM_EXT14 0xffffc000
#define IMM_EXT19 0xfff80000
#define IMM_EXT24 0xff000000

#define IMM_SHIFT_MASK 0x0000001f

#define DEFAULT_REG_SIZE 32
#define DEFAULT_MEM_SIZE 4000
#define DEFAULT_VID_MEM_SIZE 800

// Return codes
#define A3K_RUNNING   0
#define A3K_IDLE      1
#define A3K_OVERFLOW -1
#define A3K_MEM_ERR   2
#define A3K_NULL_PTR  3
#define A3K_IO_ERR    4
#define A3K_OUT_OF_RANGE 5
#define A3K_DIVIDE_BY_ZERO 6

#ifdef __cplusplus
extern "C" {
#endif
	/*
	 * Returns the length of memory;
	 * 0 if the register has not been initialized.
	 */
	uint32_t current_mem_size();

	/*
	 * Returns the offset to data (program size + 1)
	 * 0 if nothing has been initialized
	 */
	uint32_t program_offset();

	/*
	 * Initializes the memory register.
	 * Returns an array of length 32.
	 * Returns NULL on failure.
	 */
	uint32_t *initialize_regfile();

	/*
	 * Initializes the memory for the program.
	 * Memory consists of a base memory size and then a chunk of video
	 * memory, size specified by DEFAULT_VID_MEM_SIZE.
	 * The base memory size is 100 entries, defined by DEFAULT_MEM_SIZE.
	 * Base memory will include program and user data.
	 * Returns null on failure.
	 */
	uint32_t *initialize_memory();

	/*
	 * Creates the instruction register from the given input binary file.
	 * Returns an A3K code (defined above).
	 * A3K_IDLE means success.
	 */
	int load_program(uint32_t *mem, const char *filename);
#ifdef __cplusplus
}
#endif
	
#endif
