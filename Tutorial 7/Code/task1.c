#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct proc {
    char name[256];
    int priority;
    int pid;
    int runtime;
};

struct queue {
    struct proc process;
    struct queue *linked_list;
};

struct queue head;

//used to find a node in a chain of linked lists
struct queue traverse(struct queue head, int index){
    struct queue currIndex = head;
    int i = 0;
    do {
        if (i < index){
            currIndex = *currIndex.linked_list;
        }
        else if (i >= index){
            return currIndex;
        }
        i++;
    } while(currIndex.linked_list != NULL);

    return currIndex;
}

void push(struct proc process) {
    struct queue newNode;
    newNode.process = process;
    *traverse(head, 200).linked_list = newNode;
} 

int main(void){
    
}