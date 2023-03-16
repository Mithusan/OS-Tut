#include <stdio.h>
#include <stdlib.h>

int main(void){

FILE* file;
int d[30];
int i=0;

file=fopen("question2.txt","r");

if(file == NULL){
printf("File not found!");
}

while(fscanf(file,"%d", &d[i]) !=EOF){
i++;
}
fclose(file);
d[i]='\0';
i=0;
while(d[i]!='\0'){
printf("%d\n",d[i]);
i++;
}

}
