/**
* Obliczanie ilosci liczb pierwszych z zadanego zakresu
*
* usage:
* ./pierwsza_zad2 [zakres_start] [zakres_end]
*/
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

int main(int argc, char* argv[]) {
    int i, fd, res,    
    start=atoi(argv[1]),
    end=atoi(argv[2]),
    pierwszych=0;

    for(i = start; i<end; i++) {
        if(pierwsza(i)==1)
            pierwszych++;
    }

    // set data
    result.pocz = start;
    result.koniec = end;
    result.ile = pierwszych;

    fd = open("results.txt", O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);

    if(fd < 0 ) {
        perror("fd open error");
        exit(0);
    }

    res = lockf(fd,F_LOCK,0);
    res = write(fd,&result,sizeof(int)*3);
    res = lockf(fd,F_ULOCK,0);
    close(fd);

    return 0;
}
