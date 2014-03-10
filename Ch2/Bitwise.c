
/*
	setbits:
	Returns x with the n bits that begin at position p
	set to the rightmost n bits of y, leaving the other bits unchanged.
	Broken down into smaller functions and including "unit test" style methods.
*/

/*		Functions		*/

int setbits(int x, int p, int n, int y)
{
	return -1;	/* Not implemented yet	*/
}

int getrightbits(int y, int n)
{
	return (y & ~(~0 << n));
}

int negativemask(int p, int n)
{
	return ((~0 << (p + n)) | (~(~0 << p)));
}

/*		Unit Tests		*/

void test_getrightbits()
{
	int expected = 10, result;
	printf("Testing getrightbits() function\n");
	result = getrightbits(58, 4);
	printf("Expected result %d, actual result %d, test %s",
			expected,
			result,
			(result == expected) ? "passed" : "failed"); 
}

void test_negativemask()
{
	int expected = -29, result;
	printf("Testing negativemask() function\n");
	result = negativemask(2, 3);
	printf("Expected result %d, actual result %d, test %s",
			expected,
			result,
			(result == expected) ? "passed" : "failed"); 
}