#include <stdio.h>
#include "fileread.h"
#include "assemble.h"

void kasm_exit(char *message, int page)
{
	fprintf(stderr, "Error: ");
	if (page > 0) fprintf(stderr, "%d: ", page);
	fprintf(stderr, "%s\n", message);
	exit(1);
}

int main(int argc, char **argv)
{
	char *filename = NULL;
	char *outfile = NULL;

	if (argc > 1 && !strcmp(argv[1], "--help")) {
		printf("Usage: kasm INFILE [OUTFILE]\n"
			   "Assembles the a3k assembly file into a binary executable.\n"
			   "\nIf no OUTFILE is specified, kasm will create \"kasm.out\".\n"
			   "kasm does NOT check for existing files. It will overwrite\n"
			   "any existing file specified by outfile. Use with caution.\n"
			   "\nFor specification on the instruction set, please see the\n"
			   "README file or go to https://github.com/kueller/a3k.\n\n");
		exit(0);
	}
	
	if (argc > 1)
		filename = argv[1];
	if (argc > 2)
		outfile = argv[2];
	else
		kasm_exit("No parameters specified. Run kasm --help for more info.", 0);

	InstructionList *list = create_instructions_from_file(filename);
	assemble(list, outfile);
	instruction_list_free(list);

	return 0;
}

