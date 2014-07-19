#ifndef ProcessLine_INCLUDED

    #define ProcessLine_INCLUDED

    #ifdef __linux__
        #include <getopt.h>
    #endif
    #ifdef _WIN32
        #include "..\WindowsBuild\XGetopt\XGetopt.h"
        #include <string>
    #endif
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdint.h>
    #include "RunModes.h"
    #include "RunnerFunctions.h"

    #define PROCESSLINE_GETOPT_OPTIONS "m:n:"

    int PopulateModeList();
    short TryParseIntArg(char* InputArg, int* Output);
    short IsNumericChar(char input);

#endif