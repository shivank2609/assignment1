#include <stdlib.h>
#include <string.h>
#include "list.h"

// Creates a linked list and returns it

list_node* list_create(void *data)
{
	list_node *l = malloc(sizeof(list_node));
	if (l != NULL) {
		l->next = NULL;
		l->data = data;
	}

	return l;
}

// Completely destroys a list

void list_destroy(list_node **list)
{
	if (list == NULL) return;
	while (*list != NULL) {
		list_remove(list, *list);
	}
}

// Creates a list node and inserts it after the specified node

list_node* list_insert_after(list_node *node, void *data)
{
	list_node *new_node = list_create(data);
	if (new_node) {
		new_node->next = node->next;
		node->next = new_node;
	}
	return new_node;
}

// Creates a new list node and inserts it in the beginning of the list

list_node* list_insert_beginning(list_node *list, void *data)
{
	list_node *new_node = list_create(data);
	if (new_node != NULL) { new_node->next = list; }
	return new_node;
}

// Creates a new list node and inserts it at the end of the list

list_node* list_insert_end(list_node *list, void *data)
{
	list_node *new_node = list_create(data);
	if (new_node != NULL) {
		for(list_node *it = list; it != NULL; it = it->next) {
			if (it->next == NULL) {
				it->next = new_node;
				break;
			}
		}
	}
	return new_node;
}
// Removes a node from the list

void list_remove(list_node **list, list_node *node)
{
	list_node *tmp = NULL;
	if (list == NULL || *list == NULL || node == NULL) return;

	if (*list == node) {
		*list = (*list)->next;
		free(node);
		node = NULL;
	} else {
		tmp = *list;
		while (tmp->next && tmp->next != node) tmp = tmp->next;
		if (tmp->next) {
			tmp->next = node->next;
			free(node);
			node = NULL;
		}
	}
}

// Removes an element from a list by comparing the data pointers

void list_remove_by_data(list_node **list, void *data)
{
	if (list == NULL || *list == NULL || data == NULL) return;
	list_remove(list, list_find_by_data(*list, data));
}

//Find an element in a list by the pointer to the element

list_node* list_find_node(list_node *list, list_node *node)
{
	while (list) {
		if (list == node) break;
		list = list->next;
	}
	return list;
}

// Finds an elemt in a list by the data pointer

list_node* list_find_by_data(list_node *list, void *data)
{
	while (list) {
		if (list->data == data) break;
		list = list->next;
	}
	return list;
}

// Finds an element in the list by using the comparison function

list_node* list_find(list_node *list, int(*func)(list_node*,void*), void *data)
{
	if (!func) return NULL;
	while(list) {
		if (func(list, data)) break;
		list = list->next;
	}
	return list;
}

