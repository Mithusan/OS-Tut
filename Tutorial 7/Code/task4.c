#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main(void)
{
	pid_t parent = getpid();
	pid_t pid = fork();
	
		if(pid == -1){
		printf("fork failed");
		}
		
		else if(pid > 0){
		int status;
		waitpid(pid, &status, 0);
		}
		
		else{
		pid_t pid_process = getpid();
		int status;
		char * argv_list[] = {"process",NULL};
		execv("process", argv_list);
		wait(5);
		kill(pid_process,SIGTSTP);
		wait(10);
		kill(pid_process,SIGCONT);
		exit(0);
		}
	
}