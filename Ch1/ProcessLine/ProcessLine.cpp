#include <stdint.h>
#include <string>

#include "ProcessLine.h"
#include "ArgHandling.h"
#include "RunModes.h"

using std::string;

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
    
    if((selectedRunMode = GetSelectedRunMode(RunModeArgument)) == NO_RUNMODE)
    {
        ReportBadArgsAndExit();
    };

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

}
