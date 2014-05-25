#include <stdio.h>
#include "Lines.h"

#define TRUE 1
#define FALSE 0
#define MAX_LENGTH 1000

void FlipTruthValue(int *CurrentValue);		// forward declaration

void runstripcomments()
{
	int length;
	char* currentLine = getemptystring(MAX_LENGTH);	
	int in_line_comment = FALSE;
	int in_block_comment = FALSE;
	int in_quote = FALSE;
	int i;
	
	while ((length = getline(currentLine, MAX_LENGTH)) != 0)
	{
		for(i = 0; i < length; i++)
		{
			// Check if already in comment or starting one
			if ((in_line_comment + in_block_comment) == FALSE)
			{
				if(currentLine[i] == '/' && i < (length -1) && (in_quote == FALSE))
				{
					switch (currentLine[i+1])
					{
						case '/':
							in_line_comment = TRUE;
							i++;
							break;
						case '*':
							in_block_comment = TRUE;
							i++;
							break;
						default:
							break;
					}
				}
				else if (currentLine[i] == '"')
				{
					FlipTruthValue(&in_quote);
				}
			}
			
			// Print to screen if not in comment, otherwise check if we're able to mark an exit
			if (((in_line_comment + in_block_comment) == FALSE))
			{
				putchar(currentLine[i]);
			}
			else if ((in_line_comment == TRUE) && (currentLine[i] == '\n'))
			{
				in_line_comment = FALSE;
				putchar('\n');
			}
			else if (i < (length -1) && currentLine[i] == '*' && currentLine[i+1] == '/')
			{
				in_block_comment = FALSE;
				i++;
			}
			
		}
	}
}

void FlipTruthValue(int *CurrentValue)
{
	*CurrentValue = (*CurrentValue ^ TRUE);
}