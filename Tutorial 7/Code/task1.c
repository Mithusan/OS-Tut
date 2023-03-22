#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 1024

// Structure for the process
typedef struct process {
    char name[MAX_NAME_LEN];
    int priority;
    int pid;
    int runtime;
} proc;

// Structure for the linked list
typedef struct linked_list {
    proc process;
    struct linked_list *next;
} queue;

// Function to add process to the linked list
void push(queue **head, proc process) {
    queue *new_node = (queue*) malloc(sizeof(queue));
    new_node->process = process;
    new_node->next = *head;
    *head = new_node;
}

int main() {
    queue *head = NULL;
    char line[MAX_LINE_LEN];
    char *token;
    proc process;

    // Open the file containing the processes
    FILE *file = fopen("processes.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read the file line by line
    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        // Parse the line and create the process struct
        token = strtok(line, ",");
        strncpy(process.name, token, MAX_NAME_LEN);
        token = strtok(NULL, ",");
        process.priority = atoi(token);
        token = strtok(NULL, ",");
        process.pid = atoi(token);
        token = strtok(NULL, ",");
        process.runtime = atoi(token);

        // Add the process to the linked list
        push(&head, process);
    }

    // Close the file
    fclose(file);

    // Iterate through the linked list and print the processes
    queue *current = head;
    while (current != NULL) {
        printf("Name: %s, Priority: %d, PID: %d, Runtime: %d\n",
               current->process.name, current->process.priority,
               current->process.pid, current->process.runtime);
        current = current->next;
    }

    return EXIT_SUCCESS;
}