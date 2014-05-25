#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*		Generic line/ string handling functions for use in various programs		*/

int getline(char outputString[], int arrayLimit)
{
    int c, i;
        
    for (i=0; i < (arrayLimit-1) && (c=getchar()) != EOF && c!='\n'; i++)
    {
        outputString[i] = c;
    }
    if (c == '\n')
    {
		outputString[i++] = c;
    }
    outputString[i] = '\0';
    return i;
}

char* getemptystring(int requiredlength)
{
	char* s = (char*)malloc(requiredlength + 1);
	int i;
	for(i = 0; i<=requiredlength; i++)
	{
		s[i]='\0';
	}
	return s;
}

int isblank(char c)
{
	// Evaluates input against standard definition of "blank" chars
	return ((c == ' ') || (c == '\t'));
}

int trimline(char* line)
{
	// Removes trailing blanks from a string
	// Must sensibly handle cases where:
	//	- There are no trailing blanks (should return the original string unaltered)
	//	- All characters are blanks (should cleanly return a zero-length string)

	int pos;	// Current position in array
	
	// Works backward from the end, leaving NULLs, until it reaches something that's not a blank
	// (or gets all the way to the beginning without finding one)
	for (pos = (strlen(line) - 1); (pos >= 0) && (isblank(line[pos]) || line[pos] == '\n'); line[pos--] = '\0') { }
	
	// ...then returns the length of the trimmed string
	return pos++;
}

int columns_to_next_tab(int current_index, int tabsize)
{
	return (tabsize - (current_index % tabsize));
}

int add_entab_blanks_to_string(char line[], int idx, int maxlength, int tabsize, int numberofblanks)
{
	int blankstonexttab, i;

	if (idx < (maxlength - 1))
	{
		// Handle (possibly) odd number of columns in first tab
		if(numberofblanks >= (blankstonexttab = columns_to_next_tab(idx, tabsize)))
		{
			line[idx++] = '\t';
			numberofblanks -= blankstonexttab;
		}
		// Deal with rest of required blanks
		for(i = 0; i < (numberofblanks / tabsize) && idx < (maxlength - 1); i++)
		{
			line[idx++] = '\t';
		}
		for(i = 0; i < (numberofblanks % tabsize) && idx < (maxlength - 1); i++)
		{
			line[idx++] = ' ';
		}
	}

	line[idx] = '\0';
	return idx;		// Return new length of string
}

int tabstospaces(char in_line[], int arrayLimit, char out_line[], int maxlength, short tabsize)
{

	int in_idx;
	int out_idx = 0;
	int numberofspaces;
	int spaceiterator;
	
	for(in_idx = 0; ((in_idx < arrayLimit) && (out_idx < (maxlength - 1))); in_idx++)
	{
		if (in_line[in_idx] == '\t')
		{		
			numberofspaces = columns_to_next_tab(in_idx, tabsize);
			for(spaceiterator = 0; spaceiterator < numberofspaces; spaceiterator++)
			{
				out_line[out_idx++] = ' ';
			}
		}
		else
		{
			out_line[out_idx++] = in_line[in_idx];
		}
	}
	
	out_line[out_idx] = '\0';
	
	return out_idx;	// return length of output string
	
}

int spacestotabs(char in_line[], char out_line[], int maxlength, short tabsize)
{
	char c;
	int in_idx, out_idx = 0, blankstohandle = 0;
	int in_length = strlen(in_line);
	
	for(in_idx = 0; ((in_idx < in_length) && (out_idx < (maxlength - 1))); in_idx++)
	{
		c = in_line[in_idx];

		// If run of blanks or the line as a whole ends, output stored blanks in correct format
		if(blankstohandle > 0 && (!isblank(c) || (in_idx == (in_length - 1))))
		{
			// Process optimised blanks into line and set index to new length of line (i.e. next write position)
			out_idx = add_entab_blanks_to_string(out_line, out_idx, (maxlength - 1), tabsize, blankstohandle);			
			blankstohandle = 0;		// Reset counter
		}

		// If tab or space, store count of blanks. Otherwise, pass directly to output.
		switch(c)
		{
			case '\t':
				blankstohandle += columns_to_next_tab(in_idx, tabsize);
				break;
			case ' ':
				blankstohandle++;
				break;
			default:
				if (out_idx < (maxlength - 1))
				{
					out_line[out_idx++] = c;
				}
		}
	}

	out_line[out_idx] = '\0';
	return out_idx;				// return length of output string
}

int foldline(char in_line[], char out_line[], int maxlength, int maxlinewidth)
{
	int current_line_start = 0;
	int targetted_line_end = 0;
	int actual_line_end = 0;
	int out_idx = 0;
	int in_idx = 0;
	int in_length = strlen(in_line);

	while (current_line_start < in_length)		// Really not sure about this loop condition... should it actual resolve in relation to [1] below
	{
		// Scroll past any leading blanks
		for ( ; isblank(in_line[current_line_start]); current_line_start++);

		// get current point we think we should break a line at
		targetted_line_end = current_line_start + maxlinewidth;

		// Terminating condition for the loop
		if (targetted_line_end >= in_length)		// [1] as referenced above
		{
			// copy all remaining characters to output string and end
			for(in_idx = current_line_start; in_idx < in_length && (out_idx < (maxlength - 1)); in_idx++)
			{
				if ((in_idx > current_line_start) || (!isblank(in_line[in_idx])))
				{
					out_line[out_idx++] = in_line[in_idx];
				}
			}
			current_line_start = in_length;	// This is a "meaningful" way to break the outer loop
											// but doesn't really serve any other purpose
		}
		else
		{
			actual_line_end = targetted_line_end;
			// Step backwards if we haven't found a space (by at most 25% of the total max width)
			for(actual_line_end = targetted_line_end;
				(actual_line_end >= (targetted_line_end - (maxlinewidth/4)))
					&& (!isblank(in_line[actual_line_end]))
					&& (!isblank(in_line[actual_line_end+1]));
				actual_line_end--) { }

			for (in_idx = current_line_start; in_idx < actual_line_end && (out_idx < (maxlength - 1)); in_idx++)
			{
				if ((in_idx > current_line_start) || (in_line[in_idx] != ' '))
				{
					out_line[out_idx++] = in_line[in_idx];
				}
			}

			if (out_idx < (maxlength - 1) && (in_idx < (in_length - 1)))
			{
				out_line[out_idx++] = '\n';
			}

			current_line_start = actual_line_end;
		}

	}

	out_line[out_idx] = '\0';
	return out_idx;		// return length of output string	
}

int positionoflastspace(char line[])
{
	// Gets the position of the rightermost instance of a space within a given string.
	// If there are no spaces in the string, returns -1.
	int currentpos;
	for(currentpos = strlen(line) -1; currentpos >= 0 && line[currentpos] != ' '; currentpos--);
	return currentpos;
}

char* reversestring(char* output, char* input)
{
	int i;
	int length = strlen(input);
	for (i = length -1; i >= 0; i--)
	{
		output[(length-1) - i] = input[i];
	}
	output[length] = '\0';
	return output;
}
