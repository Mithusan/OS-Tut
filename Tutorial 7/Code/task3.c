#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define SHELL "/bin/sh"

/*void child_process(){
    int pid = getpid();
    printf("Child Process PID: %d\n", pid);
    sleep(5);
}*/

int main(void){
    pid_t pid;
    pid = fork();

    if (pid == -1){
        perror("Fork failed.");
        exit(1);
    } 
    else if (pid == 0){
        //Child Process
        int pid = getpid();
        printf("Child Process PID: %d\n", pid);
        execl(SHELL, SHELL, "./process", command, NULL)
        sleep(5);
        exit(0);
    }
    else {
        //Parent Process
        wait(NULL);//Wait for Child Process to terminate
        //sleep(1); //Wait for Child Process to Start
        printf("Sending LeSignalJames to Child Process\n");
        kill(pid, SIGINT);
        printf("LeChild has been Killed, Counter Terrorist Win\n");
        exit(0);
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