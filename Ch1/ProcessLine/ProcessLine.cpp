
#include "ProcessLine.h"
#include "ArgHandling.h"
#include "RunnerFunctions.h"
#include <stdint.h>
#include <string>
using std::string;

void main(int argc, char* argv[])
{

	/*
	int c;
	char* RunMode = NULL;
	char* NumericArgument = NULL;

	#ifdef __linux__
		const char* options;
	#endif
	#ifdef _WIN32
		TCHAR* options;
	#endif
	options = PROCESSLINE_GETOPT_OPTIONS;

	while ((c = getopt(argc, argv, options)) != -1)
	{
		switch (c)
			{
			case 'm':
				RunMode = optarg;
				break;
			case 'n':
				NumericArgument = optarg;
				break;
		}
	}

	*/

	char* ModeArgument = "Q";

	/*
	If there is no mode argument passed, run "bad args" method.
	Otherwise try and get a proper run mode based on that arg.
	*/
	RunMode* selectedRunMode = GetSelectedRunMode(ModeArgument);

	/*
	Then:
		- If we've got a numeric argument from the command line:
			- If the selected mode accepts a numeric arg - run it with the arg passed.
			- If not, run bad args method.
		- Else:
			- If the selected mode accepts a numeric arg - run it using the default.
			- If not, just run it without numeric arg.
	*/

}
