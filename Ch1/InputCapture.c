#include <stdio.h>
#define TRUE 1
#define FALSE 0

int CaptureWordLengthFrequency(int lengths[])
{
	int character, currentLength;
	character = currentLength = 0;
	
	while (character != EOF)
	{
		if (isWordMember(character = getchar()) == FALSE)
		{
			if (currentLength > 0)
			{
				lengths[currentLength-1]++;
				currentLength = 0;
			}
		}
		else
		{
			currentLength++;
		}
	}
	return 0;
}
	
int isWordMember(char character)
{
	if	(
		(character >= 'a' && character <= 'z')
		|| (character >= 'A' && character <= 'Z')
		|| (character == '\'')
		)
	{
		return TRUE;
	}
	return FALSE;	
}