#include <stdbool.h>
#include "defs.h"

#define INPUT_FILE	"input.csv"
#define OUTPUT_FILE "master_database.csv"

void alpha( item_t* list );
void nodecpy( item_t* from, item_t* to );

item_t database_list;	// global variable to allow list to be accesed directly everywhere
item_t ingest_list;		// global variable to allow list to be accesed directly everywhere

int main()
{
	item_t *list_start;		// structure pointer
	item_t *data_node;		// structure pointer
	item_t *ingest_node;	// structure pointer
	item_t *prev_node;		// structure pointer
	item_t transfer;
	FILE *output;
	FILE *ingest;
	char line[LINE_MAX];
	bool inlist = false;
	int debug = 0;

	database_list.next = NULL;	// sets first in list pointer to null
	ingest_list.next = NULL;	// sets first in list pointer to null

	ingest = fopen( INPUT_FILE, "r" );
	if ( ingest == NULL )
	{
		fprintf( stderr, "Error opening file: %s\n", INPUT_FILE );
		return 1;
	}

	output = fopen( OUTPUT_FILE, "r" );
	if ( output == NULL )
	{
		fprintf( stderr, "Error opening file: %s\n", OUTPUT_FILE );
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

// function to alphabetize a linked list by the name field
/* DO NOT TOUCH! */
void alpha( item_t* list )
{
	item_t *working = NULL;
	item_t *prev = NULL;
	item_t temp;
	prev = list;
	working = prev->next;
	int compare = 0;
	int sub_compare = 0;

	do
	{
		compare = strcmp( prev->name, working->name );

		/* Compare on name field MUST be split into three conditionals */
		if ( compare < 0 )
		{
			// nodes are in alphabetical order
			// advances node pointers to next node
			prev = prev->next;
			working = working->next;
			continue;
		}
		else if ( compare == 0 )
		{
			// nodes name of item matches
			// sorts by owner name
			sub_compare = strcmp( prev->owner, working->owner );
			if ( sub_compare <= 0 )
			{
				// nodes owner field are in alphabetical order
				// advances node pointers to next node
				prev = prev->next;
				working = working->next;
				continue;
			}
			else if ( sub_compare > 0 )
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
void nodecpy( item_t* from, item_t* to )
{
	strcpy( to->name, from->name );
	to->count = from->count;
	strcpy( to->owner, from->owner );
}
