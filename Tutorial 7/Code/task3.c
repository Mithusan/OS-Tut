#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

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
}