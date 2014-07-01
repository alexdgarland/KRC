#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RunnerFunctions.h"
#include "ArgHandling.h"
#include "Lines.h"
#include "Tests.h"

RunMode** GlobalModeList = (RunMode**)NULL;

NumericArgument* GetNewNumericArgDetails(char* Description, int DefaultValue)
{
	NumericArgument* NumArg = (NumericArgument*)malloc(sizeof(NumericArgument));
	NumArg->Description=GetNewString(Description);
	NumArg->DefaultValue = DefaultValue;
	return NumArg;
}

RunMode* GetNewRunMode
	(
	char				TriggerCharacter,
	char*				VerboseAlias,
	void*				RunnerFunction,
	char*				ModeDescription,
	NumericArgument*	NumericArgDetails,
	int*				CurrentModeCount
	)
{
	RunMode* ModePtr = (RunMode*)malloc(sizeof(RunMode));
	ModePtr->TriggerCharacter = TriggerCharacter;
	ModePtr->VerboseAlias = GetNewString(VerboseAlias);
	ModePtr->RunnerFunction = RunnerFunction;
	ModePtr->ModeDescription = GetNewString(ModeDescription);
	ModePtr->NumericArgDetails = NumericArgDetails;	
	(*CurrentModeCount)++;
	return ModePtr;
}

RunMode** GetGlobalModeList()
{
	/*
	This effectively returns a dispatch table which can be used as a lookup based on the (char or verbose) mode setting passed in via the command line.
	Little bit fiddly to write/read but puts all the logic regarding the different modes in a single place,
	and mode list can be easily extended by adding a new line (using GetNewRunMode and including a function pointer to a new runner funnction) below.
	*/

	if (GlobalModeList == (RunMode**)NULL)
	{

		int CurrentModeCount = 0;

		NumericArgument* NoNumericArg = (NumericArgument*)NULL;

		/*	Could also add numeric default and description of numeric argument usage as additional / separate struct fields	*/
		RunMode* TrimMode =	GetNewRunMode('T', "Trim", &RunTrim, "Remove trailing blanks from each line.", NoNumericArg, &CurrentModeCount);
		RunMode* ReverseMode = GetNewRunMode('R', "Reverse", &RunReverse, "Reverses the order of characters in each line.", NoNumericArg, &CurrentModeCount);
		RunMode* StripCommentMode = GetNewRunMode('S', "Strip", &RunStripComments, "Strips out code comments.", NoNumericArg, &CurrentModeCount);
		RunMode* WrapMode =	GetNewRunMode('W', "Wrap", &RunWrapText, "Wraps text in each line.", GetNewNumericArgDetails("Sets maximum line width.", 40), &CurrentModeCount);
	
		NumericArgument* SpacesPerTabNumArg = GetNewNumericArgDetails("Sets number of spaces per tab.", 4);
		RunMode* DetabMode = GetNewRunMode('D', "Detab", &RunDetab, "Converts tabs to spaces.", SpacesPerTabNumArg, &CurrentModeCount);
		RunMode* EntabMode = GetNewRunMode('E', "Entab", &RunEntab,	"Converts spaces to tabs.",	SpacesPerTabNumArg, &CurrentModeCount);
	
		RunMode* MinLengthMode = GetNewRunMode('M', "Minimum", &RunGetLinesOfMinimumLength,	"Gets lines of a minimum length.", GetNewNumericArgDetails("Sets minimum line length.", 80), &CurrentModeCount);
		RunMode* LongestMode = GetNewRunMode('L', "Longest", &RunGetLongestLine, "Returns longest line from set of lines entered.", NoNumericArg, &CurrentModeCount);
		RunMode* ListValidMode = GetNewRunMode('V', "ValidArgs", &ListValidArguments, "List valid command line arguments for this program.", NoNumericArg, &CurrentModeCount);
		RunMode* UnitTestMode =	GetNewRunMode('U', "UnitTest", &RunTests, "Run unit tests for internal functions", NoNumericArg, &CurrentModeCount);
		RunMode* EndOfList = GetNewRunMode(BADARGS_TRIGGER, "BadArgs", &ReportBadArgsAndExit, "Non-valid arguments passed!", NoNumericArg, &CurrentModeCount);

		int ModeArraySize = CurrentModeCount * sizeof(RunMode*);
		GlobalModeList = (RunMode**)malloc(ModeArraySize);

		int currentPosition = 0;
	
		GlobalModeList[currentPosition++] = TrimMode;
		GlobalModeList[currentPosition++] = ReverseMode;
		GlobalModeList[currentPosition++] = StripCommentMode;
		GlobalModeList[currentPosition++] = WrapMode;
		GlobalModeList[currentPosition++] = DetabMode;
		GlobalModeList[currentPosition++] = EntabMode;
		GlobalModeList[currentPosition++] = MinLengthMode;
		GlobalModeList[currentPosition++] = LongestMode;
		GlobalModeList[currentPosition++] = ListValidMode;
		GlobalModeList[currentPosition++] = UnitTestMode;
		GlobalModeList[currentPosition++] = EndOfList;

	}

	return	GlobalModeList;
};



RunMode* GetSelectedRunMode(char* ModeArgument)
{
	if (ModeArgument == NULL)
	{
		return GetRunModeByTriggerChar(BADARGS_TRIGGER);
	}

	switch(strlen(ModeArgument))
	{
		case 0 :
			return GetRunModeByTriggerChar(BADARGS_TRIGGER);
			break;
		case 1 :
			return GetRunModeByTriggerChar(ModeArgument[0]);
			break;
		default :
			return GetRunModeByVerboseAlias(ModeArgument);
			break;
	}
}


RunMode* GetRunModeByTriggerChar(char TriggerChar)
{
	RunMode** ModeList = GetGlobalModeList();
	int i = 0;
	RunMode* mode;
	while(TRUE)
	{
		mode = ModeList[i++];
		char trigger = mode->TriggerCharacter;
		if((trigger == TriggerChar) || trigger == BADARGS_TRIGGER)
		{
			return mode;
		}
	}
}


RunMode* GetRunModeByVerboseAlias(char* VerboseAlias)
{
	RunMode** ModeList = GetGlobalModeList();
	int i = 0;
	RunMode* mode;
	while(TRUE)
	{
		mode = ModeList[i++];
		if((strcmp(mode->VerboseAlias, VerboseAlias) == 0) || mode->TriggerCharacter == BADARGS_TRIGGER)
		{
			return mode;
		}
	}

}


void RunWithNumericArg(RunMode* SelectedRunMode, int NumericCLIArg)
{
	NumericArgument* numArgDetails = SelectedRunMode->NumericArgDetails;

	if (numArgDetails == (NumericArgument*)NULL)
	{
		// If we're trying to pass numeric args to a function that doesn't take them - BAD !!!!!!
		ReportBadArgsAndExit();		
	}
	else
	{
		// If the function accepts them, great, run it.
		void (*selectedFunction)(int) = (void(*)(int))(SelectedRunMode->RunnerFunction);
		selectedFunction(NumericCLIArg);
	}

}

void RunWithoutNumericArg(RunMode* SelectedRunMode)
{
	NumericArgument* numArgDetails = SelectedRunMode->NumericArgDetails;

	if (numArgDetails == (NumericArgument*)NULL)
	{
		// If we're not expecting any numeric args - simple - go ahead.
		void (*selectedFunction)() = (void(*)())(SelectedRunMode->RunnerFunction);
		selectedFunction();
	}
	else
	{
		// Otherwise, all numeric arguments have defaults, so can still proceed.
		void (*selectedFunction)(int) = (void(*)(int))(SelectedRunMode->RunnerFunction);
		selectedFunction(numArgDetails->DefaultValue);
	}
}



void RunReverse()
{
	InOutLinePair pair = GetInOutLinePair();
	
	while (GetLine(pair.InLine, MAX_LINE_LENGTH) > 0)
	{
		printf("%s\n", reversestring(pair));
	}

	FreeInOutLinePair(pair);
}


void RunWrapText(int MaxWrapWidth)
{
	InOutLinePair pair = GetInOutLinePair();

	while(GetLine(pair.InLine, MAX_LINE_LENGTH) > 0)
	{
		printf(foldline(pair, MAX_LINE_LENGTH, MaxWrapWidth));
	}

	FreeInOutLinePair(pair);
}


void RunEntab(int TabSize)
{
	InOutLinePair pair = GetInOutLinePair();
	
	while(GetLine(pair.InLine, MAX_LINE_LENGTH) > 0)
	{
		printf(spacestotabs(pair, TabSize));
	}

	FreeInOutLinePair(pair);
}


void RunDetab(int TabSize)
{
	InOutLinePair pair = GetInOutLinePair();

	while(GetLine(pair.InLine, MAX_LINE_LENGTH) >0)
	{
		printf(tabstospaces(pair, TabSize));
	}

	FreeInOutLinePair(pair);
}


void RunTests()
{
	ResultTracker tracker = {0, 0, 0};

	printf("\nRunning unit tests...\n");
	
	// Add call to each individual test in turn here
	Test_positionoflastspace(&tracker);
	Test_IsBlank(&tracker);
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
	char* line = GetEmptyString(MAX_LINE_LENGTH);
	
	while ((GetLine(line, MAX_LINE_LENGTH)) > 0)
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
	
	while ((len = GetLine(line, MAX_LINE_LENGTH)) > 0)
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
	char* currentLine = GetEmptyString(MAX_LINE_LENGTH);
	int currentLength;

	while((currentLength = GetLine(currentLine, MAX_LINE_LENGTH)) > 0)
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
	char* currentLine = GetEmptyString(MAX_LINE_LENGTH);	
	int in_line_comment = FALSE;
	int in_block_comment = FALSE;
	int in_quote = FALSE;
	int i;
	
	while ((length = GetLine(currentLine, MAX_LINE_LENGTH)) != 0)
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
	// Not sure this function is fully correct &/or serves any real purpose (rather than being inline)!
	*CurrentValue = (*CurrentValue ^ TRUE);
}


void ReportBadArgsAndExit()
{
	printf("Invalid or missing arguments.\n");
	ListValidArguments();
	exit(BADARGS_EXITCODE);
}


void ListValidArguments()
{
	printf("Valid arguments are as follows:\n");
	
	RunMode** ModeArray = GetGlobalModeList();

	int currentPosition = 0;
	RunMode* currentMode;

	while( (currentMode = ModeArray[currentPosition++])->TriggerCharacter != BADARGS_TRIGGER)	// Iterate until we hit the "Bad Args" / default case at the end of the array
	{
		printf("Mode: %c (%s) - %s\n", currentMode->TriggerCharacter, currentMode->VerboseAlias, currentMode->ModeDescription);
	}
}
