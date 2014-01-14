#include <stdio.h>

#define MAX_LENGTH 1000

// This program simply reverses all input, one line at a time.

int InitialiseString(char string[], int length);
int ReverseString(char input[], int length, char output[]);
int GetLine(char line[], int maxLength);

void main()
{
	// Declare and initialise
	char input[MAX_LENGTH];
	char reversed[MAX_LENGTH];
	int length;
	
	InitialiseString(input, MAX_LENGTH);
	InitialiseString(reversed, MAX_LENGTH);
	
	// Get and handle input
	while ((length = GetLine(input, MAX_LENGTH)) > 0)
	{
		ReverseString(input, length, reversed);
		printf("%s\n", reversed);
	}
}

int InitialiseString(char string[], int length)
{
	int arrayIndex;
	for (arrayIndex = 0; arrayIndex < length; arrayIndex++)
	{
		string[arrayIndex] = 0;
	}
	return 0;
}

int ReverseString(char input[], int length, char output[])
{
	int inputArrayIndex;
	for (inputArrayIndex = length -1; inputArrayIndex >= 0; inputArrayIndex--)
	{
		output[(length - 1) - inputArrayIndex] = input[inputArrayIndex];
	}
	output[length] = '\0';
	return length;
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