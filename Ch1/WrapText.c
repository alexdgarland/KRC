#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lines.h"
#include "Lines_TESTS.h"

#define DEFAULT_MAX_WIDTH 40
#define MAX_LENGTH 1000

void runwraptext()
{
	//int maxlinewidth;
	//char* inputline = getemptystring(MAX_LENGTH);
	//char* outputline = getemptystring(MAX_LENGTH);

	//printf("%d \"%s\"\n", argc, argv[1]);

	//// Test mode
	//if((argc > 1) && (strcmp(argv[1],"TEST")==0))
	//{
	//	RunTests();
	//}
	//// Normal mode
	//else
	//{
	//	if(argc > 1) { maxlinewidth = atoi(argv[1]); }
	//	else { maxlinewidth = DEFAULT_MAX_WIDTH; }

	//	printf("INFORMATION: Max line width will be %d.\n", maxlinewidth);

	//	while(getline(inputline, MAX_LENGTH) > 0)
	//	{
	//		foldline(inputline, outputline, MAX_LENGTH, maxlinewidth);
	//		printf(outputline);
	//	}
	//}

}
