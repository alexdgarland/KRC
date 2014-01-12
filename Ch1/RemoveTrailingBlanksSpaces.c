#include <stdio.h>
#define MAX_LENGTH 1000

int TrimLine(char line[], int arrayLength);
int GetLine(char line[], int maxLength);

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
	while ((arrayLength = GetLine(line, MAX_LENGTH)) > 0)
	{
		arrayLength = TrimLine(line, arrayLength);
		if (arrayLength > 0)
		{
			printf("%s\n", line);
		}
	}
	
}

int TrimLine(char line[], int arrayLength)
{
	int arrayPosition;
	for (arrayPosition = arrayLength - 1; line[arrayPosition] == ' ' || line[arrayPosition] == '\t'; arrayPosition--) { }
	line[++arrayPosition] = '\0';
	return arrayPosition;
}

int GetLine(char line[], int maxLength)
{
	// Gathers character input into char array until line break or EOF encountered.
	// Returns length of array used, array itself is assigned to by reference.
	
	int character;
	int arrayPosition;
	arrayPosition = 0;
	
	// Loop through and capture input to array
	while (arrayPosition < (maxLength -1) && (character = getchar()) != '\n' && character != EOF)
	{
		line[arrayPosition++] = character;
	}
	
	if (character = '\n')
	{
		line[arrayPosition] = '\n';
	}
	
	line[arrayPosition] = '\0';
	
	return arrayPosition;
}