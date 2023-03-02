#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double euclid_dist(int x1, int y1, int x2, int y2){
	double result;
	result = sqrt(pow((double)(x2 - x1), 2) + pow((double)(y2 - y1), 2)); 
	return result;
}

int main(void){
	for (int i = 0; i < 10; i++){
		double x2 = rand() % 100;
		double x1 = rand() % 100;
		double y2 = rand() % 100;
		double y1 = rand() % 100;
		
		printf("%lf \n(%f,%f) (%f,%f)", euclid_dist(x1, y1, x2, y2), x1, y1, x2, y2);
		printf("\n\n");
	}
	printf("\n");
}
