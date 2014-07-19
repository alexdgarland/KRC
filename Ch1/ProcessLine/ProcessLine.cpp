#include <stdint.h>
#include <string>

#include "ProcessLine.h"
#include "ArgHandling.h"
#include "RunModes.h"
#include "RunnerFunctions.h"

#ifdef _WIN32
    using std::string;
#endif

void main(int argc, char* argv[])
{

    #ifdef __linux__
        const char* options;
    #endif
    #ifdef _WIN32
        TCHAR* options;
    #endif
    options = PROCESSLINE_GETOPT_OPTIONS;

    int ArgumentIdentifier;
    char* RunModeArgument = NULL;
    char* NumericArgument = NULL;
    int ParsedNumericArgument;
    RunMode* selectedRunMode;

    while ((ArgumentIdentifier = getopt(argc, argv, options)) != -1)
    {
        switch (ArgumentIdentifier)
            {
            case 'm':
                RunModeArgument = optarg;
                break;
            case 'n':
                NumericArgument = optarg;
                break;
        }
    }

    PopulateModeList();

    if((selectedRunMode = GetRunMode(RunModeArgument)) == NO_RUNMODE)
    {
        ReportBadArgsAndExit();
    }

    if (NumericArgument == NULL)
    {
        RunWithoutNumericArg(selectedRunMode);
    }
    else if (TryParseIntArg(NumericArgument, &ParsedNumericArgument))
    {
        RunWithNumericArg(selectedRunMode, ParsedNumericArgument);
    }
    else
    {
        ReportBadArgsAndExit();
    }

    FreeModeList();
    exit(0);
}


int PopulateModeList()
{
    AddRunMode('T', "Trim", &RunTrim, "Remove trailing blanks from each line.", NO_NUMARG);
    AddRunMode('R', "Reverse", &RunReverse, "Reverses the order of characters in each line.", NO_NUMARG);
    AddRunMode('S', "Strip", &RunStripComments, "Strips out code comments.", NO_NUMARG);
    NumericArgument* MaxWidthNumArg = CreateNumArg("Sets maximum line width", 40);
    AddRunMode('W', "Wrap", &RunWrapText, "Wraps text in each line.", MaxWidthNumArg);
    NumericArgument* SpacesPerTabNumArg = CreateNumArg("Sets number of spaces per tab", 4);
    AddRunMode('D', "Detab", &RunDetab, "Converts tabs to spaces.", SpacesPerTabNumArg);
    AddRunMode('E', "Entab", &RunEntab, "Converts spaces to tabs.",    SpacesPerTabNumArg);
    NumericArgument* MinLengthNumArg = CreateNumArg("Sets minimum line length", 80);
    AddRunMode('M', "Minimum", &RunGetLinesOfMinimumLength, "Gets lines of a minimum length.", MinLengthNumArg);
    AddRunMode('L', "Longest", &RunGetLongestLine, "Returns longest line from set of lines entered.", NO_NUMARG);
    AddRunMode('V', "ValidArgs", &ListValidArguments, "List valid command line arguments for this program.", NO_NUMARG);
    AddRunMode('U', "UnitTest", &RunTests, "Run unit tests for internal functions.", NO_NUMARG);
    return 0;
}