#include <stdio.h>
#include <stdlib.h>

#define NAME_MAX 15
#define LINE_MAX 1024

typedef struct item
{
	char name[25];
	int count;
	char owner[NAME_MAX];
	struct item* next;
} item_t;

// adds new node and advances the current_node pointer
void addNode( item_t **node )
{
	(*node)->next = ( item_t* )malloc( sizeof( item_t ) );
	*node = (*node)->next;
	// defaults the pointer to next node to NULL for last node in list
	(*node)->next = NULL;
}
