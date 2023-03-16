#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int main(void){
	FILE *file;
	char buffer[10];
	
	file = fopen("child1.txt", "w");
	fputs("child 1", file);
	fclose(file);
	file = fopen("child2.txt", "w");
	fputs("child 2", file);
	fclose(file);

	int child1 = fork();
	int child2 = fork();
	
	sleep(1);//Wait one Second
	
	if (child1 == 0 && child2 > 0) {
		file = fopen("child1.txt", "r");
		fscanf(file, "%[^\n]", buffer);
		fclose(file);
		printf("%s ", buffer);
	}
	else if (child1 > 0 && child2 == 0) {
		file = fopen("child2.txt", "r");
		fscanf(file, "%[^\n]", buffer);
		fclose(file);
		printf("%s ", buffer);
    	}
}
