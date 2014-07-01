#ifndef RunnerFunctions_INCLUDED

	#define RunnerFunctions_INCLUDED

	#define BADARGS_TRIGGER 'Z'
	#define PROCESSLINE_GETOPT_OPTIONS "m:n:"

	typedef struct NumericArgument
	{
		char*	Description;
		int		DefaultValue;
	} NumericArgument;

	typedef struct RunMode
	{
		char				TriggerCharacter;
		char*				VerboseAlias;
		void*				RunnerFunction;
		char*				ModeDescription;
		NumericArgument*	NumericArgDetails;
	} RunMode;

	NumericArgument* GetNewNumericArgDetails(char* Description, int DefaultValue);
	RunMode* GetNewRunMode (char TriggerCharacter, char* VerboseAlias, void* RunnerFunction, char* ModeDescription, NumericArgument* NumericArgDetails, int*CurrentModeCount);
	RunMode** GetGlobalModeList();
	RunMode* GetSelectedRunMode(char* ModeArgument);
	RunMode* GetRunModeByTriggerChar(char TriggerChar);
	RunMode* GetRunModeByVerboseAlias(char* VerboseAlias);

	void RunWithNumericArg(RunMode* SelectedRunMode, int NumericCLIArg);
	void RunWithoutNumericArg(RunMode* SelectedRunMode);

	void RunReverse();
	void RunWrapText(int MaxWrapWidth);
	void RunEntab(int TabSize);
	void RunDetab(int TabSize);
	void RunTests();
	void RunTrim();
	void RunGetLongestLine();
	void RunGetLinesOfMinimumLength(int MinLength);
	void RunStripComments();

	void ReportBadArgsAndExit();
	void ListValidArguments();

	void FlipTruthValue(int *CurrentValue);

#endif