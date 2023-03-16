#include <stdio.h>
#include <stdlib.h>

int main(void){
	char array[] = "hello world";
	
	int i = 0;
	while (1) {
		if (array[i] != '\0'){
			printf("%c", array[i]);
		}
		else {
			break;
		}
		i++;
	}
	printf("\n");
}
