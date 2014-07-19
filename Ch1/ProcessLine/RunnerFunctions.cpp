#include <stdio.h>
#include <string.h>

#include "RunnerFunctions.h"
#include "Lines.h"
#include "Tests.h"

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
    printf    (
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

    int len;                            /* current line length          */
    int max = 0;                        /* maximum length seen so far   */
    char line[MAX_LINE_LENGTH];         /* current input line           */
    char longest[MAX_LINE_LENGTH];      /* longest line saved here      */
    
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
        printf("Longest line: \"%s\\n\" (length %d)", RemoveNewLine(longest), max);
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
            
            /* Print to screen if not in comment, otherwise check if we're able to mark an exit */
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
    /* Not sure this function is fully correct &/or serves any real purpose (rather than being inline)! */
    *CurrentValue = (*CurrentValue ^ TRUE);
}
