int getline(char outputString[], int arrayLimit);
int init_string(char s[], int arrayLimit);
int trimline(char line[], int arrayLength);
int columns_to_next_tab(int current_index, int tabsize);
int add_entab_blanks_to_string(char line[], int idx, int maxlength, int tabsize, int numberofblanks);
int tabstospaces(char in_line[], int arrayLimit, char out_line[], int maxlength, short tabsize);
int spacestotabs(char in_line[], int arrayLimit, char out_line[], int maxlength, short tabsize);
int foldline(char in_line[], int in_length, char out_line[], int maxlength, int maxlinewidth);