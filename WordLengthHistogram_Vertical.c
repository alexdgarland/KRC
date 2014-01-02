#include <stdio.h>

//25 is highest multiple of 5 that still works as an axis for vertical histogram in CMD window.
//Doesn't seem completely unreasonable as a max word length either.
#define WORD_LENGTH_UPPER_LIMIT 25
//Supply a minimum width so a reasonable graph is drawn even for v. compact data sets 
#define MINIMUM_GRAPH_WIDTH 10

main()
{
	int character;
	int currentLength;
	int maxObservedLength;
	int lengths[WORD_LENGTH_UPPER_LIMIT + 1];
	int currentIndex;
	int maxFrequency;
	int currentFrequencyPoint;
	
	/*
	
	*** Initialise/ zero out variables ***
	
	*/
	currentLength = 0;
	maxObservedLength = 0;
	for (currentIndex=0; currentIndex <= WORD_LENGTH_UPPER_LIMIT; currentIndex++)
	{
		lengths[currentIndex] = 0;
	}
	
	/*
	
	*** Process input into an array ***
	
	*/
	
	while ((character = getchar()) != EOF)
	{
		if (character == ' ' || character == '\t' || character == '\n')
		{
			if (currentLength > 0)
			{
				if (currentLength <= WORD_LENGTH_UPPER_LIMIT)
				{
					lengths[currentLength]++;
				}
				if (currentLength > maxObservedLength)
				{
					maxObservedLength = currentLength;
				}
				currentLength = 0;
			}
		}
		else
		{
			currentLength++;
		}
	}
	
	//Need to close off word if not already terminated by non-EOF character - little bit hacky, can we improve???
	if (currentLength > 0)
	{
		lengths[currentLength]++;
	}
	

	/*
	
	*** Now do the histogram but vertical in this version ***
	
	*/
	
	//Loop through and find max number of words of any single given length
	maxFrequency = 0;
	for (currentIndex = 1; currentIndex <= WORD_LENGTH_UPPER_LIMIT; currentIndex++)
	{
		if (lengths[currentIndex] > maxFrequency)
		{
			maxFrequency = lengths[currentIndex];
		}
	
	}
		
	//Header
	printf("\nFrequency of word lengths:\n\n");

	//Loop down through frequencies and draw each horizontal part of vertical histogram
	for (currentFrequencyPoint = maxFrequency; currentFrequencyPoint >= 1; currentFrequencyPoint--)
	{
		for (currentIndex = 1;
			currentIndex <= WORD_LENGTH_UPPER_LIMIT &&
				(currentIndex <= maxObservedLength
				|| currentIndex <= MINIMUM_GRAPH_WIDTH);
			currentIndex++)
		{
			if (lengths[currentIndex] >= currentFrequencyPoint)
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
	
	//Write out column names
	for (currentIndex = 1;
		currentIndex <= WORD_LENGTH_UPPER_LIMIT &&
			(currentIndex <= maxObservedLength
			|| currentIndex <= MINIMUM_GRAPH_WIDTH);
		currentIndex++)
	{
		printf("%2d ", currentIndex);
	}
	printf("\n");

}