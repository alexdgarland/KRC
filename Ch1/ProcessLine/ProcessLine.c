
#include "ProcessLine.h"
#include "ArgHandling.h"
#include "RunnerFunctions.h"


main(int argc, char* argv[])
{
	int NumericArgument;

	if (argc < 2)
	{
		ReportBadArguments();
	}
	else
	{
		if (argc >= 3)
		{
			if(!TryParseIntArg(argv[2], &NumericArgument))
			{
				ReportBadArguments();	
			};
		}
		else
		{
			NumericArgument = USE_DEFAULT;
		}

		TryRunFlaggedMethod(GetFlagArg(argv[1]), NumericArgument);
	}
}
