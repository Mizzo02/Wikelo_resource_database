#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 1024

typedef struct ItemNode
{
	char name[25];
	int count;
	char owner[15];
	char location[8];
	struct ItemNode* next;
} ItemNode_t;

ItemNode_t database_head; // global variable to allow list to be accesed directly everywhere
ItemNode_t ingest_head; // global variable to allow list to be accesed directly everywhere

int main()
{
	ItemNode_t *list_start;
	ItemNode_t *current_node;
	ItemNode_t *prev_node;
	FILE *output;
	FILE *ingest;
	char line[LINE_MAX];

	ingest = fopen( "input.csv", "r" );
	if ( ingest == NULL )
	{
		fprintf( stderr, "Error opening file: input.csv\n" );
		return 1;
	}

	output = fopen( "master_database.csv", "r" );
	if ( output == NULL )
	{
		fprintf( stderr, "Error opening file: master_database.csv\n" );
		return 1;
	}

	list_start = &database_head;
	current_node = list_start;

	// for loop allows new nodes to be added easier
	for ( ; fgets( line, sizeof(line), output ) != NULL; addNode( current_node->next, *current_node ) )
	{
		char* token;

		// gets item name
		token = strtok( line, "," );
		strncpy( current_node->name, token, sizeof( current_node->name ) - 1 );

		// gets item count
		token = strtok( NULL, "," );
		current_node->count = atoi( token );

		// gets owner of item
		token = strtok( NULL, "," );
		strncpy( current_node->owner, token, sizeof( current_node->owner ) - 1 );

		// gets location of item
		token = strtok( NULL, "\n" );
		strncpy( current_node->location, token, sizeof( current_node->location ) - 1 );
	}
}

void addNode( ItemNode_t *new, ItemNode_t *old )
{
	new = ( ItemNode_t* )malloc( sizeof( ItemNode_t ) );
	old = new;
}
