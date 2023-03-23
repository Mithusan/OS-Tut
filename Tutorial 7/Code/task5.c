#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_NAME_LENGTH 100

struct process {
    char name[MAX_NAME_LENGTH];
    int priority;
    pid_t pid;
    int runtime;
    struct process *next;
};

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

void execProcess(struct process *p) {
    pid_t pid = fork();
    if (pid == 0) {
        char path[MAX_NAME_LENGTH + 2];
        snprintf(path, MAX_NAME_LENGTH + 2, "./%s", p->name);
        char * argv_list[] = {"process",NULL}; 
        execv(argv_list[0], argv_list);
        exit(1);
    } else if (pid < 0) {
        printf("Error: Failed to fork process\n");
        exit(1);
    } else {
        p->pid = pid;
        sleep(p->runtime);
        kill(p->pid, SIGINT);
        waitpid(pid, NULL, 0);
        
        p->name[strlen(p->name)-1] = ' ';

        printf("Name: %s\nPriority: %d\nPID: %d\nRuntime: %d\n", p->name, p->priority, p->pid, p->runtime);
        printf("************************\n");
    }
}


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
