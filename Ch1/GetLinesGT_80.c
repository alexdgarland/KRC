#include <stdio.h>
#include "Lines.h"

#define CHAR_ARRAY_LENGTH 1000
#define MIN_LINE_LENGTH_TO_PRINT 81

int getline(char outputString[], int arrayLimit);

main()
{
	char currentLine[CHAR_ARRAY_LENGTH];
	int currentLength;
	
	while((currentLength = getline(currentLine, CHAR_ARRAY_LENGTH)) > 0)
	{
		if(currentLength >= MIN_LINE_LENGTH_TO_PRINT)
		{
			printf("%s", currentLine);
		}
	}
}
