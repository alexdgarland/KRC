#ifndef ArgHandling_INCLUDED

    #ifdef __linux__
        #include <getopt.h>
    #endif
    #ifdef _WIN32
        #include "XGetopt\XGetopt.h"
    #endif

    #define ArgHandling_INCLUDED

    #define USE_DEFAULT -1

    short TryParseIntArg(char* InputArg, int* Output);
    short IsNumericChar(char input);
    char GetFlagArg (char* InputArg);
    char UpperChar(char InChar);

#endif