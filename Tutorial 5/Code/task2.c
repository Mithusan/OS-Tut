#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 5
#define STUDENT_COUNT 5

void *bell_curve(void *param){
	float *grades= (float *)param;
	float bellcurve = *grades * 1.5;
	
	if (bellcurve > 100){
		bellcurve = 100;
	}
	
	printf("%.2f\n\n", bellcurve);
	
	return 0;
}

int main(){
	//Variables
	pthread_t thread[THREAD_COUNT];
	float grade[STUDENT_COUNT];
	
	//Student Details
	for(int i = 0; i < STUDENT_COUNT; i++){
		printf("Enter Student %d's Grade: ", i+1);
		scanf("%f", &grade[i]);
	}
	
	printf("\n****************************************\n\n");
	//Create Thread for each student
	for(int i = 0; i < THREAD_COUNT; i++){
		printf("Student %d: ", i+1);
		pthread_create(&thread[i], NULL, bell_curve, (void *)&grade[i]);
		pthread_join(thread[i], 0);
	}
}
