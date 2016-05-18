#include "a3ksetup.h"

static uint32_t mem_size = 0;
static uint32_t data_offset = 0;

uint32_t current_mem_size()
{
	return mem_size;
}

uint32_t program_offset()
{
	return data_offset;
}

uint32_t *initialize_regfile()
{
	// The 9th register is for storing the return address for a JSR
    uint32_t *reg = calloc(DEFAULT_REG_SIZE, sizeof(uint32_t));
	return reg;
}

uint32_t *initialize_memory()
{
	uint32_t *mem = calloc(DEFAULT_MEM_SIZE + DEFAULT_VID_MEM_SIZE,
						   sizeof(uint32_t));
	mem_size = DEFAULT_MEM_SIZE + DEFAULT_VID_MEM_SIZE;
	return mem;
}

int load_program(uint32_t *mem, const char *filename)
{
	if (!mem) return A3K_NULL_PTR;
	
	FILE *fp = fopen(filename, "rb");
	if (!fp) return A3K_IO_ERR;

	uint32_t insn = 0;
	int i = 0; // memory index

	uint32_t prog_length = 0;

	// Read leading 0
	if (fread(&insn, sizeof(uint32_t), 1, fp) != 1)
		return A3K_IO_ERR;

	// Read program length
	if (fread(&prog_length, sizeof(uint32_t), 1, fp) != 1)
		return A3K_IO_ERR;

	if (prog_length > mem_size)
		return A3K_OVERFLOW;
	data_offset = prog_length + 1;

	// Read separating 0
	if (fread(&insn, sizeof(uint32_t), 1, fp) != 1)
		return A3K_IO_ERR;

	// Read variable data (see kasm-src/assemble.c: write_data_header)
	uint32_t type, value, addr;
	if (fread(&type, sizeof(uint32_t), 1, fp) != 1)
		return A3K_IO_ERR;
	if (type != 0) {
		if (data_offset > mem_size - 1)
			return A3K_OVERFLOW;
		
		while (type != 0) {
			if (fread(&value, sizeof(uint32_t), 1, fp) != 1)
				return A3K_IO_ERR;
			if (fread(&addr, sizeof(uint32_t), 1, fp) != 1)
				return A3K_IO_ERR;

			if (type == TYPE_DATA) {
				if ((data_offset + addr) > (mem_size - 1))
					return A3K_OVERFLOW;
				mem[data_offset + addr] = value;
			} else if (type == TYPE_ARRAY) {
				if ((data_offset + addr + value) > (mem_size - 1))
					return A3K_OVERFLOW;
			} else {
				return A3K_IO_ERR;
			}

			if (fread(&type, sizeof(uint32_t), 1, fp) != 1)
				return A3K_IO_ERR;
		}
	}

	while (fread(&insn, sizeof(uint32_t), 1, fp) == 1) {
		mem[i++] = insn;
	}

	fclose(fp);

	return A3K_IDLE;
}
