#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 1024

struct proc {
    char name[MAX_NAME_LEN];
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
    //Variables
    char line[MAX_LINE_LEN];
    char *token;
    struct proc process;
    
    // Open the file containing the processes
    FILE *file = fopen("processes.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
}