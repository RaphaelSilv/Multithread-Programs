#include <stdio.h>
#include <stdlib.h>

#define MAX_PRIMES 10000

int is_prime(int input)
{
	if (input == 2)
	{
		return 1;
	}
	else if (input % 2 == 0 || input <= 1)
	{
		return 1;
	}
	else
	{
		for (int i = 2; i < input / 2; i++)
		{
			if (input % i == 0)
			{
				return 0;
			}
		}
	}

	return 1;
}

int main(int argc, char *argv[])
{

	for (int i = 0; i < MAX_PRIMES; i++)
	{
		is_prime(i);
	}
	
	return 1;
}