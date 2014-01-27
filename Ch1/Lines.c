#include <stdio.h>

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

void init_string(char s[], int arrayLimit)
{
	int i;
	for (i = 0; i < arrayLimit; i++)
	{
		s[i] = '\0';
	}
}

int trimline(char line[], int arrayLength)
{
	int arrayPosition;
	for (arrayPosition = arrayLength - 1; line[arrayPosition] == ' ' || line[arrayPosition] == '\t'; arrayPosition--) { }
	line[++arrayPosition] = '\0';
	return arrayPosition;
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
			numberofspaces = tabsize - (in_idx % tabsize);
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

int spacestotabs(char in_line[], int arrayLimit, char out_line[], int maxlength, short tabsize)
{
	char c;
	int in_idx, out_idx = 0, blankstohandle = 0;
	
	for(in_idx = 0; ((in_idx < arrayLimit) && (out_idx < (maxlength - 1))); in_idx++)
	{
		c = in_line[in_idx];

		// If run of blanks or the line as a whole ends, output stored blanks in correct format
		if(blankstohandle > 0 && ((c != '\t' && c != ' ') || (in_idx == (arrayLimit - 1))))
		{
			// Process optimised blanks into line and set index to new length of line (i.e. next write position)
			out_idx = add_entab_blanks_to_string(out_line, out_idx, tabsize, blankstohandle);			
			blankstohandle = 0;		// Reset counter
		}

		// If tab or space, store count of blanks. Otherwise, pass directly to output.
		switch(c)
		{
			case '\t':
				blankstohandle += (tabsize - (in_idx % tabsize));
				break;
			case ' ':
				blankstohandle++;
				break;
			default:
				out_line[out_idx++] = c;
		}

	}

	out_line[out_idx] = '\0';	
	return out_idx;				// return length of output string
}

int add_entab_blanks_to_string(char line[], int idx, int tabsize, int numberofblanks)
{
	int blankstonexttab, i;

	// Handle (possibly) odd number of columns in first tab
	if(numberofblanks >= (blankstonexttab = tabsize - (idx % tabsize)))
	{
		line[idx++] = '\t';
		numberofblanks -= blankstonexttab;
	}
	// Deal with rest of required blanks
	for(i = 0; i < (numberofblanks / tabsize); i++) { line[idx++] = '\t'; }
	for(i = 0; i < (numberofblanks % tabsize); i++) { line[idx++] = ' '; }

	return idx;		// Return new length of string
}