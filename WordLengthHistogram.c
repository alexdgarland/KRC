#include <stdio.h>

#define MAX_WORD_LENGTH 20

#define TRUE 1
#define FALSE 0

main()
{
	/* Declare and (where required) initialise variables */
	int lengths[MAX_WORD_LENGTH];
	int i;
	for (i=0; i < MAX_WORD_LENGTH; i++) { lengths[i] = 0; }

	/* Perform the actual work of the program */
	CaptureInput(lengths);
	DrawHistogram(lengths);
}

int CaptureInput(int lengths[])
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
	return 1;
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

int DrawHistogram(int lengths[])
{
	int i, j;
	
	for (i = 0; i < MAX_WORD_LENGTH; i++)
	{
		printf("%3d ", i + 1);
		for (j = 1; j <= lengths[i]; j++)
		{
			printf("|");
		}
		printf("\n");
	}
	return 1;
}