#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//hello world function
void *hello_world(void) {
    // sleep for a random time between 0 and 5
    sleep(rand()%5);
    // print hello world
    printf("Hello world!\n");
    pthread_exit(0);
}

void *goodbye(void) {
    // sleep for a random time between 0 and 5
    sleep(rand()%5);
    // print goodbye
    printf("Goodbye.\n");
    pthread_exit(0);
}

int main(void) {
    //initialize the threads
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, hello_world, NULL);
    pthread_create(&tid2, NULL, goodbye, NULL);
    
    // join the threads
    pthread_join(tid1, 0);
    pthread_join(tid2, 0);
    
    return 0;
}

