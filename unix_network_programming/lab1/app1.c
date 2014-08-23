#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int pid, status;
	
	#ifdef DEBUG
		printf("debug on\n");
	#endif

	switch(pid = fork()) {
	case -1:
		perror("fork error");
		exit(1);

	case 0:
		printf("child process\n");
		printf("pid = %d\nppid = %d\n", getpid(), getppid());
		sleep(1);
		exit(1);

	default:
		pid = wait(&status);
		printf("main process\n");
		printf("pid = %d\nstatus = %d\n", pid, WEXITSTATUS(status));
	}

	return 0;
}