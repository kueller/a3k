#ifndef __SPLIT_H__
#define __SPLIT_H__

#include <string.h>
#include <stdlib.h>
#include "kasm.h"

/*
 * A simple linked list data structure that contains a list of strings.
 * Created from one string parsed by spaces.
 */

typedef struct _split_node_ {
	struct _split_node_ *prev;
	struct _split_node_ *next;
	char *str;
} StrNode;

typedef struct _split_ {
	StrNode *head;
	StrNode *tail;
	int size;
} StringList;

void string_list_free(StringList*);
void node_append(StringList *, char *);
void remove_first(StringList *);
void remove_last(StringList *);
void string_list_remove_at(StringList *, int);
StringList *split_string(char *);

#endif
