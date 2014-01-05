#include <stdio.h>

#define LETTERS_IN_ALPHABET 26

main()
{
	int character;

	int letters[LETTERS_IN_ALPHABET];
	int currentIndex;

	int maxFrequency;
	int currentFrequencyPoint;
	
	/*
	
	*** Initialise/ zero out variables ***
	
	*/
	for (currentIndex=0; currentIndex < LETTERS_IN_ALPHABET; currentIndex++)
	{
		letters[currentIndex] = 0;
	}
	
	/*
	
	*** Process input into an array ***
	
	*/
	
	while ((character = getchar()) != EOF)
	{
		if (character >= 'a' && character <= 'z')
		{
			letters[character - 'a']++;
		}
		else if (character >= 'A' && character <= 'Z')
		{
			letters[character - 'A']++;
		}
	}
		

	/*
	
	*** Draw vertical histogram ***
	
	*/
	
	/* Loop through and find max frequency of any given letter */
	maxFrequency = 0;
	for (currentIndex = 0; currentIndex < LETTERS_IN_ALPHABET; currentIndex++)
	{
		if (letters[currentIndex] > maxFrequency)
		{
			maxFrequency = letters[currentIndex];
		}
	
	}
		
	/* Header */
	printf("\nFrequency of letters (case-insensitive):\n\n");

	/* Loop down through frequencies and draw each horizontal part of vertical histogram */
	for (currentFrequencyPoint = maxFrequency; currentFrequencyPoint >= 1; currentFrequencyPoint--)
	{
		for (currentIndex = 0; currentIndex < LETTERS_IN_ALPHABET; currentIndex++)
		{
			if (letters[currentIndex] >= currentFrequencyPoint)
			{
				printf(" | ");
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n");
	}
	
	/* Write out column names */
	for (currentIndex = 0; currentIndex < LETTERS_IN_ALPHABET; currentIndex++)
	{
		printf(" %c ", 'a' + currentIndex);
	}
	printf("\n");

}