#ifndef Lines_INCLUDED

    #define Lines_INCLUDED

    #define MAX_LINE_LENGTH 1000

    typedef struct
    {
        char* InLine;
        char* OutLine;
    } InOutLinePair;

    InOutLinePair GetInOutLinePair();
    void FreeInOutLinePair(InOutLinePair p);

    int GetLine(char outputString[], int arrayLimit);
    int IsBlank(char c);
    int trimline(char line[]);
    int columns_to_next_tab(int current_index, int tabsize);
    int add_entab_blanks_to_string(char line[], int idx, int maxlength, int tabsize, int numberofblanks);
    char* tabstospaces(InOutLinePair p, short tabsize);
    char* spacestotabs(InOutLinePair p, short tabsize);
    char* foldline(InOutLinePair p, int maxlength, int maxlinewidth);
    int positionoflastspace(char line[]);
    char* GetEmptyString(int requiredlength);
    char* reversestring(InOutLinePair p);
    char* GetNewString(char* inputtext);
    void Copy(char to[], char from[]);
    char* RemoveNewLine(char* s);

#endif