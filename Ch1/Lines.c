#include <stdio.h>

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