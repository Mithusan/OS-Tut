#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

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
        char * argv_list[] = {"process",NULL}; 
        execv(argv_list[0], argv_list);
		exit(0);
		
	}
    else {
		//Parent Process
        // wait 5 seconds then send interupt signal
		int status;
		sleep(5);
        kill(pid, SIGTSTP);
		sleep(3);
		kill(pid, SIGCONT);
		waitpid(pid, NULL, 0);
		kill(pid, SIGINT);
		exit(0);
    }
}