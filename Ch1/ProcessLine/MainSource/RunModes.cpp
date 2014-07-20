#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RunModes.h"
#include "Lines.h"

RunModeList* GlobalModeList = NO_MODELIST;

NumericArgument* CreateNumArg(char* Description, int DefaultValue)
{
    NumericArgument* NumArg = (NumericArgument*)malloc(sizeof(NumericArgument));
    NumArg->Description=GetNewString(Description);
    NumArg->DefaultValue = DefaultValue;
    NumArg->ReferenceCount = 0;
    return NumArg;
}

ListNode* AddRunMode
    (
    char                TriggerCharacter,
    char*               VerboseAlias,
    void*               RunnerFunction,
    char*               ModeDescription,
    NumericArgument*    NumArgDetails
    )
{
    /* Create new run mode */
    RunMode* RunModePtr = (RunMode*)malloc(sizeof(RunMode));
    RunModePtr->TriggerCharacter = TriggerCharacter;
    RunModePtr->VerboseAlias = GetNewString(VerboseAlias);
    RunModePtr->RunnerFunction = RunnerFunction;
    RunModePtr->ModeDescription = GetNewString(ModeDescription);
    RunModePtr->NumericArgDetails = NumArgDetails;
    if (NumArgDetails != NO_NUMARG)
    {
        NumArgDetails->ReferenceCount++;    /* Allowing a crude/ non-generic form of RC memory management */
    }

    /* Wrap in node struct */
    ListNode* NewNodePtr = (ListNode*)malloc(sizeof(ListNode));
    NewNodePtr->RunMode = RunModePtr;
    NewNodePtr->Next = (ListNode*)NULL;

    if (GlobalModeList == NO_MODELIST)
    {
        /* Initialise Global Mode List and set first and last pointers to new node */
        GlobalModeList = (RunModeList*)malloc(sizeof(RunModeList));
        GlobalModeList->First = GlobalModeList->Last = NewNodePtr;
    }
    else
    {
        /*  Insert to end of populated list  */
        GlobalModeList->Last->Next = NewNodePtr;
        GlobalModeList->Last = NewNodePtr;
    }
    return NewNodePtr;
}

int MatchMode_Char(RunMode* Mode, char* ModeArgument)
{
    return (Mode->TriggerCharacter == ModeArgument[0]);
}

int MatchMode_Verbose(RunMode* Mode, char* ModeArgument)
{
    return(strcmp(Mode->VerboseAlias, ModeArgument) == 0);
}

RunMode* GetRunMode(char* ModeArgument)
{
    if (ModeArgument == NULL || strlen(ModeArgument) == 0)
    {
        ReportBadArgsAndExit();
    }
    
    ListNode* CurrentNode = NO_LISTNODE;

    /*  Pick matching function  */
    void* MatchFuncPtr = strlen(ModeArgument) == 1 ? &MatchMode_Char : &MatchMode_Verbose;
    int (*MatchFunction)(RunMode*,char*) = (int(*)(RunMode*,char*))MatchFuncPtr;

    do
    {
        CurrentNode = (CurrentNode == NO_LISTNODE) ? GlobalModeList->First : CurrentNode->Next;
        if(MatchFunction(CurrentNode->RunMode, ModeArgument))
        {
            return CurrentNode->RunMode;
        }
    }
    while(CurrentNode != GlobalModeList->Last);

    return NO_RUNMODE;  /*  Error condition, only if not found and returned a proper mode by this point. */
}

void RunWithNumericArg(RunMode* SelectedRunMode, int NumericCLIArg)
{
    NumericArgument* numArgDetails = SelectedRunMode->NumericArgDetails;

    if (numArgDetails == (NumericArgument*)NULL)
    {
        /* If we're trying to pass numeric args to a function that doesn't take them - BAD !!!!!! */
        ReportBadArgsAndExit();        
    }
    else
    {
        /* If the function accepts them, great, run it. */
        void (*selectedFunction)(int) = (void(*)(int))(SelectedRunMode->RunnerFunction);
        selectedFunction(NumericCLIArg);
    }

}

void RunWithoutNumericArg(RunMode* SelectedRunMode)
{
    NumericArgument* numArgDetails = SelectedRunMode->NumericArgDetails;

    if (numArgDetails == NO_NUMARG)
    {
        /* If we're not expecting any numeric args - simple - go ahead. */
        void (*selectedFunction)() = (void(*)())(SelectedRunMode->RunnerFunction);
        selectedFunction();
    }
    else
    {
        /* Otherwise, all numeric arguments have defaults, so can still proceed. */
        void (*selectedFunction)(int) = (void(*)(int))(SelectedRunMode->RunnerFunction);
        selectedFunction(numArgDetails->DefaultValue);
    }
}

int FreeNumericArg(NumericArgument* Arg)
{
    if (Arg != NO_NUMARG && --(Arg->ReferenceCount) == 0)
    {
        free(Arg->Description);
        free(Arg);
    }
    return 0;
}

int FreeRunMode(RunMode* Mode)
{
    if(Mode != NO_RUNMODE)
    {
        FreeNumericArg(Mode->NumericArgDetails);
        free(Mode->ModeDescription);
        free(Mode);
    }
    return 0;
}

int FreeListNode(ListNode* Node)
{
    if (Node != NO_LISTNODE)
    {
        FreeRunMode(Node->RunMode);
        free(Node);
    }
    return 0;
}

int FreeModeList()
{
    ListNode* CurrentNode = NO_LISTNODE;
    ListNode* NextNode = NO_LISTNODE;

    if(GlobalModeList != NO_MODELIST)
    {
        do
        {
            CurrentNode = (NextNode == NO_LISTNODE) ? GlobalModeList->First : NextNode;
            NextNode = (CurrentNode == GlobalModeList->Last) ? NO_LISTNODE : CurrentNode->Next;
            FreeListNode(CurrentNode);
        }
        while(NextNode != NO_LISTNODE);
        free(GlobalModeList);
    }
    return 0;
}

void ListValidArguments()
{
    ListNode* CurrentNode = NO_LISTNODE;
    RunMode* CurrentRunMode;

    printf("\nValid arguments are:\n\n");
    printf("    -m followed by single char or full word = Run Mode (must be supplied)\n");
    printf("    -n followed by number = Numeric Argument\n");
    printf("       (where appropriate based on mode, defaults as indicated)\n");
    
    if (GlobalModeList == NO_MODELIST)
    {
        printf("\n(Mode list has not been set by application).\n");
    }
    else
    {
        printf("\nModes are as follows:\n\n");
        do
        {
            CurrentNode = (CurrentNode == NO_LISTNODE) ? GlobalModeList->First : CurrentNode->Next;
            CurrentRunMode = CurrentNode->RunMode;
            
            printf("%c (%s) - %s",
                CurrentRunMode->TriggerCharacter,
                CurrentRunMode->VerboseAlias,
                CurrentRunMode->ModeDescription);
            
            if(CurrentRunMode->NumericArgDetails != NO_NUMARG)
            {
                printf(" -n: %s (%d).",
                    CurrentRunMode->NumericArgDetails->Description,
                    CurrentRunMode->NumericArgDetails->DefaultValue);
            }
            printf("\n");
        }
        while(CurrentNode != GlobalModeList->Last);
    }
}

void ReportBadArgsAndExit()
{
    printf("\n**********************   INVALID OR MISSING ARGUMENTS   **********************\n");
    ListValidArguments();
    FreeModeList();
    exit(BADARGS_EXITCODE);
}
