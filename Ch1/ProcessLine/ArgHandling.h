#ifndef ArgHandling_INCLUDED

	#define ArgHandling_INCLUDED

	#define USE_DEFAULT -1
	#define TRUE 1
	#define FALSE 0

	short TryParseIntArg(char* InputArg, int* Output);
	short IsNumericChar(char input);
	char GetFlagArg (char* InputArg);
	char UpperChar(char InChar);
	void ReportBadArguments();
	void ListValidArguments();

#endif