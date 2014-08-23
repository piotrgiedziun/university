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
        pierwszych = 0, i, status, fd,
        sub_start, sub_end, buf_count, pierwszych_it,
        start_time, end_time;


    start_time = time(NULL);

    remove("results.txt");

    for(i = 0; i<process_count; i++) {
        if (fork() == 0) {
            sub_start = start+(i*tasks_per_process)+1;
            sub_end = start+(i+1)*tasks_per_process;
            if(i+1==process_count) {
                sub_end += tasks_additional;
            }
            sprintf(startbuff, "%d", sub_start);
            sprintf(endbuff, "%d", sub_end);
            execl("./pierwsza_zad2", "pierwsza_zad2", startbuff, endbuff, NULL);
            perror("error");
        }
    }

    for(i = 0; i<process_count; i++) {
        pid = wait(&status);
        printf("process stopped [pid=%d]\n", pid);
    }

    // read file
    fd = open("results.txt",O_RDONLY);
    if(fd < 0 ) {
            perror("file1 open error");
            exit(0);
    }
    do {
            buf_count = read(fd,buf,SIZE);
            if(buf_count==0) continue;
            memcpy(&pierwszych_it,buf+8,sizeof(int));
            pierwszych += pierwszych_it;
    } while(buf_count == SIZE);

    close(fd);

    end_time = time(NULL);

    printf("pierwszych = %d\n", pierwszych);
    printf("czas wykonywania = %d\n", end_time-start_time);

    return 0;
}
