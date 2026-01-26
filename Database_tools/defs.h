#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX 16
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

void buffclear()
{
	while ( getchar() != '\n' );
}

void printNode( item_t node )
{
	// prints the contents of a node to the stdout in final output format
	// it is recomended to redirect stdout to a log file
	fprintf( stdout, "%s,%d,%s\n", node.name, node.count, node.owner );
}
