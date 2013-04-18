#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include "msg.h"

int main(int argc, char* argv[]) {
    struct mq_attr attr;
    mqd_t  mq;
    struct msg_t msg;
    
    int i, res, 
        producent_id = atoi(argv[1]),
        msg_counter = atoi(argv[2]);
        
    if(argc < 2) {
        perror("invalid parms");
        exit(1);
    }
        
    mq=mq_open(MQ_NAME, O_RDWR);
    
    if( mq == -1 ) {
        perror("error open mq");
        exit(1);
    }
    
    printf("Kolejka otwarta, mq: %d\n", mq);
    
    for(i=0; i < msg_counter; i++) {
        mq_getattr(mq,&attr);   
        
        printf("> W kolejce %ld komunikatow\n",attr.mq_curmsgs);
        
        sprintf(msg.text,"producent #%d komunikat #%d", producent_id, i+1);
        msg.type = producent_id;
        res = mq_send(mq,(char *)&msg,sizeof(msg),0);
        
        if (res == -1 ) {
            perror("Blad zapisu do mq");
            continue;
        }
        
        printf("> producent #%d wiadomość #%d wysłana\n",producent_id, i+1);
        sleep(1);
    }
    
    mq_close(mq);
}
