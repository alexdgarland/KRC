#include <stdio.h>
#include <stdlib.h>
#include "Lines.h"

#define DEFAULT_MAX_WIDTH 40
#define MAX_LENGTH 1000

main(int argc, char *argv[])
{

	int maxlinewidth, currentlength;
	char inputline[MAX_LENGTH], outputline[MAX_LENGTH];

	init_string(inputline, MAX_LENGTH);
	init_string(outputline, MAX_LENGTH);

	if(argc > 1) { maxlinewidth = atoi(argv[1]); }
	else { maxlinewidth = DEFAULT_MAX_WIDTH; }

	while((currentlength = getline(inputline, MAX_LENGTH)) > 0)
	{
		foldline(inputline, currentlength, outputline, MAX_LENGTH);
		printf(outputline);
	}

}

int foldline(char in_line[], int in_length, char out_line[], int maxlength)
{
	int current_length = 0;	// length of current line of output string
	int in_idx, out_idx = 0;
	
	for (in_idx = 0; (in_idx < in_length) && (out_idx < (maxlength - 1)); in_idx++)
	{
		// check if at end of possible line
		// IF SO:
		//		track back and find last space/ blank
		//		if there really isn't one, do an in-word break (e.g. "undoubtedly" -> "undoubt-\nedly")
		//		- note that we can set a line width < 40 which makes this more likely
		//		increment length counter for any inserted chars (can just do out_line[out_idx++] = ...)
		//		need to keep checking whether approaching maxlength
		//		reset current_length to 0
		// END IF
		// insert actual next char
		// using out_idx++, maxlength check
		// currentlength++
	}

	out_line[out_idx] = '\0';
	return out_idx;		// return length of output string	
}