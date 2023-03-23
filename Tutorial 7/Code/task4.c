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
		int c_pid = getpid();
        printf("Child Process PID: %d\n", c_pid);
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
		sleep(10);
		kill(pid, SIGCONT);
        waitpid(pid, &status, 0);
		exit(0);
    }
}