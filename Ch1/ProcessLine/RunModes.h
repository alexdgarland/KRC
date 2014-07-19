#ifndef RunModes_INCLUDED
    
    #define RunModes_INCLUDED

    #define BADARGS_TRIGGER 'Z'
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

    NumericArgument* CreateNumArg(char* Description, int DefaultValue);
    ListNode* AddRunMode (
        char TriggerCharacter, char* VerboseAlias,
        void* RunnerFunction, char* ModeDescription,
        NumericArgument* NumArgDetails);

    int MatchMode_Char(RunMode* Mode, char* ModeArgument);
    int MatchMode_Verbose(RunMode* Mode, char* ModeArgument);
    RunMode* GetRunMode(char* ModeArgument);

    void RunWithNumericArg(RunMode* SelectedRunMode, int NumericCLIArg);
    void RunWithoutNumericArg(RunMode* SelectedRunMode);

    int FreeNumericArg(NumericArgument* Arg);
    int FreeRunMode(RunMode* Mode);
    int FreeListNode(ListNode* Node);
    int FreeModeList();

    void ListValidArguments();
    void ReportBadArgsAndExit();

#endif