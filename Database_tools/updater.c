#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 1024

typedef struct ItemNode
{
	char name[25];
	int count;
	char owner[15];
	struct ItemNode* next;
} ItemNode_t;

ItemNode_t database_list;	// global variable to allow list to be accesed directly everywhere
ItemNode_t ingest_list;		// global variable to allow list to be accesed directly everywhere

int main()
{
	ItemNode_t *list_start;		// structure pointer
	ItemNode_t *data_node;	// structure pointer
	ItemNode_t *input_node;	// structure pointer
	ItemNode_t *prev_node;		// structure pointer
	ItemNode_t transfer;
	FILE *output;
	FILE *ingest;
	char line[LINE_MAX];

	database_list.next = NULL;	// sets first in list pointer to null
	ingest_list.next = NULL;	// sets first in list pointer to null

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

	list_start = &database_list;
	data_node = list_start;

	// for loop allows new nodes to be added easier
	// for loop adds data from current database
	for ( char* token; fgets( line, sizeof(line), output ) != NULL; addNode( *data_node ) )
	{
		// gets item name
		token = strtok( line, "," );
		strncpy( data_node->name, token, sizeof( data_node->name ) - 1 );

		// gets item count
		token = strtok( NULL, "," );
		data_node->count = atoi( token );

		// gets owner of item
		token = strtok( NULL, "\n" );
		strncpy( data_node->owner, token, sizeof( data_node->owner ) - 1 );
	}
	fclose( output );	// closes output file after reading into list

	list_start = &input_list;
	input_node = list_start;
	// for loop adds data from input file
	for ( char* token; fgets( line, sizeof(line), input ) != NULL; addNode( *current_node ) )
	{
		// gets item name
		token = strtok( line, "," );
		strncpy( input_node->name, token, sizeof( input_node->name ) - 1 );

		// gets item count
		token = strtok( NULL, "," );
		input_node->count = atoi( token );

		// gets owner of item
		token = strtok( NULL, "\n" );
		strncpy( input_node->owner, token, sizeof( input_node->owner ) - 1 );
	}
	fclose( input );

	data_node = &database_list;
	list_start = &input_list;
	input_node = list_start;
	do
	{
		transfer.name = input_node->name;
		transfer.count = input_node->count;
		transfer.owner = input_node->owner;

		do
		{
		} while ();
	} while ( input_node->next != NULL );

	output = fopen( "master_database.csv", "w" );
	if ( output == NULL )
	{
		fprintf( stderr, "Error opening file: master_database.csv\n" );
		return 1;
	}
}

// adds new node and advances the current_node pointer
void addNode( ItemNode_t *node )
{
	node->next = ( ItemNode_t* )malloc( sizeof( ItemNode_t ) );
	node = node->next;
	node->next = NULL;
}

// function to alphabetize a linked list by the name field
void alpha( ItemNode_t list )
{
	ItemNode_t *working = NULL;
	ItemNode_t *prev = NULL;
	prev = &list;
	working = prev->next;
	int compare = 0;

	do
	{
		compare = strcmp( prev->name, working->name );

		if ( compare <= 0 )
		{
			// nodes are in alphabetical order
		}	
		else if ( compare > 0 )
		{
			// nodes are not in alphabetical order
		}
	} while ( working->next != NULL );
}
