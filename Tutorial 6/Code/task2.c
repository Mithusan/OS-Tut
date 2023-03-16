#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int main(void){
	int process = fork();
    
    	//If Child Proccess
    	if (process == 0){
        	sleep(1);
        	printf("Child process\n");
        	exit(0);
    	}
    
    	//Parent Process
    	while(wait(NULL) > 0);
    	printf("Parent process\n");
}
