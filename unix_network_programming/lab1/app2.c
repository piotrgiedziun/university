#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef int bool;
#define TRUE  1
#define FALSE 0

extern char *optarg;

void create_recursion_process(int process_count) {
	int pid, status;

	if(process_count == 0) return;
	
	pid = fork();
	if (pid == 0) {
		create_recursion_process(process_count-1);
		exit(process_count-1);
	}else if(pid == -1) {
		perror("fork error");
		exit(1);
	}

	printf("^start process [id=%d, pid = %d, ppid = %d]\n", process_count, getpid(), getppid());
	sleep(1);

	pid = wait(&status);
	printf("$close process [pid = %d, status = %d]\n", pid, WEXITSTATUS(status));
}

void create_for_process(int process_count) {
	int i, pid, status;

	for(i = 0; i<process_count; i++) {
			switch(pid = fork()) {
				case -1:
					perror("fork error");
					exit(1);

				case 0:
					printf("^start process [id=%d, pid = %d, ppid = %d]\n", i+1, getpid(), getppid());
					sleep(1);
					exit(i+1);
			}
	}

	for(i = 0; i<process_count; i++) {
		pid = wait(&status);
		printf("$close process [pid = %d, status = %d]\n", pid, WEXITSTATUS(status));
	}

}

int main(int argc, char* argv[]) {
	int cname, process_count;
	bool app_type_recursion=FALSE, process_count_received=FALSE;

	// get process count and app type
	while ((cname = getopt(argc, argv, ":c:r")) != -1) {
		switch(cname) {
		case 'c':
			process_count_received = TRUE;
			process_count = atoi(optarg);
			break;
        case 'r':
        	app_type_recursion = TRUE;
			break;
        }
    }

    if (!process_count_received) {
    	printf("error no parm");
		return 2;
	}

	// create process
	if ( app_type_recursion ) {
		create_for_process(process_count);
	} else {
		create_recursion_process(process_count);
	}

	return 0;
}