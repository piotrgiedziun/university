/**
* Obliczanie ilosci liczb pierwszych w danym zakresie na danej liczbie procesow.
* Aplikacja pierwsza_zad2 zapisuje wynik dzialania do pliku.
*
* usage:
* ./zad2 [zakres_start] [zakres_end] [ilosc_procesow]
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SIZE 4*3

struct result_struct {
    int pocz;
    int koniec;
    int ile;
} result;

void make_fifo(char* filename) {
    remove(filename);
    
    int res = mkfifo(filename, 0666);
    
    if (res < 0 ) {
        perror("mkfifo create error");
        exit(1);
    }
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

    if(argc < 4) {
        return 1;
    }
    char startbuff[50], endbuff[50], buf[SIZE];
    pid_t pid;
    int start=atoi(argv[1])-1,
        end=atoi(argv[2]),
        process_count=atoi(argv[3]),
        tasks=end-start,
        tasks_per_process = (tasks/process_count),
        tasks_additional = tasks-(tasks_per_process*process_count),
        pierwszych = 0, i, status, ifd, ofd,
        sub_start, sub_end, buf_count, pierwszych_it,
        start_time, end_time, res;


    start_time = time(NULL);

    make_fifo("i_fifoYOLO");
    make_fifo("o_fifoYOLO");
    
    ifd = open_fifo("i_fifoYOLO");
    ofd = open_fifo("o_fifoYOLO");

    // create input fifo
    for(i = 0; i<process_count; i++) {
        sub_start = start+(i*tasks_per_process)+1;
        sub_end = start+(i+1)*tasks_per_process;
        if(i+1==process_count) {
            sub_end += tasks_additional;
        }
        result.pocz = sub_start;
        result.koniec = sub_end;
        write(ifd,&result,sizeof(result));
    }

    // run 
    for(i = 0; i<process_count; i++) {
        if (fork() == 0) {
            execl("./pierwsza_zad2", "pierwsza_zad2", NULL);
            perror("error");
        }
    }

    for(i = 0; i<process_count; i++) {
        pid = wait(&status);
        buf_count = read(ofd,&result,sizeof(result));
        pierwszych += result.ile;
        printf("process stopped [pid=%d,ile=%d]\n", pid, result.ile);
    }

    close(ifd);
    close(ofd);

    end_time = time(NULL);

    printf("pierwszych = %d\n", pierwszych);
    printf("czas wykonywania = %d\n", end_time-start_time);

    return 0;
}

