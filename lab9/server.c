#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

#define MAX_CLIENTS 10
#define MESSAGE_LENGTH 512

int clients_count = 0;
struct sockaddr_in clients[MAX_CLIENTS];


int main(int argc , char *argv[]) {
    int i, rec, s, port, res, client_s, len;
    struct sockaddr_in server, client;
    char client_message[MESSAGE_LENGTH];
    
    // read args
    port = 8080;
    if ( argc > 2 ) {
        port = atoi(argv[1]);
    }
    signal(SIGPIPE, SIG_IGN);

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == -1) {
        perror("socket failed");
        return 1;
    }
    
    memset((char *) &server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons( port );
    if( bind(s,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("bind failed");
        return 1;
    }
    printf("bind done\n");
    
    while( 1 ) {
        rec = recvfrom(s, client_message, MESSAGE_LENGTH, 0, (struct sockaddr*)&client, (socklen_t *) &len);
        if(rec < 0) printf("recvfrom()");
        // add client
        if ( strcmp(client_message, "init") == 0) {
            //printf("new client (id:%d,port:%d)\n", clients_count, client.sin_port);
            clients[clients_count] = client;
            clients_count++;
        }else{
            //printf("client_thread - %s\n", client_message);
            for(i=0; i<clients_count; i++) {
                printf("%d", clients[i].sin_port);
                if( sendto(s, client_message, MESSAGE_LENGTH, 0, &clients[i], len) < 0) {
                    printf("error send\n");
                }
            }
        }
    }
          
    return 0;
}