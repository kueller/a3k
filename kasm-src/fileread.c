#include <stdio.h>
#include <ctype.h>
#include "fileread.h"

int whitespace_or_comment_line(char *line)
{
	int i;
	for (i = 0; line[i]; i++) {
		if (!isspace((int)line[i]) && (line[i] != '#'))
			return 0;
		if (line[i] == '#')
			return 1;
	}
	return 1;
}

void str_to_lower(char *line)
{
	int i;
	for (i = 0; i < strlen(line); i++) {
		if (line[i] >= 65 && line[i] <= 90)
			line[i] = line[i] + 32;
	}
}

InstructionList *create_instructions_from_file(char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (!fp) kasm_exit("Reading input file.", 0);

	InstructionList *list = new_instruction_list();

	int current_page = 1;
	char line[MAX_LENGTH];
	while (fgets(line, MAX_LENGTH, fp) != NULL) {
		if (!whitespace_or_comment_line(line)) {
			str_to_lower(line);
			StringList *s = split_string(line);

			Instruction *inst = new_instruction();
			inst->list = s;
			inst->page = current_page;
			instruction_append(list, inst);
		}
		current_page++;
	}

	if (fclose(fp) == EOF)
		kasm_exit("Closing input file.", 0);

	return list;
}
