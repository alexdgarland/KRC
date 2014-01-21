#include <stdio.h>
#include "InputCapture.h"
#include "DrawHistograms.h"

#define MAX_WORD_LENGTH 20

main()
{
	/* Declare and (where required) initialise variables */
	int lengths[MAX_WORD_LENGTH];
	int i;
	for (i=0; i < MAX_WORD_LENGTH; i++) { lengths[i] = 0; }

	/* Perform the actual work of the program */
	CaptureWordLengthFrequency(lengths);
	DrawHistogram_Horizontal(lengths, MAX_WORD_LENGTH);
	DrawHistogram_Vertical(lengths, MAX_WORD_LENGTH);
}