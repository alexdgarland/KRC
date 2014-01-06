#include <stdio.h>
#define MAXLINE 1000	/* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);
void RemoveNewLine(char s[], int lim);

/* print longest input line */
main()
{
	int len;				/* current line length */
	int max;				/* maximum length seen so far */
	char line[MAXLINE];		/* current input line */
	char longest[MAXLINE];	/* longest line saved here */
	
	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)
	{
		if (len > max)
		{
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0)
	{
		RemoveNewLine(longest, max);
		printf("Longest line: \"%s\\n\" (length %d)", longest, max);
	}
	return 0;
}

/* getline: read a line into s, return length */
int getline(char outputString[], int arrayLimit)
{
	int character, inputLength, arrayIndex;
	
	for (arrayIndex=inputLength=0; (character=getchar()) != EOF && character!='\n'; inputLength++)
	{
		if (inputLength < (arrayLimit-1))
		{
			outputString[arrayIndex++] = character;
		}
	}
	if (character == '\n')
	{
		outputString[arrayIndex++] = character;
		inputLength++;
	}
	outputString[arrayIndex] = '\0';
	return inputLength;
}

/* copy: copy 'from' into 'to'; assume 'to' is big enough */
void copy (char to[], char from[])
{
	int i;
	
	i = 0;
	while ((to[i] = from[i]) != '\0')
	{
		++i;
	}
}

/* Remove newline from string if present */
void RemoveNewLine(char s[], int lim)
{
	int i;
	for (i = 0; i < lim; i++)
	{
		if (s[i] == '\n')
		{
			s[i] = '\0';
		}
	}
}