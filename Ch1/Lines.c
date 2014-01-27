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
	int in_idx, out_idx = 0, i, blankstohandle = 0, spacestoadd, tabstoadd, blankstonexttab, idx_lastnonblank = 0;
	
	for(in_idx = 0; ((in_idx < arrayLimit) && (out_idx < (maxlength - 1))); in_idx++)
	{
		c = in_line[in_idx];

		// If run of blanks or the line as a whole ends, output stored blanks in correct format
		if(blankstohandle > 0 && ((c != '\t' && c != ' ') || (in_idx == (arrayLimit - 1))))
		{			
			// Handle (possibly) odd number of columns in first tab
			blankstonexttab = tabsize - ((idx_lastnonblank + 1) % tabsize);
			if(blankstohandle >= blankstonexttab)
			{
				out_line[out_idx++] = '\t';
				blankstohandle -= blankstonexttab;
			}
		
			// Deal with rest of required blanks
			spacestoadd = blankstohandle % tabsize;
			tabstoadd = blankstohandle / tabsize;
			for(i = 0; i < tabstoadd; i++) { out_line[out_idx++] = '\t'; }
			for(i = 0; i < spacestoadd; i++) { out_line[out_idx++] = ' '; }
			
			// Reset counter
			blankstohandle = 0;
		}

		// If tab or space, store count of blanks. Otherwise, pass directly to output.
		if (c == '\t')
		{
			blankstohandle += (tabsize - (in_idx % tabsize));
		}
		else if (c == ' ')
		{		
			blankstohandle++;
		}
		else
		{
			idx_lastnonblank = out_idx;
			out_line[out_idx++] = c;
		}
	
	}

	out_line[out_idx] = '\0';
	
	return out_idx;	// return length of output string

}
