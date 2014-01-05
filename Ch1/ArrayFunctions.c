
int GetMaxIntegerArrayValue(int array[], int arraySize)
{
	int i;
	int maxValue = 0;
	
	for(i = 0; i < arraySize; i++)
	{
		if (array[i] > maxValue) { maxValue = array[i]; }
	}
	return maxValue;
}

int GetMaxNonZeroIntegerArrayElement(int array[], int arraySize)
{
	int i;
	
	for (i = arraySize -1; i >= 0; i--)
	{
		if (array[i] > 0)
		{
			return i;
		}
	}
	return -1;
}