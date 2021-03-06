#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

pthread_mutex_t mutex;

sem_t oxygen;
sem_t hydrogen;

pthread_barrier_t barrier;

int oxygenCounter;
int hydrogenCounter;
int molecule;

void *oxygen_thread(void *input) {
    int t_id = *(int *)input;

    pthread_mutex_lock(&mutex);
    oxygenCounter++;
    if (hydrogenCounter >= 2) {
       // printf("[Oxygen] Entrou if para liberar threads \n");
        sem_post(&hydrogen);
        sem_post(&hydrogen);
        hydrogenCounter -= 2;
        sem_post(&oxygen);
        oxygenCounter--;
    } else {
        pthread_mutex_unlock(&mutex);
    }

    sem_wait(&oxygen);

    printf("Oxigenio ( %d ) se ligou para formar a molecula \n", t_id);

    pthread_barrier_wait (&barrier);

    printf("Molecula criada \n");

    molecule++;

    pthread_mutex_unlock(&mutex);

    return 0;
}

void *hydrogen_thread(void *input) {
    int t_id = *(int *)input;

    pthread_mutex_lock(&mutex);
    hydrogenCounter++;
    if (hydrogenCounter >= 2 && oxygenCounter >= 1) {
       // printf("[Hydrogen] Entrou if para liberar threads \n");
        sem_post(&hydrogen);
        sem_post(&hydrogen);
        hydrogenCounter -= 2;
        sem_post(&oxygen);
        oxygenCounter--;
    } else {
        pthread_mutex_unlock(&mutex);
    }

    sem_wait(&hydrogen);

    printf("Hidrogenio ( %d ) se ligou para formar a molecula \n", t_id);

    pthread_barrier_wait (&barrier);

    pthread_mutex_unlock(&mutex);

    return 0;
}

int main(int argc, char *argv[]) {
    int molecules;
    molecules = atoi(argv[1]);

    pthread_t t_hydrogen[molecules * 2];
    pthread_t t_oxygen[molecules];
    int ids[molecules * 2];

    int i;
    
    pthread_mutex_init(&mutex, NULL);

    sem_init(&oxygen, 0, 0);
    sem_init(&hydrogen, 0, 0);

    pthread_barrier_init (&barrier, NULL, 3);

    for (i = 0; i < molecules * 2; i++) {
        ids[i] = i;

        if (i < molecules)
            pthread_create(&t_oxygen[i], NULL, oxygen_thread, (void *)&ids[i]);

        pthread_create(&t_hydrogen[i], NULL, hydrogen_thread, (void *)&ids[i]);
    }

    for (i = 0; i < molecules * 2; i++) {
        ids[i] = i;

        if (i < molecules)
            pthread_join(t_oxygen[i], NULL);

        pthread_join(t_hydrogen[i], NULL);
    }

    sem_destroy(&oxygen);
    sem_destroy(&hydrogen);
    pthread_mutex_destroy(&mutex);

    printf("Foram criadas ( %d ) moleculas \n", molecule);

    return 0;
}
