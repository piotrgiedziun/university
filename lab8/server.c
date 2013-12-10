#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define MAX_CLIENTS 10
#define MESSAGE_LENGTH 512

int clients_count = 0;
int clients[MAX_CLIENTS];
pthread_t threads[MAX_CLIENTS];
 
void *client_thread(void *s_struct) {
    int read_size, i, s = *(int*)s_struct;
    char *message , client_message[MESSAGE_LENGTH];
     
    while( (read_size = recv(s , client_message , MESSAGE_LENGTH , 0)) > 0 ) {
        printf("got new message from %d %d\n", s, read_size);
        for(i=0; i<clients_count; i++) {
            if(s==clients[i])
                continue;
            write(clients[i], client_message, strlen(client_message));
        }
        memset(client_message, 0, MESSAGE_LENGTH);
    }

    return 0;
}

int main(int argc , char *argv[]) {
    int port, res, s, client_s, len;
    struct sockaddr_in server, client;
    
    // read args
    port = 8080;
    if ( argc > 2 ) {
        port = atoi(argv[1]);
    }
    signal(SIGPIPE, SIG_IGN);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1) {
        perror("socket failed");
        return 1;
    }
    printf("socket created\n");
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( port );
    if( bind(s,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("bind failed");
        return 1;
    }
    printf("bind done\n");
    
    listen(s, 5);
    len = sizeof(struct sockaddr_in);

    while( (client_s = accept(s, (struct sockaddr *)&client, (socklen_t*)&len)) ) {
        // add client
        printf("new client (id:%d)\n", clients_count);
        clients[clients_count] = client_s;
        printf("id=%d\n", clients[clients_count]);
        res = pthread_create( &threads[clients_count], NULL, 
            client_thread, (void*) &clients[clients_count]);
        if( res < 0) {
            perror("could not create thread");
            return 1;
        }
        clients_count++;
        printf("thread created\n");
    }
          
    return 0;
}