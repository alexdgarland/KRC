#include <stdio.h>
#include "Lines.h"

#define MAX_LENGTH 1000

// This program simply reverses all input, one line at a time.

void runreverse()
{
	// Declare and initialise
	char* input = getemptystring(MAX_LENGTH);
	char* reversed = getemptystring(MAX_LENGTH);
	
	printf("\nInput will be reversed...\n");

	// Get and handle input
	while (getline(input, MAX_LENGTH) > 0)
	{
		printf("%s\n", reversestring(reversed, input));
	}
}

