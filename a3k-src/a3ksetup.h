#ifndef __A3KSETUP_H__
#define __A3KSETUP_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ADD  0b0001
#define ADDI 0b0010
#define AND  0b0011
#define INV  0b0100
#define MULT 0b0101
#define DIV  0b0110
#define MOD  0b0111
#define LDI  0b1000
#define BLZ  0b1001
#define BEZ  0b1010
#define BGZ  0b1011
#define JMP  0b1100
#define JSR  0b1101
#define RET  0b1110
#define END  0b1111

#define OP_MASK  0x000f
#define REG_MASK 0x0007

#define IMM6_EXT  0xffc0
#define IMM9_EXT  0xfe00
#define IMM12_EXT 0xf000

#ifdef __cplusplus
extern "C" {
#endif
	/*
	 * Returns the length of the instruction register.
	 * 0 if the register has not been initialized.
	 */
	int isr_length();

	/*
	 * Initializes the memory register.
	 * An int array of length 9. 8 registers are addressable by instructions.
	 * Register 9 stores the return address from JSR calls for RET.
	 */
	int *initialize_regfile();

	/*
	 * Creates the instruction register from the given input binary file.
	 * Returns NULL on any errors.
	 */
        uint16_t *initialize_instruction_reg(const char *);
#ifdef __cplusplus
}
#endif
	
#endif
