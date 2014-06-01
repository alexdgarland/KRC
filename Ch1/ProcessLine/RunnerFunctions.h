#ifndef RunnerFunctions_INCLUDED

	#define RunnerFunctions_INCLUDED

	#define DEFAULT_MAX_WRAP_WIDTH 40
	#define DEFAULT_TABSIZE 4
	#define DEFAULT_MIN_LENGTH_TO_PRINT 80

	void TryRunFlaggedMethod(char FlagArg, int NumericArgument);
	
	void RunReverse();
	void RunWrapText(int MaxWrapWidth);
	void RunEntab(int TabSize);
	void RunDetab(int TabSize);
	void RunTests();
	void RunTrim();
	void RunGetLongestLine();
	void RunGetLinesOfMinimumLength(int MinLength);
	void RunStripComments();

	void FlipTruthValue(int *CurrentValue);

	void AssignDefaultIfRequired(int* ActualArgument, int DefaultValue);

#endif