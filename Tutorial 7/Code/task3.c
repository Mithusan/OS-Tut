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
        wait(pid, &status,0);
        printf("%d parentld\n",(int)pid);
    }
    else 
    {
        pid_t pid_process = getpid();
        char * argv_list[] = {"process","./sigtrap",NULL};
        execv(argv_list[1], argv_list);
        printf("%d child \n",(int)pid);
        sleep(5);
        printf("%d parentld\n",(int)parent);
        kill(pid, SIGINT);
    }
}