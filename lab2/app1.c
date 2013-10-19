#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

#define CASE_1 1

typedef int bool;
#define TRUE  1
#define FALSE 0

bool step_by_step = FALSE;

void signal_step_handler(int signum) {
	printf("step by step/slow mode %d\n",signum);
	step_by_step = !step_by_step;
}

int main(int argc, char* argv[]) {
	int pid, status, fd[2], i, count = 10, write_count = 0;
	char c = 'a';
	pipe(fd);

	#ifdef CASE_1
		count = INT_MAX;
	#endif

	switch(pid = fork()) {
	case -1:
		perror("fork error");
		exit(1);

	case 0:
		close(fd[1]);
		printf("[child process] - reading\n");
		printf("[child process] - pid = %d\n", getpid());

		#ifdef CASE_1
			signal(SIGUSR1, signal_step_handler);
			pause();
		#endif

		for(i=0; i<count; i++) {
			read(fd[0], &c, 1024);
			printf("[child process] - character %c, pid = %d, step = 10\n", c, getpid());
			if (step_by_step)
				getchar();
		}

		close(fd[0]);
		exit(0);

	default:
		close(fd[0]);
		printf("[main process] - writing\n");
		printf("[main process] - pid = %d\n", getpid());

		#ifdef CASE_1
			signal(SIGUSR1, signal_step_handler);
		#endif

		for(i=0; i<count; i++) {
			write(fd[1], &c, 1);
			write_count++;
			printf("[main process] - character %c, count = %d, pid = %d, sig = 12\n", c, write_count, getpid());
			if (step_by_step)
				usleep(1000000);
		}

		pid = wait(&status);
		close(fd[1]);
		printf("pid = %d\nstatus = %d\n", pid, WEXITSTATUS(status));
	}

	return 0;
}