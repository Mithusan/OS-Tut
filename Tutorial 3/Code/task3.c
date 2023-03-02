#include <stdio.h>

struct student{
	int studentID;
	int age;
	int year;
};

void save_student(struct student student){
	FILE *file;
	file = fopen("student.txt","a");
	fprintf(file, "%d, %d, %d\n", student.studentID, student.age, student.year);
	fclose(file);
}

int main(void){
	int studentID, age, year;
	struct student student;
	
	printf("What is your Student ID? ");
	scanf("%d", &studentID);
	printf("What is your age? ");
	scanf("%d", &age);
	printf("What is your year of study? ");
	scanf("%d", &year);
	
	student.studentID = studentID;
	student.age = age;
	student.year = year;
	
	save_student(student);
}
