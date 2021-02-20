#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct abc_t
{
	int begin;
	int end;
} abc_t;

int is_prime(int number);

void *t_function(void *input)
{
	abc_t *abc;
	abc = (abc_t *)input;

	for (int i = abc->begin; i < abc->end; i++)
	{
		is_prime(i);
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int MAX_PRIMES;
	int NUM_THREADS;
	int BLOCK_SIZE;

	NUM_THREADS = atoi(argv[1]);
	MAX_PRIMES = atoi(argv[2]);

	BLOCK_SIZE = MAX_PRIMES / NUM_THREADS;

	pthread_t t[NUM_THREADS];
	abc_t *aux[NUM_THREADS];

	int i;

	for (i = 0; i < NUM_THREADS; i++)
	{
		if (i == 0)
		{
			aux[i] = malloc(sizeof(abc_t));
			aux[i]->begin = 0;
			aux[i]->end = BLOCK_SIZE;

			pthread_create(&t[i], NULL, t_function, (void *)aux[i]);
		}
		else
		{
			aux[i] = malloc(sizeof(abc_t));
			aux[i]->begin = BLOCK_SIZE * i;
			aux[i]->end = BLOCK_SIZE * (i + 1);

			pthread_create(&t[i], NULL, t_function, (void *)aux[i]);
		}
	}

	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(t[i], NULL);
	}

	return 1;
}

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
