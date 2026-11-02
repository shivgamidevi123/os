
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE], count = 0;
pthread_mutex_t mutex;
sem_t full, empty;

void *producer(void *arg)
{
    int item;
    while(1)
    {
        item = rand() % 100;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[count++] = item;
        printf("Producer produced %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
}

void *consumer(void *arg)
{
    int item;
    while(1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[--count];
        printf("Consumer consumed %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    int time, p, c;

    if(argc != 4)
    {
        printf("Usage: ./a.out time producers consumers\n");
        return 1;
    }

    time = atoi(argv[1]);
    p = atoi(argv[2]);
    c = atoi(argv[3]);

    pthread_t pt[p], ct[c];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, SIZE);

    for(int i = 0; i < p; i++)
        pthread_create(&pt[i], NULL, producer, NULL);

    for(int i = 0; i < c; i++)
        pthread_create(&ct[i], NULL, consumer, NULL);

    sleep(time);
    printf("Exit the program\n");

    return 0;
}

//run :- 

//  gcc p3.c -o practical3 -pthread
//  ./p3 5 2 2