#ifndef Lines_INCLUDED

	#define Lines_INCLUDED

	#define MAX_LINE_LENGTH 1000

	typedef struct
	{
		char* InLine;
		char* OutLine;
	} InputOutputPair;

	InputOutputPair GetInputOutPutPair();
	void FreeInputOutputPair(InputOutputPair p);

	int getline(char outputString[], int arrayLimit);
	int isblank(char c);
	int trimline(char line[]);
	int columns_to_next_tab(int current_index, int tabsize);
	int add_entab_blanks_to_string(char line[], int idx, int maxlength, int tabsize, int numberofblanks);
	char* tabstospaces(InputOutputPair p, short tabsize);
	char* spacestotabs(InputOutputPair p, short tabsize);
	char* foldline(InputOutputPair p, int maxlength, int maxlinewidth);
	int positionoflastspace(char line[]);
	char* getemptystring(int requiredlength);
	char* reversestring(InputOutputPair p);
	char* getnewstring(char* inputtext);
	void Copy(char to[], char from[]);
	void RemoveNewLine(char* s);

#endif