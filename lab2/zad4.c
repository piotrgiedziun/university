/**
* parms:
* range_start range_end process_count
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if(argc < 4) {
        return 1;
    }
    char startbuff[50], endbuff[50];
    pid_t pid;
    int start=atoi(argv[1]),
        end=atoi(argv[2]),
        process_count=atoi(argv[3]),
        i,
        per_process = ((end-start)/process_count)+1,
        pierwszych = 0,
        status;

    printf("per_process = %d\n",per_process);


    for(i = 0; i<process_count; i++) {
        if (fork() == 0) {
            printf("%d, %d\n", start+(i*per_process), (i+1)*per_process);
            sprintf(startbuff, "%d", start+(i*per_process));
            sprintf(endbuff, "%d", (i+1)*per_process);
            execl("./pierwsza", "pierwsza", startbuff, endbuff, NULL);
            perror("error");
        }
    }

    for(i = 0; i<process_count; i++) {
        pid = wait(&status);
        printf("process stopped [pid=%d,p=%d]\n", pid, WEXITSTATUS(status));
        pierwszych += WEXITSTATUS(status);
    }


    printf("pierwszych = %d\n", pierwszych);

    return 1;
}
