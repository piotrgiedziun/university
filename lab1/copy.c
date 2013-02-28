/**
*  Copy file
*  
*  usage:
*    copy src dest
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


#define SIZE 512

int main( int argc, char* argv[] ) {
    int buf_count;
    int file1, file2;
    char buf[SIZE];

    file1 = open(argv[1], O_RDONLY);
    if(file1 < 0 ) {
        perror("file1 open error");
        exit(0);
    }

    file2 = open(argv[2], O_WRONLY | O_CREAT, 0666);
    if(file2 < 0) {
        perror("file2 open error");
        exit(0);
    }

    do {
        buf_count = read(file1,buf,SIZE);
        write(file2, buf, buf_count);
    } while(buf_count != 1);

    close(file1);
    close(file2);

    return 0;
}