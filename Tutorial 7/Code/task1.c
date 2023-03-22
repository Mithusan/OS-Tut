#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue *headPtr, head;

#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 1024

// Structure for the process
struct proc {
    char name[256];
    int priority;
    int pid;
    int runtime;
};

// Structure for the linked list
struct queue {
    struct proc process;
    struct queue *linkedList;
};

//Adds a node to the tail
void push(struct proc process) {
    struct queue newNode;
    newNode.process = process;
    *traverse(head, 200).linkedList = newNode;
}

//used to find a node in a chain of linked lists
struct queue traverse(struct queue head, int index){
    struct queue currIndex = head;
    int i = 0;
    do {
        if (i < index){
            currIndex = *currIndex.linkedList;
        }
        else if (i >= index){
            return currIndex;
        }
        i++;
    } while(currIndex.linkedList != NULL);

    return currIndex;
}

int main() {
    //file setup
    struct proc *headProcPtr, headProc;

    char path[128];

    printf("Please enter the path of the process.txt...\n");
    scanf("%[^\n]s", path);

    FILE *processFile = fopen(path, "r");

    if (processFile == NULL){
        printf("No file in that location...\n");
        return 1;
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    struct proc procs[10];

    //j is the currecnt procs number listed
    int j = 0;

    //line contains the text and read contains the line length
    while ((read = getline(&line, &len, processFile)) != -1) {
        int i = 0;
        int iterationID = 0;
        char buffer[128] = "";

        printf("%s", line);

        //read until your first comma
        for (i = 0; i < read; i++){
            if ((!line[iterationID]) == ','){
                buffer[i] = line[iterationID];
                printf(line[iterationID]);
            }
            else {
                buffer[i] = "\0";
                break;
            }
            iterationID++;
        }

        strcpy(procs[j].name, buffer);       
        buffer[128] = "";
}