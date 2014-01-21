#include <stdio.h>

// Generic line/ string handling functions for use in various programs

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