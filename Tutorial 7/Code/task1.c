#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>

struct queue *headPtr, head;

struct proc{
    char name[256];
    int priority;
    int pid;
    int runtime;
};

struct queue{
    struct proc process;
    struct queue *linkedList;
};

void push(struct proc process) {
    struct queue newNode;
    newNode.process = process;
    *traverse(head, 200).linkedList = newNode;
}

int main(){

}