
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t oxygen;
sem_t hydrogen;

pthread_mutex_t mutex;

int oxygenCounter;
int hydrogenCounter;

void *t_function(void *input)
{
    int t_id = *(int *)input;
    int value;

    return 0;
}

int main(int argc, char *argv[])
{
    int molecules;
    molecules = atoi(argv[1]);

    pthread_t t_hydrogen[molecules * 2];
    pthread_t t_oxygen[molecules];
    int ids[molecules * 2];

    int i;

    sem_init(&oxygen, 0, 0);
    sem_init(&hydrogen, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < molecules * 2; i++)
    {
        ids[i] = i;

        if (i < molecules)
        {
            pthread_create(&t_oxygen[i], NULL, t_function, (void *)&ids[i]);
        }

        pthread_create(&t_hydrogen[i], NULL, t_function, (void *)&ids[i]);
    }

    for (i = 0; i < molecules * 2; i++)
    {
        ids[i] = i;

        if (i < molecules)
        {
            pthread_join(t_oxygen[i], NULL);
        }

        pthread_join(t_hydrogen[i], NULL);
    }

    sem_destroy(&t_hydrogen);
    sem_destroy(&t_oxygen);
    pthread_mutex_destroy(&mutex);

    return 0;
}
