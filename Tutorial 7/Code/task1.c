#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>

typedef struct process {
    char name[256];
    int priority;
    int pid;
    int runtime;
} proc;

typedef struct linked_list {
    proc process;
    queue linked_list;
} queue;

void push(proc process){
    
}

int main(void){
    
}