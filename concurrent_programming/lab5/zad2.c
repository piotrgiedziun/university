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
#include <mqueue.h>

#include "zad2_msg.h"
    
int open_make_mq(char* filename, struct mq_attr *attr) {
    mq_unlink(filename);
    int mq = mq_open(filename, O_RDWR | O_CREAT, 0660, attr);
    
    if( mq == -1 ) {
        perror("error creating mq");
        exit(1);
    }
    
    return mq; 
}

int main(int argc, char* argv[]) {

    if(argc < 4) {
        return 1;
    }
    
    struct mq_attr attr;
    mqd_t  mq_i, mq_o;
    struct msg_t msg;
    
    pid_t pid;
    int start=atoi(argv[1])-1,
        end=atoi(argv[2]),
        process_count=atoi(argv[3]),
        tasks=end-start,
        tasks_per_process = (tasks/process_count),
        tasks_additional = tasks-(tasks_per_process*process_count),
        pierwszych = 0, i, status, ifd, ofd,
        sub_start, sub_end,
        start_time, end_time, res, msg_prio;

    attr.mq_msgsize = sizeof(msg);
    attr.mq_maxmsg = (process_count > 10) ? 10 : process_count;
    attr.mq_flags = 0;

    start_time = time(NULL);

    mq_i=open_make_mq(MQ_INPUT, &attr);
    mq_o=open_make_mq(MQ_OUTPUT, &attr);
    
    // run 
    for(i = 0; i<process_count; i++) {
        if (fork() == 0) {
            execl("./pierwsza_zad2", "pierwsza_zad2", NULL);
            perror("error");
        }
    }

    // create input
    for(i = 0; i<process_count; i++) {
        sub_start = start+(i*tasks_per_process)+1;
        sub_end = start+(i+1)*tasks_per_process;
        if(i+1==process_count) {
            sub_end += tasks_additional;
        }
        msg.pocz = sub_start;
        msg.koniec = sub_end;
        
        res = mq_send(mq_i,(char *)&msg,sizeof(msg),0);
        if (res == -1 ) {
            perror("Blad zapisu do mq");
            continue;
        }
    }

    // gather output
    for(i = 0; i<process_count; i++) {
        pid = wait(&status);
        res = mq_receive(mq_o,(char *)&msg,sizeof(msg),&msg_prio);
        
        if (res == -1 ) {
            perror("Blad odczytu z mq");
            continue;
        }else{
            pierwszych += msg.ile;
            printf("process stopped [pid=%d,ile=%d]\n", pid, msg.ile);
        }
    }

    mq_close(mq_i);
    mq_close(mq_o);

    end_time = time(NULL);

    printf("pierwszych = %d\n", pierwszych);
    printf("czas wykonywania = %d\n", end_time-start_time);

    return 0;
}

