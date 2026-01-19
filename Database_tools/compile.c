#include <string.h>
#include "defs.h"

#define OUTPUT_FILE "input.csv"

char user[NAME_MAX]; // global for direct access in functions

int main()
{
	int i;
	char check;
	char trash = 'a'; // initalizing to anything other than '\n' works

	item_t list_head;

	printf( "Enter your username: " );

	// for loop assigns the next character in the buffer to the array
    for ( i = 0; (check = getchar()) != '\n' && i < NAME_MAX; i++ )
    {
        user[i] = check;
    }

    // adds a null terminator
    user[i] = '\0';

    // clears buffer of any extra characters
    if ( i == NAME_MAX && check != '\n' )
    {
        while ( (trash = getchar()) != '\n' );
    }
}
