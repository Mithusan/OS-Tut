#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define BUFFER_SIZE 5
#define NUMBERS 10

int buffer[BUFFER_SIZE];
int pro = 0;
int con= 0;
sem_t empty, full, mutex;

void producer(void *arg) {
    int *num = (int*) arg;
    int i, item;
    for (i = 0; i < NUMBERS; i++) {
        item = num[i];
        sleep(rand() % 3);
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[pro] = item;
        printf("Producer Item Number: %d", item);
        pro = (pro + 1) % BUFFER_SIZE;
        sem_post(&mutex); 
        sem_post(&full); 
    }
    pthread_exit(NULL);
}

void consumer(void *arg) {
    int i, item;
    for (i = 0; i < NUMBERS; i++) {
        sleep(rand() % 3S);
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[con];
        buffer[con] = 0;
        printf("\t \t Consumer Item Number: %d\n\n", item);
        con = (con + 1) % BUFFER_SIZE;
        sem_post(&mutex); 
        sem_post(&empty); 
    }
    pthread_exit(NULL);
}
int main() {
    int num[NUMBERS], i;
    pthread_t prod_tid, cons_tid;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = 0;
    }

    printf("Enter %d numbers:\n", NUMBERS);
    for (i = 0; i < NUMBERS; i++) {
        scanf("%d", &num[i]);
    }

    pthread_create(&prod_tid, NULL, producer, num);
    pthread_create(&cons_tid, NULL, consumer, NULL);

    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    printf("\n\n\t\tThe Buffer Array\n\t\t___________\n\n\t\t");
    for (i = 0; i < BUFFER_SIZE; i++) {
        printf(" %d", buffer[i]);
    }
    printf("\n\t\t___________");


    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
