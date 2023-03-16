#include <stdio.h>
#include <stdlib.h>

int main(void){
	double array[5] = {1.2, 5.5, 2.1, 3.3, 3.3};
	
	for (int i=0; i < 5; i++){
		if (array[i] > array[i-1]) {
			printf("Greater Than, ");
		}
		else if (array[i] < array[i-1]) {
			printf("Less Than, ");
		}
		else {
			printf("Equal To");
		}
	}
	printf("\n");
}
