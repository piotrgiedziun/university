#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_COUNT 20

extern char *optarg;

int main(int argc, char* argv[]) {
	// 20 to max, YOLO
	int cname, res, status, pid, i, max_count=0;

	char app_name[MAX_COUNT][100], fifo_name[100];
	
	// get process count and app type
	while ((cname = getopt(argc, argv, ":p:")) != -1) {
		switch(cname) {
		case 'p':
			sprintf(app_name[max_count], "%s", optarg);
			max_count++;
        }
    }

    if ( max_count > MAX_COUNT ) {
    	printf("max allowed parms is %d\n", MAX_COUNT);
    	exit(2);
    }

    for(i=0; i<max_count; i++) {
    	sprintf(fifo_name, "fifo_%d", i);
		remove(fifo_name);
		res = mkfifo(fifo_name, 0666);
	    
	    if (res < 0 ) {
	        perror("mkfifo create error");
	        exit(1);
	    }
    }

    for(i=0; i<max_count; i++) {
    	int fd_fork;
		// start process
		switch(pid = fork()) {
			case -1:
				perror("fork error");
				exit(1);
			case 0:
				// not first
				if ( i != 0 ) {
					// set in
					sprintf(fifo_name, "fifo_%d", i-1);
					fd_fork = open(fifo_name,O_RDONLY);

					if (fd_fork < 0 ) {
				        perror("mkfifo open error");
				        exit(1);
				    }

					if ( dup2(fd_fork, STDIN_FILENO) == -1 ) {
						perror("dup2 error");
						exit(1);
					}
				}

				// not last
				if ( i != (max_count-1) ) {
					// set out
					sprintf(fifo_name, "fifo_%d", i);
					fd_fork = open(fifo_name,O_WRONLY);

					if (fd_fork < 0 ) {
				        perror("mkfifo open error");
				        exit(1);
				    }

					if ( dup2(fd_fork, STDOUT_FILENO) == -1 ) {
						perror("dup2 error");
						exit(1);
					}
				}

				execlp(app_name[i], app_name[i], NULL);
				perror("execlp error");
				exit(1);
		}
    }

    // main

    for(i=0; i<max_count; i++) {
    	wait(&status);
    }

    for(i=0; i<max_count; i++) {
    	sprintf(fifo_name, "fifo_%d", i);
		remove(fifo_name);
	}

	return 0;
}