#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define THREAD_COUNT 5
#define STUDENT_COUNT 5

struct student{
	char name[50];
	int student_id;
	float grade;
} s[STUDENT_COUNT];


void *bell_curve(void *param){
	float *grades= (float *)param;
	float bellcurve = *grades * 1.5;
	
	if (bellcurve > 100){
		bellcurve = 100;
	}
	
	printf("Grade: %.2f\n\n", bellcurve);
	
	return 0;
}

int main(){
	//Variables
	pthread_t thread[THREAD_COUNT];

	for (int i = 0; i < STUDENT_COUNT; i++){
		printf("Student %d\n\n", i+1);
		printf("Enter Student name (First Name Only): ");
		scanf("%s", s[i].name);
		
		printf("Enter Student ID: ");
		scanf("%d", &s[i].student_id);
		
		printf("Enter Student grade: ");
		scanf("%f", &s[i].grade);
		
		printf("\n**************************\n");
	}

	//Create Thread for each student
	for(int i = 0; i < THREAD_COUNT; i++){
		printf("%s - %d\n", s[i].name, s[i].student_id);
		pthread_create(&thread[i], NULL, bell_curve, (void *)&s[i].grade);
		pthread_join(thread[i], 0);
	}
}

