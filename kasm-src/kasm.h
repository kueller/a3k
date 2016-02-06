#ifndef __KASM_H__
#define __KASM_H__

#define MAX_LENGTH 100

/*
 * Prints the error message to stderr and exits the program as failure.
 * If the line number (parameter 2) is non-zero it will print it too.
 */
void kasm_exit(char *, int);

#endif
