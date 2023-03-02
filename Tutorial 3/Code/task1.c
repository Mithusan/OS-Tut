#include <stdio.h>

int main(void){
	char fName[100];
	int age, height;
	
	printf("What is your First Name? ");
	scanf("%s", fName);
	printf("What is your age? ");
	scanf("%d", &age);
	printf("What is your height? ");
	scanf("%d", &height);
	
	printf("\nYour first name is %s, your age is %i, and your height is %icm.\n", fName, age, height);
}
