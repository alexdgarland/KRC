#ifndef ArgHandling_INCLUDED

	#ifdef __linux__
		#include <getopt.h>
	#endif
	#ifdef _WIN32
		#include "XGetopt\XGetopt.h"
	#endif

	#define ArgHandling_INCLUDED

	#define USE_DEFAULT -1
	#define TRUE 1
	#define FALSE 0
	#define BADARGS_EXITCODE -1

	short TryParseIntArg(char* InputArg, int* Output);
	short IsNumericChar(char input);
	char GetFlagArg (char* InputArg);
	char UpperChar(char InChar);

#endif