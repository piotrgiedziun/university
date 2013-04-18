#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include "msg.h"

int main(int argc, char* argv[]) {
    struct mq_attr attr;
    mqd_t  mq;
    struct msg_t msg;
    
    if(argc < 2) {
        perror("invalid parms");
        exit(1);
    }
    
    attr.mq_msgsize = sizeof(msg);
    attr.mq_maxmsg = atoi(argv[1]);
    attr.mq_flags = 0;
    
    mq_unlink(MQ_NAME);
    
    mq=mq_open(MQ_NAME , O_CREAT , 0660, &attr );
    
    if( mq == -1 ) {
        perror("error creating mq");
        exit(1);
    }
    
    mq_close(mq);
}
