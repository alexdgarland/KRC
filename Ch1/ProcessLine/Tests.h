#ifndef Tests_INCLUDED

	#define Tests_INCLUDED

	typedef struct
	{
		int TotalTestCount;
		int PassCount;
		int FailCount;
	} ResultTracker;

	void EqualityTest_Int(int ExpectedResult, int ActualResult, ResultTracker* tracker);
	void EqualityTest_String(char ExpectedResult[], char ActualResult[], ResultTracker* tracker);

	void Test_positionoflastspace(ResultTracker* tracker);
	void Test_isblank(ResultTracker* tracker);
	void Test_trimline(ResultTracker* tracker);
	void Test_foldline(ResultTracker* tracker);
	void Test_reverse(ResultTracker* tracker);

#endif