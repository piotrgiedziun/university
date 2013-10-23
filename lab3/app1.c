#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <signal.h>
#include <fcntl.h>

#define CASE_1 1
#define FIFO_NAME "fifo"
typedef int bool;
#define TRUE  1
#define FALSE 0

bool step_by_step = FALSE;

void signal_step_handler(int signum) {
	printf("step by step/slow mode %d\n",signum);
	step_by_step = !step_by_step;
}

int main(int argc, char* argv[]) {
	int pid, status, fd, i, res, count = 10, write_count = 0;
	char c = 'a';

	remove(FIFO_NAME);
	res = mkfifo(FIFO_NAME, 0666);
    
    if (res < 0 ) {
        perror("mkfifo create error");
        exit(1);
    }

    // O_RDWR - nie blokuje procesu
    // O_RDONLY lub O_WRONLY - blokuje
    fd = open(FIFO_NAME,O_RDWR);

    if (fd < 0 ) {
        perror("mkfifo open error");
        exit(1);
    }

	#ifdef CASE_1
		count = INT_MAX;
	#endif

	switch(pid = fork()) {
	case -1:
		perror("fork error");
		exit(1);

	case 0:
		printf("[child process] - reading\n");
		printf("[child process] - pid = %d\n", getpid());

		#ifdef CASE_1
			signal(SIGUSR1, signal_step_handler);
			pause();
		#endif

		for(i=0; i<count; i++) {
			read(fd, &c, 1024);
			printf("[child process] - character %c, pid = %d, step = 10\n", c, getpid());
			if (step_by_step)
				getchar();
		}

		close(fd);
		exit(0);

	default:
		printf("[main process] - writing\n");
		printf("[main process] - pid = %d\n", getpid());

		#ifdef CASE_1
			signal(SIGUSR1, signal_step_handler);
		#endif

		for(i=0; i<count; i++) {
			write(fd, &c, 1);
			write_count++;
			printf("[main process] - character %c, count = %d, pid = %d, sig = 12\n", c, write_count, getpid());
			if (step_by_step)
				usleep(1000000);
		}

		pid = wait(&status);
		close(fd);
		printf("pid = %d\nstatus = %d\n", pid, WEXITSTATUS(status));
	}

	return 0;
}