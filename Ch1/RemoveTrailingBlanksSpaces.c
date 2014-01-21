#include <stdio.h>
#include "Lines.h"

#define MAX_LENGTH 1000

// This program will print any input, excluding trailing blanks or tabs
// and omitting completely-blank lines altogether.

main()
{
	// Declare and initialise
	int i;
	int arrayLength;
	char line[MAX_LENGTH];
	for (i = 0; i < MAX_LENGTH; i++) { line[i] = 0; }
	
	// Get & handle lines
	while ((arrayLength = getline(line, MAX_LENGTH)) > 0)
	{
		arrayLength = trimline(line, arrayLength);
		if (arrayLength > 0)
		{
			printf("%s\n", line);
		}
	}
	
}