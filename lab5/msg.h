#ifndef MSG_H
#define MSG_H 

#define TEXT_SIZE 100
#define MQ_NAME "/mq"

struct msg_t {
      int  nr_producenta;
      int type;
      char text[TEXT_SIZE];
};

#endif
