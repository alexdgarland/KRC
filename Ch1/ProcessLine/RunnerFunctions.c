#include <stdio.h>

#include "RunnerFunctions.h"
#include "ArgHandling.h"
#include "Lines.h"
#include "Tests.h"


void TryRunFlaggedMethod(char FlagArg, int NumericArgument)
{
	switch (FlagArg)
		{
		case 'T':
			// Trim
			RunTrim();
			break;
		case 'R':
			// Reverse
			RunReverse();
			break;
		case 'S':
			// Strip comments
			RunStripComments();
			break;
		case 'W':
			// Wrap text
			RunWrapText(NumericArgument);
			break;
		case 'D':
			// De-tab
			RunDetab(NumericArgument);
			break;
		case 'E':
			// En-tab
			RunEntab(NumericArgument);
			break;
		case 'G':
			// Get lines greater than a certain length
			RunGetLinesOfMinimumLength(NumericArgument);
			break;
		case 'L':
			// Get longest line
			RunGetLongestLine();
			break;
		case 'V':
			// Provide a list of valid command line arguments for this program
			ListValidArguments();
			break;
		case 'X':
			// Run unit tests for internal functions
			RunTests();
			break;
		default:
			ReportBadArguments();
		}
}


void RunReverse()
{
	InputOutputPair pair = GetInputOutPutPair();
	
	while (getline(pair.InLine, MAX_LINE_LENGTH) > 0)
	{
		printf("%s\n", reversestring(pair));
	}

	FreeInputOutputPair(pair);
}


void RunWrapText(int MaxWrapWidth)
{
	InputOutputPair pair = GetInputOutPutPair();

	AssignDefaultIfRequired(&MaxWrapWidth, DEFAULT_MAX_WRAP_WIDTH);

	while(getline(pair.InLine, MAX_LINE_LENGTH) > 0)
	{
		printf(foldline(pair, MAX_LINE_LENGTH, MaxWrapWidth));
	}

	FreeInputOutputPair(pair);
}


void RunEntab(int TabSize)
{
	InputOutputPair pair = GetInputOutPutPair();

	AssignDefaultIfRequired(&TabSize, DEFAULT_TABSIZE);
	
	while(getline(pair.InLine, MAX_LINE_LENGTH) > 0)
	{
		printf(spacestotabs(pair, TabSize));
	}

	FreeInputOutputPair(pair);
}


void RunDetab(int TabSize)
{
	InputOutputPair pair = GetInputOutPutPair();

	AssignDefaultIfRequired(&TabSize, DEFAULT_TABSIZE);

	while(getline(pair.InLine, MAX_LINE_LENGTH) >0)
	{
		printf(tabstospaces(pair, TabSize));
	}

	FreeInputOutputPair(pair);
}


void RunTests()
{
	ResultTracker tracker = {0, 0, 0};

	printf("\nRunning unit tests...\n");
	
	// Add call to each individual test in turn here
	Test_positionoflastspace(&tracker);
	Test_isblank(&tracker);
	Test_trimline(&tracker);
	Test_foldline(&tracker);
	Test_reverse(&tracker);

	// Get summary results
	printf	(
			"\nNumber of tests run: %d, passed: %d, failed: %d\n",
			tracker.TotalTestCount, 
			tracker.PassCount,
			tracker.FailCount
			);

}


void RunTrim()
{
	char* line = getemptystring(MAX_LINE_LENGTH);
	
	while ((getline(line, MAX_LINE_LENGTH)) > 0)
	{
		if (trimline(line) > 0)
		{
			printf("%s\n", line);
		}
	}

}


void RunGetLongestLine()
{
	/* print longest input line */

	int len;						/* current line length */
	int max = 0;					/* maximum length seen so far */
	char line[MAX_LINE_LENGTH];		/* current input line */
	char longest[MAX_LINE_LENGTH];	/* longest line saved here */
	
	while ((len = getline(line, MAX_LINE_LENGTH)) > 0)
	{
		if (len > max)
		{
			max = len;
			Copy(longest, line);
		}
	}
	if (max > 0)
	{
		RemoveNewLine(longest);
		printf("Longest line: \"%s\\n\" (length %d)", longest, max);
	}
}


void RunGetLinesOfMinimumLength(int MinLength)
{
	char* currentLine = getemptystring(MAX_LINE_LENGTH);
	int currentLength;
	
	AssignDefaultIfRequired(&MinLength, DEFAULT_MIN_LENGTH_TO_PRINT);

	while((currentLength = getline(currentLine, MAX_LINE_LENGTH)) > 0)
	{
		if(currentLength >= MinLength)
		{
			printf("%s", currentLine);
		}
	}
}


void RunStripComments()
{
	int length;
	char* currentLine = getemptystring(MAX_LINE_LENGTH);	
	int in_line_comment = FALSE;
	int in_block_comment = FALSE;
	int in_quote = FALSE;
	int i;
	
	while ((length = getline(currentLine, MAX_LINE_LENGTH)) != 0)
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


void AssignDefaultIfRequired(int* ActualArgument, int DefaultValue)
{
	if(*ActualArgument == USE_DEFAULT)
	{
		*ActualArgument = DefaultValue;
	}
}



