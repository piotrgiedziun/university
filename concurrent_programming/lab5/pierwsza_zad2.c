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
#include <mqueue.h>

#include "zad2_msg.h"

int open_mq(char* filename) {
    int mq = mq_open(filename, O_RDWR);
    
    if( mq == -1 ) {
        perror("error creating mq");
        exit(1);
    }
    
    return mq; 
}

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
    int i, pierwszych=0, msg_prio, res;
    struct mq_attr attr;
    mqd_t  mq_i, mq_o;
    struct msg_t msg;
    
    mq_i = open_mq(MQ_INPUT);
    
    res = mq_receive(mq_i,(char *)&msg,sizeof(msg),&msg_prio);
    if (res == -1 ) {
        perror("Blad odczytu z mq");
        exit(0);
    }
        
    mq_close(mq_i);
     
    for(i = msg.pocz; i<msg.koniec; i++) {
        if(pierwsza(i)==1)
            pierwszych++;
    }

    // set data
    msg.ile = pierwszych;

    mq_o = open_mq(MQ_OUTPUT);

    res = mq_send(mq_o,(char *)&msg,sizeof(msg),0);
    if (res == -1 ) {
        perror("Blad zapisu do mq");
        exit(0);
    }
    
    mq_close(mq_o);

    return 0;
}


