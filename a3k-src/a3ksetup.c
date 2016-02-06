#include "a3ksetup.h"

static int isr_len = 0;

int isr_length() {
	return isr_len;
}

int *initialize_regfile()
{
	// The 9th register is for storing the return address for a JSR
    int *reg = calloc(9, sizeof(int));
	return reg;
}

uint16_t *initialize_instruction_reg(const char *filename)
{
	FILE *fp = fopen(filename, "rb");
	if (!fp) return NULL;

    uint16_t *isr = malloc(sizeof(uint16_t));
	if (!isr) return NULL;

	uint16_t insn = 0;
	int i = 0;

	if (fread(&insn, sizeof(uint16_t), 1, fp) == 1) {
		isr[i] = insn;
		i++;
	} else {
		return NULL;
	}

	while (fread(&insn, sizeof(uint16_t), 1, fp) == 1) {
        uint16_t *__isr = realloc(isr, sizeof(uint16_t) * (i + 1));
        if (!__isr) return NULL;

        isr = __isr;
		isr[i] = insn;
		i++;
	}

	isr_len = i;
	fclose(fp);

	return isr;
}
