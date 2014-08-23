/**
* Fork process
*
* todo:
* spawn arcg-2 process and sleep them for argv[proc_id] times
* main sleep for argv[1] times
* wait for working childs
*
* usage:
* fork main_steps p1_steps p2_steps ... pn_steps
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) {
	int i;
	char argbuff[50];
	pid_t pid;
	int status;

	for(i = 0; i<argc-2; i++) {
		if (fork() == 0) {
			sprintf(argbuff, "%d", i);
			execl("./pot", "pot", argbuff, argv[i+2], NULL);
			perror("error");
		}
	}

	for(i = 0; i<atoi(argv[1]); i++) {
		printf("[main] step %d\n", i);
		sleep(1);
	}

	for(i = 0; i<argc-2; i++) {
		pid = wait(&status);
		printf("pid = %d\nstatus = %d\n", pid, WEXITSTATUS(status));
	}

	printf("\nthe end\n");

	return 1;
}

