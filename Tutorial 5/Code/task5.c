#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 11
#define STUDENT_COUNT 10

float total_grade;
float total_bellcurve;
float grade[STUDENT_COUNT];

pthread_mutex_t mutex1;
pthread_barrier_t barrier;

FILE *fs;

void *save_bellcurve(void *param){
	float *grades= (float *)param;

	//Total Grades
	//Mutal Exclusion
	pthread_mutex_lock(&mutex1);//Lock Acquired
	total_grade += *grades;
	pthread_mutex_unlock(&mutex1);//Lock Released
	
	//Total Bell Curve
	float bellcurve = *grades * 1.5;
	total_bellcurve += bellcurve;
	
	fprintf(fs, "%.2f\n", bellcurve);
	
	return 0;
}

void *read_grades(void *param){	
	//Variables
	FILE* fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int i = 0;
	
	//Opens File
	fp = fopen("grades.txt", "r");
	
	//If File Cannot be Opened
	if (fp == NULL){
		printf("Error! File Cannot be Opened");
	}
	
	//If File can be Opened
	//Loops until End of File
	while ((read = getline(&line, &len, fp)) != -1){
		grade[i] = atof(line);
		i++;
	}
	
	pthread_barrier_wait (&barrier);
	
	//Closes File
	fclose(fp);
	return 0;
}

int main(){
	//Variables
	pthread_t thread[THREAD_COUNT];
	pthread_barrier_init(&barrier, NULL, 1);
	
	//Read Grades
	pthread_create(&thread[0], NULL, read_grades, NULL);
	pthread_join(thread[0], 0);
	
	fs = fopen("bellcurve.txt", "w");
	
	//Calculate Grades
	for(int i = 1; i < THREAD_COUNT; i++){
		pthread_create(&thread[i], NULL, save_bellcurve, (void *)&grade[i-1]);
		pthread_join(thread[i], 0);
	}
	
	fclose(fs);
	
	printf("Total Grades: %.2f\n", total_grade);
	printf("\nAverage Before: %.2f\nAverage After: %.2f\n", total_grade/10, total_bellcurve/10);
	
}
