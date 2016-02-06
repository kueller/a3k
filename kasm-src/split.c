#include "split.h"

StrNode *node_create(char *data)
{
	StrNode *new = (StrNode *)malloc(sizeof(StrNode));
	if (!new) kasm_exit("Memory error creating type StrNode.", 0);
	new->prev = NULL;
	new->next = NULL;

	char *dup = strdup(data);
	if (!dup) kasm_exit("Memory error creating type StrNode.", 0);

	new->str = dup;
	return new;
}

StringList *string_list_create()
{
	StringList *new = (StringList *)malloc(sizeof(StringList));
	if (!new) kasm_exit("Memory error creating type StringList.", 0);
	new->head = NULL;
	new->tail = NULL;
	new->size = 0;

	return new;
}

void node_free(StrNode *n)
{
	if (n) {
		free(n->str);
		free(n);
	}
}

void string_list_free(StringList *list)
{
	if (list) {
		if (list->size > 0) {
			StrNode *current = list->head;
			while(current != NULL) {
				StrNode *tmp = current;
				current = current->next;
				node_free(tmp);
			}
		}
		free(list);
	}
}

void node_append(StringList *list, char *data)
{
	if (!list) kasm_exit("Passed null list to node_append.", 0);
	
	StrNode *n = node_create(data);

	if (list->size == 0) {
		list->head = n;
		list->tail = n;
	} else {
		list->tail->next = n;
		n->prev = list->tail;
		list->tail = n;
	}

	list->size++;
}

void remove_first(StringList *list)
{
	if (!list) kasm_exit("Passed null list to remove function.", 0);
	if (list->size == 0) return;

	if (list->size == 1) {
		node_free(list->head);
		list->head = NULL;
		list->tail = NULL;
	} else {
		StrNode *tmp = list->head;
		list->head->next->prev = NULL;
		list->head = list->head->next;
		node_free(tmp);
	}

	list->size--;
}

void remove_last(StringList *list)
{
	if (!list) kasm_exit("Passed null list to remove function.", 0);
	if (list->size == 0) return;

	if (list->size == 1) {
		remove_first(list);
	} else {
		StrNode *tmp = list->tail;
		list->tail->prev->next = NULL;
		list->tail = list->tail->prev;
		node_free(tmp);
		list->size--;
	}
}


void string_list_remove_at(StringList *list, int index)
{
	if (!list) kasm_exit("Passed null list to remove_at.", 0);
	if (index < 0 || index > (list->size - 1))
		kasm_exit("Out of range index for remove_at.", 0);

	if (!list->head) return;

	if (index == 0) {
		remove_first(list);
	} else if (index == (list->size - 1)) {
		remove_last(list);
	} else {
		StrNode *current = list->head;
		int scroll;
		for (scroll = 0; scroll < index; scroll++)
			current = current->next;
		current->prev->next = current->next;
		current->next->prev = current->prev;
		node_free(current);
		list->size--;
	}
}

void replace_specials(char *entry)
{
	if (!entry) return;
	
	int i;
	for (i = 0; i < strlen(entry); i++) {
		if (entry[i] == ',' || entry[i] == ':')
			entry[i] = ' ';
	}
}

StringList *split_string(char *thing)
{
	StringList *list = string_list_create();
	replace_specials(thing);

	char *token = strtok(thing, " \t\n");
	while (token != NULL) {
		node_append(list, token);
		token = strtok(NULL, " \t\n");
	}

	return list;
}
