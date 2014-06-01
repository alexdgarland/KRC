#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Lines.h"
#include "Tests.h"


void EqualityTest_Int(int ExpectedResult, int ActualResult, ResultTracker* tracker)
{
	(*tracker).TotalTestCount++;
	printf("\tExpected: %d, Actual: %d", ExpectedResult, ActualResult);
	if (ExpectedResult == ActualResult)
	{
		printf(" - passed.\n");
		(*tracker).PassCount++;
	}
	else
	{
		printf(" - FAILED.\n");
		(*tracker).FailCount++;
	}
}


void EqualityTest_String(char* ExpectedResult, char* ActualResult, ResultTracker* tracker)
{
	(*tracker).TotalTestCount++;
	printf("\tExpected: \"%s\", Actual: \"%s\"", ExpectedResult, ActualResult);
	
	if (strcmp(ExpectedResult, ActualResult)==0)
	{
		printf(" - passed.\n");
		(*tracker).PassCount++;
	}
	else
	{
		printf(" - FAILED.\n");
		(*tracker).FailCount++;
	}
}


void Test_positionoflastspace(ResultTracker* tracker)
{
	printf("\nTesting function \"Position of last space\"\n");
	EqualityTest_Int(13, positionoflastspace("Theoretically sound"), tracker);
	EqualityTest_Int(29, positionoflastspace("See you say that, but I'm not sure"), tracker);
	EqualityTest_Int(-1, positionoflastspace("Antidisestablishmentarianism"), tracker);
	EqualityTest_Int(0, positionoflastspace(" Lets_see_if_this_one_tricks_you"), tracker);
}


void Test_isblank(ResultTracker* tracker)
{
	printf("\nTesting function \"Is blank\"\n");
	EqualityTest_Int(0, isblank('H'), tracker);
	EqualityTest_Int(1, isblank(' '), tracker);
	EqualityTest_Int(1, isblank('\t'), tracker);
}


void Test_trimline(ResultTracker* tracker)
{
	// Function under test is an in-place operation
	// so need to create input as mutables, not string literal constants.
	char* testline1 = strncpy(getemptystring(100), "Hello     ", 100);
	char* testline2 = strncpy(getemptystring(100), "Hello world     \n", 100);

	printf("\nTesting function \"Trim line\"\n");

	// Simple test
	trimline(testline1);
	EqualityTest_Int(5, strlen(testline1), tracker);
	EqualityTest_String("Hello", testline1, tracker);

	// Slightly longer test including newline
	trimline(testline2);
	EqualityTest_Int(11, strlen(testline2), tracker);
	EqualityTest_String("Hello world", testline2, tracker);
}


void Test_foldline(ResultTracker* tracker)
{
	InputOutputPair p = { getnewstring("There is an end"), getemptystring(20) };

	printf("\nTesting function \"Fold line\"\n");

	foldline(p, MAX_LINE_LENGTH, 5);
	EqualityTest_String("There\nis an\nend", p.OutLine, tracker);

	FreeInputOutputPair(p);
}


void Test_reverse(ResultTracker* tracker)
{
	InputOutputPair p = { getnewstring("Hello world"), getemptystring(100) };

	printf("\nTesting function \"Reverse string\"\n");

	EqualityTest_String("dlrow olleH", reversestring(p), tracker);

	FreeInputOutputPair(p);
}