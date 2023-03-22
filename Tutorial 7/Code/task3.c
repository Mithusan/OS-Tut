#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void child_process(){
    int pid = getpid();
    printf("Child Process PID: %d\n", pid);
    sleep(5);
}

int main(void){
    pid_t pid;
    pid = fork();

    if (pid == -1){
        perror("Fork failed.");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0){
        //Child Process
        child_process();
        exit(EXIT_SUCCESS);
    }
    else {
        //Parent Process
        sleep(1); //Wait for Child Process to Start
        printf("Sending LeSignalJames to Child Process\n");
        kill(pid, SIGINT);
        wait(NULL);//Wait for Child Process to terminate
        printf("LeChild has been Killed, Counter Terrorist Win\n");
        exit(EXIT_SUCCESS);
    }
}


/*
int main(void)
{
    pid_t parent = getpid();
    pid_t pid = fork();

    if (pid == -1)
    {
        printf("Fork failed.");
    } 
    else if (pid > 0)
    {
        int status;
        
        printf("%d parentld\n",(int)pid);
    }
    else 
    {
        pid_t pid_process = getpid();
        char * argv_list[] = {"process",NULL}; 
        execv(argv_list[0], argv_list);
        exit();
        printf("%d child \n",(int)pid);
        sleep(5);
        
        kill(pid, SIGINT);
    }
}*/