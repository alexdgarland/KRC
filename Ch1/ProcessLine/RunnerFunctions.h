#ifndef RunnerFunctions_INCLUDED

    #define RunnerFunctions_INCLUDED

    #define TRUE 1
    #define FALSE 0

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

#endif