/**
 * @file q5.c
 * @author Group 12
 * @brief 
 * @version 1.0
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */


/**
 * Import all necessary header files.
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief Define constant to use throughout program. 
 *        Ensures max length of a processes name is 
 *        100 characters. Placing a leeway threshold 
 *        based on the file provided --> processes_q5.txt.
 * 
 */
#define MAX_NAME_LENGTH 100

/**
 * @brief Initiate a process struct data type with 
 *        necessary fields name, priority, pid
 *        and runtime. 
 * 
 *        Used to create instances of processes to 
 *        queue and dequeue. 
 * 
 */
struct process {
    char name[MAX_NAME_LENGTH];
    int priority;
    pid_t pid;
    int runtime;
    struct process *next;
};

/**
 * @brief Adds a new process to the linked list by creating a new struct process 
 *        > setting its values based on the arguments passed to the function.
 *        
 *        If the linked list is empty > new process is added. 
 *        
 *        If the linked list isn't empty > add process to end of list.
 *  
 *        Return pointer to new list. 
 * 
 * @param head 
 * @param new_process 
 */
void addProcess(struct process **head, struct process *new_process) {
    if (*head == NULL) {
        *head = new_process;
    } else {
        struct process *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_process;
    }
}


/**
 * @brief Removes a process with the given name from the linked list.
 *        
 *        Searches for the node containing the process with the given name 
 *        when found > removes it from the list.
 *          
 *        Returns a pointer to the linked list. 
 * 
 * @param head 
 * @param name 
 * @return struct process* 
 */
struct process *delete_name(struct process **head, char *name) {
    struct process *current = *head;
    struct process *previous = NULL;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            return current;
        }
        previous = current;
        current = current->next;
    }
    return NULL;
}

/**
 * @brief Function to execute process by assigning process id to fork.
 *        
 *        Creates child process > execute process binary. 
 *        
 *        Have an error handler to ensure process is created. 
 *        
 *        Child process runs till specified runtime and parent
 *        process waits for full completion.
 * 
 *        Parent process id is set to that of child using pointer.     
 * 
 *        Once child is fully terminated and parent receives exit
 *        status --> print name, priority, pid, and runtime of the process.
 *    
 * @param p 
 */
void execProcess(struct process *p) {
    pid_t pid = fork();
    if (pid == 0) {
        char path[MAX_NAME_LENGTH + 2];
        snprintf(path, MAX_NAME_LENGTH + 2, "./%s", p->name);
        char *args[] = {path, NULL};
        execvp(args[0], args);
        exit(1);
    } else if (pid < 0) {
        printf("Error: Failed to fork process\n");
        exit(1);
    } else {
        p->pid = pid;
        sleep(p->runtime);
        kill(p->pid, SIGINT);
        waitpid(pid, NULL, 0);
        printf("Name: %s, Priority: %d, PID: %d, Runtime: %d\n", p->name, p->priority, p->pid, p->runtime);
    }
}

/**
 * @brief Main driver initializes a queue > read processes from file 
 *        > processes_q5.txt > add them to queue > close file. 
 *        
 *        Iterate through queue and execute processes as long as
 *        queue isn't empty.
 * 
 *        Based on the assignment requirements, execute processes
 *        with a priority of zero first. 
 * 
 *        Once priority of zero process completed > remove from queue
 *        using delete_name() function as advised. 
 *         
 *        For any process with a pid > 0, dequeue from front of the 
 *        queue and execute the process after all priority processes
 *        have completed. 
 * 
 *        Upon doing so will essentially print name, priority, pid, and 
 *        runtime of the process by calling the execProcess() function. 
 * 
 *         Free up memory and allocation space by destroying the queue.
 *        
 * @return int 
 */
int main() {
    FILE *file = fopen("processes_q5.txt", "r");
    if (file == NULL) {
        printf("Error: Failed to open processes_q5.txt\n");
        exit(1);
    }

    struct process *head = NULL;

    char name[MAX_NAME_LENGTH];
    int priority, runtime;
    while (fscanf(file, "%s %d %d", name, &priority, &runtime) != EOF) {
        struct process *p = malloc(sizeof(struct process));
        strcpy(p->name, name);
        p->priority = priority;
        p->pid = 0;
        p->runtime = runtime;
        p->next = NULL;
        addProcess(&head, p);
    }

    fclose(file);

    struct process *current = head;
    while (current != NULL) {
        if (current->priority == 0) {
            execProcess(current);
            struct process *removed = delete_name(&head, current->name);
            free(removed);
            current = head;
        } else {
            current = current->next;
        }
    }

    current = head;
    while (current != NULL) {
        execProcess(current);
        struct process *removed = delete_name(&head, current->name);
        free(removed);
        current = head;
    }

    return 0;
}
