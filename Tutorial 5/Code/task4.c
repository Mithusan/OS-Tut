#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 10
#define STUDENT_COUNT 10

float total_grade;
pthread_mutex_t mutex1;

void *class_total(void *param){
	float *grades= (float *)param;
	
	//Mutal Exclusion
	pthread_mutex_lock(&mutex1);//Lock Acquired
	total_grade += *grades;
	pthread_mutex_unlock(&mutex1);//Lock Released
	
	return 0;
}

int main(){
	//Variables
	pthread_t thread[THREAD_COUNT];
	pthread_mutex_init(&mutex1, NULL);
	float grade[STUDENT_COUNT];
	
	//Student Details
	for(int i = 0; i < STUDENT_COUNT; i++){
		printf("Enter Student %d's Grade: ", i+1);
		scanf("%f", &grade[i]);
	}
	
	printf("\n****************************************\n\n");
	//Create Thread for each student
	for(int i = 0; i < THREAD_COUNT; i++){
		pthread_create(&thread[i], NULL, class_total, (void *)&grade[i]);
		pthread_join(thread[i], 0);
	}
	
	printf("The Total Grade is : %.2f\n", total_grade);
}
