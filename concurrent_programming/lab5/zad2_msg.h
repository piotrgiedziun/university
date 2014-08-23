#ifndef MSG_H
#define MSG_H 

#define MQ_INPUT "/mq_input"
#define MQ_OUTPUT "/mq_output"

struct msg_t {
    int pocz;
    int koniec;
    int ile;
};

#endif