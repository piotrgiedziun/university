/**
* Obliczanie ilosci liczb pierwszych z zadanego zakresu
*
* usage:
* ./pierwsza_zad2 [zakres_start] [zakres_end]
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

struct result_struct {
    int pocz;
    int koniec;
    int ile;
} result;

int pierwsza(int n)
{
    int i;
    if(n==1) return 0;
    for(i=2;i*i<=n;i++) {
        if(n%i == 0) return 0;
    }
    return 1;
}

int open_fifo(char* filename) {
    int fd = open(filename,O_RDWR);

    if (fd < 0 ) {
        perror("mkfifo open error");
        exit(1);
    }
    
    return fd;
}

int main(int argc, char* argv[]) {
    int i, ifd, ofd, pierwszych=0;

    ifd = open_fifo("i_fifoYOLO");
    read(ifd,&result,sizeof(result));
    close(ifd);
     
    for(i = result.pocz; i<result.koniec; i++) {
        if(pierwsza(i)==1)
            pierwszych++;
    }

    // set data
    result.ile = pierwszych;

    ofd = open_fifo("o_fifoYOLO");

    write(ofd,&result,sizeof(result));
    
    close(ofd);

    return 0;
}

