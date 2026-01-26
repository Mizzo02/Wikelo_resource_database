#include "defs.h"
#include "readstring.h"

#define OUTPUT_FILE "input.csv"

char user[NAME_MAX]; // global for direct access in functions

int main()
{
	char answer;
	item_t list_head;
	item_t *current;
	FILE *output;

	list_head.next = NULL;
	current = &list_head;
	printf( "Enter your username: " );
	readString( user, NAME_MAX );

	while ( 1 )
	{
		printf( "Item name: " );	// gets item name
		readString( current->name, sizeof( current->name ) / sizeof( char ) );

		printf( "Item count: " );	// gets item count
		scanf( "%d", &current->count );

		strcpy( current->owner, user );	// copies the owner name

		printf( "Add another record? (Y/n): " );
		getchar(); // clears '\n' from the input buffer
		answer = getchar();
		if ( answer == 'y' || answer == 'Y' )
		{
			while ( getchar() != '\n' );	// semicolon is deliberate
			addNode( &current );
			continue;
		}
		else
		{
			// clears the input buffer
			while ( getchar() != '\n' );	// semicolon is deliberate
			break;	// exits the loop
		}
	}

	output = fopen( OUTPUT_FILE, "w" );

	for ( current = &list_head; current != NULL; current = current->next )
	{
		fprintf( output, "%s,%d,%s\n", current->name, current->count, current->owner );
	}
	fclose( output );
}
