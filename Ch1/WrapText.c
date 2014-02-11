#include <stdio.h>
#include <stdlib.h>
#include "Lines.h"

#define DEFAULT_MAX_WIDTH 40
#define MAX_LENGTH 1000

main(int argc, char *argv[])
{

	int maxlinewidth, currentlength;
	char inputline[MAX_LENGTH], outputline[MAX_LENGTH];

	init_string(inputline, MAX_LENGTH);
	init_string(outputline, MAX_LENGTH);

	if(argc > 1) { maxlinewidth = atoi(argv[1]); }
	else { maxlinewidth = DEFAULT_MAX_WIDTH; }

	while((currentlength = getline(inputline, MAX_LENGTH)) > 0)
	{
		foldline(inputline, currentlength, outputline, MAX_LENGTH, maxlinewidth);
		printf(outputline);
	}

}
