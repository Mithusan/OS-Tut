#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

// global variable to hold the sum of factorials
int total_sum = 0;

// semaphore to protect total_sum
sem_t sem_total_sum;

// function to calculate factorial of a number
void *factorial(void *num_ptr) {
    int num = *((int*)num_ptr);
    int fact = 1;
    
    // calculate factorial
    for (int i = 1; i <= num; i++) {
        factorial *= i;
    }
    
    // increment total_sum in a thread-safe manner
    sem_wait(&sem_total_sum);
    total_sum += factorial;
    sem_post(&sem_total_sum);
    
    // print current factorial value and calculated factorial
    printf("Factorial of %d: %d\n", num, factorial);
    
    return NULL;
}

int main() {
    // prompt user for five numbers
    int numbers[5];
    printf("Enter five numbers: \n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &numbers[i]);
    }

    printf("\n**************************\n");
    
    // write numbers to file
    FILE *fp;
    fp = fopen("numbers.txt", "w");
    for (int i = 0; i < 5; i++) {
        fprintf(fp, "%d\n", numbers[i]);
    }
    fclose(fp);
    
    // fork a child process
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) { // child process
        // read numbers from file
        fp = fopen("numbers.txt", "r");
        int numbers[NUM_THREADS];
        for (int i = 0; i < NUM_THREADS; i++) {
            fscanf(fp, "%d", &numbers[i]);
        }
        fclose(fp);
        
        // initialize semaphore
        sem_init(&sem_total_sum, 0, 1);
        
        // create threads
        pthread_t threads[NUM_THREADS];
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_create(&threads[i], NULL, factorial, &numbers[i]);
        }
        
        // join threads
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }
        
        // write total_sum to file
        fp = fopen("sum.txt", "w");
        fprintf(fp, "%d\n", total_sum);
        fclose(fp);
        
        // exit child process
        exit(EXIT_SUCCESS);
    }
    else { // parent process
        // wait for child process to terminate
        int status;
        wait(&status);
        
        // read total_sum from file
        fp = fopen("sum.txt", "r");
        int sum;
        fscanf(fp, "%d", &sum);
        fclose(fp);
        
        // print total sum
        printf("Total sum: %d\n", sum);
    }
    
    return 0;
}
