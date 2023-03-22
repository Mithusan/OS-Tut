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
        waitpid(pid, &status, 0);
        int id=getpid();
        printf("%d\n",id);
    }
    else 
    {
        pid_t pid_process = getpid();
        char * argv_list[] = {"process",NULL}; 
        execv("process", argv_list);
        wait(5);
        int id=getpid();
        printf("%d\n",id);
        kill(pid_process, SIGINT);
    }
}