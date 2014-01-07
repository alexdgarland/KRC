#include <stdio.h>

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

int getline(char outputString[], int arrayLimit)
{
	int arrayIndex, character;
	arrayIndex = 0;
	while(arrayIndex < (arrayLimit-1) && (character = getchar()) != EOF && character != '\n')
	{
		outputString[arrayIndex++] = character;
	}
	if (character == '\n')
	{
		outputString[arrayIndex++] = character;
	}
	outputString[arrayIndex] = '\0';
	return arrayIndex;
}