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

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) {
    int i;

	for(i = 0; i<argc-2; i++) {
		if (fork() == 0) {
			int j;
			for(j = 0; j<atoi(argv[i+2]); j++) {
				printf("[child %d] step %d\n", i, j);
				sleep(1);
			}
			exit(i);
		}
	}

	for(i = 0; i<atoi(argv[1]); i++) {
		printf("[main] step %d\n", i);
		sleep(1);
	}

	pid_t pid;
	int status;
	for(i = 0; i<argc-2; i++) {
		pid = wait(&status);
		printf(">\npid = %d\nstatus = %d\n", pid, WEXITSTATUS(status));
	}

	printf("\nthe end\n");

	return 1;
}
