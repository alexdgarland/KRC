#include <stdio.h>

#define MAX_WORD_LENGTH 10

main()
{
	int character;
	int currentLength;
	int lengths[MAX_WORD_LENGTH + 1];	//assume no words longer than 50 length;
										//if we were being clever could dynamically resize arrays but this is not super-easy in C
	int lengthCountTracker;
	int currentIndex;
	
	currentLength = 0;
	for (currentIndex=0; currentIndex <= MAX_WORD_LENGTH; currentIndex++)
	{
		lengths[currentIndex] = 0;
	}
	
	while ((character = getchar()) != EOF)
	{
		if (character == ' ' || character == '\t' || character == '\n')
		{
			if (currentLength > 0)
			{
				lengths[currentLength]++;
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
		This could sit in a separate function "Display_Histogram()"
		but there are issues with passing arrays
		[ have to use pointer to first element :-(  ]
	*/
	for (currentIndex = 1; currentIndex <= MAX_WORD_LENGTH; currentIndex++)
	{
		printf("%3d ", currentIndex);
		for (lengthCountTracker = 1; lengthCountTracker <= lengths[currentIndex]; lengthCountTracker++)
		{
			printf("|");
		}
		printf("\n");
	}
}

