#ifndef RunModes_INCLUDED
    
    #define RunModes_INCLUDED

    #define BADARGS_TRIGGER 'Z'
    #define PROCESSLINE_GETOPT_OPTIONS "m:n:"
    #define BADARGS_EXITCODE -1

    /*  Struct declarations */

    typedef struct NumericArgument
    {
        char*   Description;
        int     DefaultValue;
        int     ReferenceCount;
    } NumericArgument;

    #define NO_NUMARG (NumericArgument*)NULL
    
    typedef struct RunMode
    {
        char                TriggerCharacter;
        char*                VerboseAlias;
        void*                RunnerFunction;
        char*                ModeDescription;
        NumericArgument*    NumericArgDetails;
    } RunMode;

    #define NO_RUNMODE (RunMode*)NULL

    typedef struct ListNode
    {
        RunMode* RunMode;
        ListNode* Next;
    } ListNode;

    #define NO_LISTNODE (ListNode*)NULL

    typedef struct RunModeList
    {
        ListNode* First;
        ListNode* Last;
    } RunModeList;

    #define NO_MODELIST (RunModeList*)NULL

    /*  Function signatures     */

    NumericArgument* CreateNumericArg(char* Description, int DefaultValue);
    RunMode* CreateRunMode (char TriggerCharacter, char* VerboseAlias, void* RunnerFunction, char* ModeDescription, NumericArgument* NumericArgDetails);
    
    RunModeList* GetGlobalModeList();

    int MatchMode_Char(RunMode* Mode, char* ModeArgument);
    int MatchMode_Verbose(RunMode* Mode, char* ModeArgument);
    RunMode* GetSelectedRunMode(char* ModeArgument);

    void RunWithNumericArg(RunMode* SelectedRunMode, int NumericCLIArg);
    void RunWithoutNumericArg(RunMode* SelectedRunMode);

    int FreeNumericArg(NumericArgument* Arg);
    int FreeRunMode(RunMode* Mode);
    int FreeListNode(ListNode* Node);
    int FreeModeList(RunModeList* ModeList);
    int FreeGlobalModeList();

    void ListValidArguments();
    void ReportBadArgsAndExit();

#endif