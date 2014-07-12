#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RunModes.h"
#include "RunnerFunctions.h"
#include "Lines.h"

RunModeList* GlobalModeList = NO_MODELIST;

NumericArgument* CreateNumericArg(char* Description, int DefaultValue)
{
    NumericArgument* NumArg = (NumericArgument*)malloc(sizeof(NumericArgument));
    NumArg->Description=GetNewString(Description);
    NumArg->DefaultValue = DefaultValue;
    NumArg->ReferenceCount = 0;
    return NumArg;
}

RunMode* CreateRunMode
    (
    char                TriggerCharacter,
    char*                VerboseAlias,
    void*                RunnerFunction,
    char*                ModeDescription,
    NumericArgument*    NumericArgDetails
    )
{
    RunMode* ModePtr = (RunMode*)malloc(sizeof(RunMode));
    ModePtr->TriggerCharacter = TriggerCharacter;
    ModePtr->VerboseAlias = GetNewString(VerboseAlias);
    ModePtr->RunnerFunction = RunnerFunction;
    ModePtr->ModeDescription = GetNewString(ModeDescription);
    ModePtr->NumericArgDetails = NumericArgDetails;
    if (NumericArgDetails != NO_NUMARG)
    {
        NumericArgDetails->ReferenceCount++;    /* Allowing a crude/ non-generic form of RC memory management */
    }
    return ModePtr;
}

RunModeList* GetNewModeList()
{
    RunModeList* NewList = (RunModeList*)malloc(sizeof(RunModeList));
    NewList->First = (ListNode*)NULL;
    NewList->Last = (ListNode*)NULL;
    return NewList;
}

RunModeList* AddModeToList(RunModeList* List, RunMode* NewRunMode)
{
    ListNode* NewListNode = (ListNode*)malloc(sizeof(ListNode));
    NewListNode->RunMode = NewRunMode;
    NewListNode->Next = (ListNode*)NULL;

    if (List->First == (ListNode*)NULL)     /*  Working with empty list */
    {
        List->First = List->Last = NewListNode;
    }   
    else
    {
        /*  Inserting to end of populated list  */
        List->Last->Next = NewListNode;
        List->Last = NewListNode;
    }
    return List;
}

RunModeList* GetGlobalModeList()
{
    /*
    This effectively returns a dispatch table in the form of a linked list,
    which can be used as a lookup based on the (char or verbose) mode setting passed in via the command line.
    Mode list can be easily extended by adding a new line (using CreateRunMode and including a function pointer to a new runner function) below.
    */
    if (GlobalModeList == NO_MODELIST)
    {
        GlobalModeList = GetNewModeList();
        AddModeToList(GlobalModeList, CreateRunMode('T', "Trim", &RunTrim, "Remove trailing blanks from each line.", NO_NUMARG));
        AddModeToList(GlobalModeList, CreateRunMode('R', "Reverse", &RunReverse, "Reverses the order of characters in each line.", NO_NUMARG));
        AddModeToList(GlobalModeList, CreateRunMode('S', "Strip", &RunStripComments, "Strips out code comments.", NO_NUMARG));
        NumericArgument* MaxWidthNumArg = CreateNumericArg("Sets maximum line width", 40);
        AddModeToList(GlobalModeList, CreateRunMode('W', "Wrap", &RunWrapText, "Wraps text in each line.", MaxWidthNumArg));
        NumericArgument* SpacesPerTabNumArg = CreateNumericArg("Sets number of spaces per tab", 4);
        AddModeToList(GlobalModeList, CreateRunMode('D', "Detab", &RunDetab, "Converts tabs to spaces.", SpacesPerTabNumArg));
        AddModeToList(GlobalModeList, CreateRunMode('E', "Entab", &RunEntab, "Converts spaces to tabs.",    SpacesPerTabNumArg));
        NumericArgument* MinLengthNumArg = CreateNumericArg("Sets minimum line length", 80);
        AddModeToList(GlobalModeList, CreateRunMode('M', "Minimum", &RunGetLinesOfMinimumLength, "Gets lines of a minimum length.", MinLengthNumArg));
        AddModeToList(GlobalModeList, CreateRunMode('L', "Longest", &RunGetLongestLine, "Returns longest line from set of lines entered.", NO_NUMARG));
        AddModeToList(GlobalModeList, CreateRunMode('V', "ValidArgs", &ListValidArguments, "List valid command line arguments for this program.", NO_NUMARG));
        AddModeToList(GlobalModeList, CreateRunMode('U', "UnitTest", &RunTests, "Run unit tests for internal functions.", NO_NUMARG));
    }
    return    GlobalModeList;
};

int MatchMode_Char(RunMode* Mode, char* ModeArgument)
{
    return (Mode->TriggerCharacter == ModeArgument[0]);
}

int MatchMode_Verbose(RunMode* Mode, char* ModeArgument)
{
    return(strcmp(Mode->VerboseAlias, ModeArgument) == 0);
}

RunMode* GetSelectedRunMode(char* ModeArgument)
{
    if (ModeArgument == NULL || strlen(ModeArgument) == 0)
    {
        ReportBadArgsAndExit();
    }
    
    RunModeList* ModeList = GetGlobalModeList();
    ListNode* CurrentNode = NO_LISTNODE;

    /*  Pick matching function  */
    int (*MatchFunction)(RunMode*,char*) = (int(*)(RunMode*,char*))(strlen(ModeArgument) == 1 ? &MatchMode_Char : &MatchMode_Verbose);

    do
    {
        CurrentNode = (CurrentNode == NO_LISTNODE) ? ModeList->First : CurrentNode->Next;
        if(MatchFunction(CurrentNode->RunMode, ModeArgument))
        {
            return CurrentNode->RunMode;
        }
    }
    while(CurrentNode != ModeList->Last);

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
    if (Arg == NO_NUMARG)
    {
        return -1;
    }
    else
    {
        Arg->ReferenceCount--;
        if(Arg->ReferenceCount == 0)    /* Check for any remaining references */
        {
            free(Arg->Description);
            free(Arg);
        }
        return 0;
    }
}

int FreeRunMode(RunMode* Mode)
{
    if(Mode == NO_RUNMODE)
    {
        return -1;
    }
    else
    {
        FreeNumericArg(Mode->NumericArgDetails);
        free(Mode->ModeDescription);
        free(Mode);
        return 0;
    }
}

int FreeListNode(ListNode* Node)
{
    if (Node == NO_LISTNODE)
    {
        return -1;
    }
    else
    {
        FreeRunMode(Node->RunMode);
        free(Node);
        return 0;
    }
}

int FreeModeList(RunModeList* ModeList)
{
    ListNode* CurrentNode = NO_LISTNODE;
    ListNode* NextNode = NO_LISTNODE;

    if(ModeList == NO_MODELIST)
    {
        return -1;
    }
    else
    {
        do
        {
            CurrentNode = (NextNode == NO_LISTNODE) ? ModeList->First : NextNode;
            NextNode = (CurrentNode == ModeList->Last) ? NO_LISTNODE : CurrentNode->Next;
            FreeListNode(CurrentNode);
        }
        while(NextNode != NO_LISTNODE);
        free(ModeList);
        return 0;
    }
}

int FreeGlobalModeList()
{
    return FreeModeList(GlobalModeList);
}

void ListValidArguments()
{
    RunModeList* ModeList = GetGlobalModeList();
    ListNode* CurrentNode = NO_LISTNODE;
    RunMode* CurrentRunMode;

    printf("Valid arguments are:\n\n");
    printf("    -m followed by single char or full word = Run Mode (must be supplied)\n");
    printf("    -n followed by number = Numeric Argument\n");
    printf("       (where appropriate based on mode, defaults as indicated)\n");
    
    printf("\nModes are as follows:\n\n");

    do
    {
        CurrentNode = (CurrentNode == NO_LISTNODE) ? ModeList->First : CurrentNode->Next;
        CurrentRunMode = CurrentNode->RunMode;
        printf("%c (%s) - %s", CurrentRunMode->TriggerCharacter, CurrentRunMode->VerboseAlias, CurrentRunMode->ModeDescription);
        if(CurrentRunMode->NumericArgDetails != NO_NUMARG)
        {
            printf(" -n: %s (%d)",
                CurrentRunMode->NumericArgDetails->Description,
                CurrentRunMode->NumericArgDetails->DefaultValue);
        }
        printf("\n");
    }
    while(CurrentNode != ModeList->Last);
}

void ReportBadArgsAndExit()
{
    printf("\n**********************   INVALID OR MISSING ARGUMENTS   **********************\n\n");
    ListValidArguments();
    FreeGlobalModeList();
    exit(BADARGS_EXITCODE);
}
