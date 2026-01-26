void readString( char *string, int length )
{
	int i = 0;
	char check;
	char trash = 'a'; // initalizing to anything other than '\n' works

	// for loop assigns the next character in the buffer to the array
	for ( i = 0; (check = getchar()) != '\n' && i < length - 1; i++ )
	{
		string[i] = check;
	}

	// adds a null terminator
	string[i] = '\0';

	// clears buffer of any extra characters
	if ( i == length - 1 && check != '\n' )
	{
		while ( (trash = getchar()) != '\n' );
	}
}
