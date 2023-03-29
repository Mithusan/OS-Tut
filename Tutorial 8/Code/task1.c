//"proc.c"

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>

struct proc{
    char parent[256];
    char name[256];
    int priority;
    int memory;
};

struct proc_tree{
    struct proc process;
    struct proc_tree *left;
    struct proc_tree *right;
};

struct proc_tree* new_proc(char parent[], char name[], int priority, int memory){
    struct proc_tree *pr = (struct proc_tree*)malloc(sizeof(struct proc_tree));
    memset(pr->process.parent, 0, 256);
    memset(pr->process.name, 0, 256);
    strcpy(pr->process.parent, parent);
    strcpy(pr->process.name, name);
    pr->process.priority = priority;
    pr->process.memory = memory;
    pr->left = pr->right = NULL;
    return pr;
}

struct proc_tree* insert_into_bt(struct proc_tree* root, struct proc_tree* pr, bool *inserted){
    if(strcmp(pr->process.parent, "NULL") == 0){
        *inserted = true;
        return pr;
    }

    if(!root){
       return NULL; 
    }

    if(strcmp(pr->process.parent, root->process.name) == 0){
        if(!root->left){
            root->left = pr;
        }
        else if(!root->right){
            root->right = pr;
        }

        *inserted = true;
        return root;
    }
    if(!(*inserted)){
        root->left = insert_into_bt(root->left, pr, inserted);
    }
    if(!(*inserted)){
        root->right = insert_into_bt(root->right, pr, inserted);
    }
    return root;
}

void print_bt(struct proc_tree* root){
    if(!root){
        return;
    }

    print_bt(root->left);
    printf("process -> {name: %s, parent: %s, priority: %d, memory: %d MB}\n\n", root->process.name, root->process.parent, root->process.priority, root->process.memory);
    print_bt(root->right);
}

int main(int argc, char *argv[]){
    FILE *fp = fopen("processes_tree.txt", "r");
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    struct proc_tree *root = NULL;

    while((read = getline(&line, &length, fp)) != -1){
        char *token = strtok(line, ",");
        char parent[256];
        char name[256];
        int priority, memory;
        priority = memory = 0;
        int counter = 0;

        while(token){
            if(token[0] == ' '){
                token++;
            }
            
            counter++;
            if(counter == 1){
                memset(parent, 0, 256);
                strcpy(parent, token);
            }
            else if(counter == 2){
                memset(name, 0, 256);
                strcpy(name, token);
            }
            else if(counter == 3){
                priority = atoi(token);
            }
            else if(counter == 4){
                memory = atoi(token);
            }
            token = strtok(NULL, ",");
        }
        bool inserted = false;
        root = insert_into_bt(root, new_proc(parent, name, priority, memory), &inserted);
    }
    free(line);
    print_bt(root);
    return EXIT_SUCCESS;
}
