#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_COUNT 20

extern char *optarg;

int main(int argc, char* argv[]) {
	// 20 to max, YOLO
	int cname, status, pid, i, j, max_count=0;

	char app_name[MAX_COUNT][100];
	int fd[MAX_COUNT][2];
	
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
    	if ( pipe(fd[i]) == -1 ) {
    		perror("pipe error");
    		exit(1);
    	}
    }

    for(i=0; i<max_count; i++) {
		// start process
		switch(pid = fork()) {
			case -1:
				perror("fork error");
				exit(1);
			case 0:
				// not first
				if ( i != 0 ) {
					// set in
					if ( dup2(fd[i-1][0], STDIN_FILENO) == -1 ) {
						perror("dup2 error");
						exit(1);
					}
				}

				// not last
				if ( i != (max_count-1) ) {
					// set out
					if ( dup2(fd[i][1], STDOUT_FILENO) == -1 ) {
						perror("dup2 error");
						exit(1);
					}
				}

				// close all pipes
				for(j=0; j<max_count; j++) {
			    	close(fd[j][0]);
			    	close(fd[j][1]);
			    }

				execlp(app_name[i], app_name[i], NULL);
				perror("execlp error");
				exit(1);
		}
    }

    for(i=0; i<max_count; i++) {
    	close(fd[i][0]);
    	close(fd[i][1]);
    }

    for(i=0; i<max_count; i++) {
    	wait(&status);
    }

	return 0;
}