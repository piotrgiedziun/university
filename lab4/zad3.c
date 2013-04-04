/**
* a -> b -> c -> etc
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int fd_in[2],fd_out[2],fd_between[2], i;
    char c;
    int ile = atoi(argv[1]);
    
    pipe(fd_in);
    pipe(fd_out);
    pipe(fd_between);
    
    // sub1
    if (fork() > 0) {
        close(fd_out[1]);
        close(fd_between[0]);
        
        for(i=0; i<ile; i++) {
            read(fd_out[0], &c, 1);
            printf("[sub1] = %c \n",c);
            c+=1;
            write(fd_between[1], &c,1);
        }

        close(fd_out[0]);
        close(fd_between[1]);
        exit(0);
    }
    // sub2
    if (fork() > 0) {
        close(fd_in[0]);
        close(fd_between[1]);
        
        for(i=0; i<ile; i++) {
            read(fd_between[0], &c, 1);
            printf("[sub2] = %c \n",c);
            c+=1;
            write(fd_in[1], &c,1);
        }
        
        close(fd_in[1]);
        close(fd_between[0]);
        exit(0);
    }
    
    close(fd_out[0]);
    close(fd_in[1]);
    close(fd_between[0]);
    close(fd_between[1]);
    
    printf("Podaj znak: ");
    c=getchar();
    for(i=0; i<ile; i++) {
        write(fd_out[1], &c, 1);
        c+=1;
        read(fd_in[0], &c, 1);
    }
    printf("[main] = %c \n",c);
    
    close(fd_out[0]);
    
    return 0;
}

