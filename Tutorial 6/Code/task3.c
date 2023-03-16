#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define _XOPEN_SOURCE 700 // required for barriers to work
#define NUMBER_COUNT 5
#define THREAD_COUNT 5

int *moving_sum[NUMBER_COUNT] = {0};
sem_t semaphores[NUMBER_COUNT];

typedef struct{
    int number;
    int index;
} FactorialArgs;

void *factorial(void *args) {
    FactorialArgs *fa = (FactorialArgs *) args;
    int number = fa->number;
    int index = fa->index;

    int fact = 1;
    for (int i = 1; i <= number; i++) {
        fact *= i;
    }

    int prev_sum = 0;
    if (index > 0) {
        sem_wait(&semaphores[index-1]);
        prev_sum = moving_sum[index-1];
    }

    int sum = prev_sum + fact;
    moving_sum[index] = sum;

    printf("\nFactorial of %d is %d\nSum at index %d is %d\n", number, fact, index, sum);

    if (index < NUMBER_COUNT-1) {
        sem_post(&semaphores[index+1]);
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t threads[THREAD_COUNT];
    FactorialArgs args[THREAD_COUNT];

    for (int i = 0; i < NUMBER_COUNT; i++) {
        sem_init(&semaphores[i], 0, 0);
    }
    sem_post(&semaphores[0]);

    for (int i = 0; i < THREAD_COUNT; i++) {
    	printf("Enter Number %d: ", i+1);
        scanf("%d", &args[i].number);
        args[i].index = i;
    }
    
    printf("\n**************************\n");

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, factorial, &args[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\n\nMoving Sum: [%d, %d, %d, %d, %d]\n\n", moving_sum[0], moving_sum[1], moving_sum[2], moving_sum[3], moving_sum[4]);

    for (int i = 0; i < NUMBER_COUNT; i++) {
        sem_destroy(&semaphores[i]);
    }
    return 0;
}
