#include <stdio.h>

/* print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300 */

float tocelsius(float fahr)
{
	return (5.0/9.0) * (fahr-32.0);
}

float tofahr(float celsius)
{
	return (celsius * (9.0/5.0)) + 32.0;
}

void print_f_to_c()
{
	float fahr;
	
	int lower = 0;		/* lower limit of temperature table */
	int upper = 300;	/* upper limit */
	int step = 20;		/* step size */
	
	printf("\n%15s\t%15s\n", "Fahrenheit:", "Celsius:");
	printf("-------------------------------\n");
	
	fahr = lower;
	while (fahr <= upper)
	{
		printf("%15.0f\t%15.1f\n", fahr, tocelsius(fahr));
		fahr = fahr + step;
	}
}

void print_c_to_f()
{
	float celsius;
	
	int lower = -20;	/* lower limit of temperature table */
	int upper = 150;	/* upper limit */
	int step = 15;		/* step size */
	
	printf("\n%15s\t%15s\n", "Celsius:", "Fahrenheit:");
	printf("-------------------------------\n");
	
	celsius = lower;
	while (celsius <= upper)
	{
		printf("%15.0f\t%15.1f\n", celsius, tofahr(celsius));
		celsius = celsius + step;
	}
}

main()
{
	print_f_to_c();
	print_c_to_f();
}

