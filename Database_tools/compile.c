#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT_FILE "input.csv"
#define NAME_MAX 15

typedef struct item
{
	char name[25];
	int count;
	char owner[NAME_MAX];
	struct item* next;
} item_t;

char user[NAME_MAX]; // global for direct access in functions

int main()
{
	printf( "Enter your username: " );
}
