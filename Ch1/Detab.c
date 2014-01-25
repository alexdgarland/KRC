#include <stdio.h>
#include "Lines.h"

#define MAX_LENGTH 1000
#define DEFAULT_TABSIZE 4

main (int argc, char *argv[])
{
	char currentline[MAX_LENGTH];
	char processedline[MAX_LENGTH];
	int length;
	int tabsize;

	// assign tabsize via argument or use default
	if (argc >= 2) { tabsize = atoi(argv[1]); }
	else { tabsize = DEFAULT_TABSIZE; }
	
	init_string(currentline, MAX_LENGTH);
	init_string(processedline, MAX_LENGTH);
	
	while((length = getline(currentline, MAX_LENGTH)) >0)
	{
		tabstospaces(currentline, length, processedline, MAX_LENGTH, tabsize);
		printf(processedline);
	}
}

