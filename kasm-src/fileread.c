#include <stdio.h>
#include "fileread.h"

InstructionList *create_instructions_from_file(char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (!fp) kasm_exit("Reading input file.", 0);

	InstructionList *list = new_instruction_list();

	int current_page = 1;
	char line[MAX_LENGTH];
	while (fgets(line, MAX_LENGTH, fp) != NULL) {
		if (strlen(line) < 5 || line[0] == '#') {
			current_page++;
			continue;
		}
		
		StringList *s = split_string(line);

		Instruction *inst = new_instruction();
		inst->list = s;
		inst->page = current_page;
		instruction_append(list, inst);
		
		current_page++;
	}

	setup_instruction_list(list);

	if (fclose(fp) == EOF)
		kasm_exit("Closing input file.", 0);

	return list;
}
