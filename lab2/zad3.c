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

void spawn(int poziom, char* argv[]) {
	int i;
	pid_t pid;
	int status;

	if(poziom == 0) return;

	if (fork() == 0) {
		spawn(poziom-1, argv);
		exit(poziom-1);
	}
	for(i = 0; i<atoi(argv[poziom]); i++) {
			if(poziom == 1) {
				printf("[main] step %d\n", i);
			}else{
				printf("[child %d] step %d\n", poziom, i);
			}
			sleep(1);
	}
	pid = wait(&status);
	printf("pid = %d\nstatus = %d\n", pid, WEXITSTATUS(status));
}

int main(int argc, char* argv[]) {
	spawn(argc-2, argv);

	printf("\nthe end\n");

	return 1;
}

