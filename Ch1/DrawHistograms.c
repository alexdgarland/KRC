#include <stdio.h>
#include "ArrayFunctions.h"

#define MIN_VERTICAL_HISTOGRAM_WIDTH 10
#define MAX_VERTICAL_HISTOGRAM_WIDTH 25

int DrawHistogram_Horizontal(int lengths[], int arraySize)
{
	int i, j;
	
	PrintHeader();
	
	for (i = 0; i < arraySize; i++)
	{
		printf("%3d ", i + 1);
		for (j = 1; j <= lengths[i]; j++)
		{
			printf("|");
		}
		printf("\n");
	}
	return 0;
}

int DrawHistogram_Vertical(int lengths[], int arraySize)
{

	int i, f;
	
	//int maxActualLength = GetMaxNonZeroIntegerArrayElement(lengths, arraySize) + 1;
	
	PrintHeader();
	
	//Loop down through frequencies and draw each horizontal part of vertical histogram
	for (f = GetMaxIntegerArrayValue(lengths, arraySize); f >= 1; f--)
	{
		for (i = 0; i < arraySize; i++)
		{
			if (lengths[i] >= f)
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
	for (i = 1; i <= arraySize; i++)
	{
		printf("%2d ", i);
	}
	printf("\n");
	
	return 0;
}

int PrintHeader()
{
	printf("\nFrequency of word lengths:\n\n");
	return 0;
}

