#include <stdio.h>
#include <stdlib.h>

int main(void){

char* prof;
int* std_id;
int* grades;
int size=256;
int marks;


prof=(char*)calloc(size,sizeof(char));

printf("Hi Professor what is your name: ");
fgets(prof,size,stdin);

if(prof==NULL){
printf("no memory for professor");
}

printf("Hi %s,how many students do you mark:",prof);
scanf("%d",&marks);

grades=(int*)malloc(marks *sizeof(int));
std_id=(int*)malloc(marks *sizeof(int));

if(grades==NULL || std_id==NULL){
printf("no memory for students id or grades");
}

free(prof);
free(std_id);
free(grades);
}
