#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArgHandling.h"


short TryParseIntArg(char* InputArg, int* Output)
{
    /*
    This function checks whether the input string is too long to be an integer, or has any non-numeric characters.
    If it does, it sets the numeric output to zero and returns false.
    Otherwise, we've done a partial/ incomplete check that it's parseable to an int
    so performs the conversion, assigns to the output and returns true.
    Almost certainly there are better standard functions in C if we were writing production code...
    this is just for practice/ learning purposes :-)
    */
    int i;
    int in_length = (int)strlen(InputArg);

    if (in_length > 9)
    {
        *Output = '\0';
        return FALSE;
    }

    for(i = 0; i < in_length; i++)
    {
        if (!IsNumericChar(InputArg[i]))
        {
            *Output = '\0';
            return FALSE;
        }
    }

    *Output = atoi(InputArg);
    return TRUE;
}


short IsNumericChar(char input)
{
    if (input >= '0' && input <= '9')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


char GetFlagArg (char* InputArg)
{
    if (strlen(InputArg) == 2 || *InputArg == '-')
    {
        return UpperChar(InputArg[1]);
    }
    else { return '\0'; }
}


char UpperChar(char InChar)
{
    if(InChar >= 'a' && InChar <= 'z')
    {
        return InChar + ('A'-'a');
    }
    else { return InChar; }
}


