#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_MAX	1024
#define INPUT_FILE	"input.csv"

typedef struct ItemNode
{
	char name[25];
	int count;
	char owner[15];
	struct ItemNode* next;
} ItemNode_t;

void addNode( ItemNode_t **node );
void alpha( ItemNode_t* list );
void nodecpy( ItemNode_t* from, ItemNode_t* to );

ItemNode_t database_list;	// global variable to allow list to be accesed directly everywhere
ItemNode_t ingest_list;		// global variable to allow list to be accesed directly everywhere

int main()
{
	ItemNode_t *list_start;		// structure pointer
	ItemNode_t *data_node;	// structure pointer
	ItemNode_t *ingest_node;	// structure pointer
	ItemNode_t *prev_node;		// structure pointer
	ItemNode_t transfer;
	FILE *output;
	FILE *ingest;
	char line[LINE_MAX];
	bool inlist = false;

	database_list.next = NULL;	// sets first in list pointer to null
	ingest_list.next = NULL;	// sets first in list pointer to null

	ingest = fopen( INPUT_FILE, "r" );
	if ( ingest == NULL )
	{
		fprintf( stderr, "Error opening file: %s\n", INPUT_FILE );
		return 1;
	}
	else
	{
		printf( "Opened file: INPUT\n" );
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
	for ( char* token; fgets( line, sizeof(line), output ) != NULL; addNode( &data_node ) )
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

		// sets a pointer to the current node
		prev_node = data_node;
	}
	// removes extra trailing node
	free( prev_node->next );
	// sets the pointer of last node in list to NULL
	prev_node->next = NULL;
	fclose( output );	// closes output file after reading into list

	list_start = &ingest_list;
	ingest_node = list_start;
	// for loop adds data from input file
	for ( char* token; fgets( line, sizeof(line), ingest ) != NULL; addNode( &ingest_node ) )
	{
		// gets item name
		token = strtok( line, "," );
		strncpy( ingest_node->name, token, sizeof( ingest_node->name ) - 1 );

		// gets item count
		token = strtok( NULL, "," );
		ingest_node->count = atoi( token );

		// gets owner of item
		token = strtok( NULL, "\n" );
		strncpy( ingest_node->owner, token, sizeof( ingest_node->owner ) - 1 );

		// sets a pointer to the current node
		prev_node = ingest_node;
	}
	// removes extra trailing node
	free( prev_node->next );
	// sets the pointer of last node in list to NULL
	prev_node->next = NULL;
	fclose( ingest );

	ingest_node = &ingest_list;
	prev_node = NULL;

	do
	{
		data_node = &database_list;
		inlist = false;
		do
		{
			// compares the item name and owner
			if ( strcmp( ingest_node->name, data_node->name ) == 0 && strcmp( ingest_node->owner, data_node->owner ) == 0 )
			{
				data_node->count += ingest_node->count;
				ingest_node = ingest_node->next;
				inlist = true;
				break;
			}
			else
			{
				prev_node = data_node;
				data_node = data_node->next;
			}
		} while ( data_node != NULL );

		if ( inlist == false )
		{
			// data node is reassigned make the following function calls more clear
			data_node = prev_node;
			addNode( &data_node );
			nodecpy( ingest_node, data_node );

			ingest_node = ingest_node->next;
		}
	} while ( ingest_node != NULL );

	output = fopen( "master_database.csv", "w" );
	if ( output == NULL )
	{
		fprintf( stderr, "Error opening file: master_database.csv\n" );
		return 1;
	}

	// alphabetize the database list
	alpha( &database_list );

	for ( data_node = &database_list; data_node != NULL; data_node = data_node->next )
	{
		fprintf( output, "%s,%d,%s\n", data_node->name, data_node->count, data_node->owner );
	}
	fclose( output );
}

// adds new node and advances the current_node pointer
void addNode( ItemNode_t **node )
{
	(*node)->next = ( ItemNode_t* )malloc( sizeof( ItemNode_t ) );
	*node = (*node)->next;
	// defaults the pointer to next node to NULL for last node in list
	(*node)->next = NULL;
}

// function to alphabetize a linked list by the name field
void alpha( ItemNode_t* list )
{
	ItemNode_t *working = NULL;
	ItemNode_t *prev = NULL;
	ItemNode_t temp;
	prev = list;
	working = prev->next;
	int compare = 0;
	int sub_compare = 0;

	do
	{
		compare = strcmp( prev->name, working->name );

		if ( compare <= 0 )
		{
			// nodes name field are in alphabetical order
			sub_compare = strcmp( prev->owner, working->owner );
			if ( sub_compare <= 0 )
			{
				// nodes owner field are in alphabetical order
				// advances node pointers to next node
				prev = prev->next;
				working = working->next;
				continue;
			}
			else if ( sub_compare > 0 && compare == 0 )
			{
				// nodes owner field are not in alphabetical order
				nodecpy( prev, &temp );
				nodecpy( working, prev );
				nodecpy( &temp, working );

				// sets node pointers back to start of list
				// setting the pointers back lets the entire list get sorted completely in one function call
				prev = list;
				working = prev->next;
				continue;
			}
		}	
		else if ( compare > 0 )
		{
			// nodes are not in alphabetical order
			nodecpy( prev, &temp );
			nodecpy( working, prev );
			nodecpy( &temp, working );

			// sets node pointers back to start of list
			// setting the pointers back lets the entire list get sorted completely in one function call
			prev = list;
			working = prev->next;
			continue;
		}
	} while ( working != NULL );
}

// copies the contents of one structure to another
void nodecpy( ItemNode_t* from, ItemNode_t* to )
{
	strcpy( to->name, from->name );
	to->count = from->count;
	strcpy( to->owner, from->owner );
}
