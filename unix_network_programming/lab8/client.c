#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/types.h>
#include <signal.h>

#define MESSAGE_LENGTH 512

int main(int argc , char *argv[]) {
    int s, port;
    fd_set readfds;
    struct sockaddr_in server;
    char user[50], ip[50], message[MESSAGE_LENGTH], server_message[MESSAGE_LENGTH];

    // read args
    strcpy(ip, "127.0.0.1");
    strcpy(user, "user");
    port = 8080;
    if ( argc > 4 ) {
        strcpy(ip, argv[1]);
        port = atoi(argv[2]);
        strcpy(user, argv[3]);
    } else if ( argc > 3 ) {
        strcpy(ip, argv[1]);
        port = atoi(argv[2]);
    } else if ( argc > 2 ) {
        strcpy(ip, argv[1]);
    }

    s = socket(AF_INET , SOCK_STREAM , 0);
    if (s == -1) {
        perror("socket failed");
        return 1;
    }
     
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("connect failed");
        return 1;
    }

    printf("connected to %s:%d\n", ip, port);
    while(1) {
        // select
        FD_ZERO(&readfds);
        FD_SET(s, &readfds);
        FD_SET(0, &readfds);
        int rc = select(s+1, &readfds, NULL, NULL, NULL);

        if(rc == 0)
            break;

        if(rc == -1)
            break;

        if(FD_ISSET(0, &readfds)) {
            if( fgets(message, MESSAGE_LENGTH , stdin) != NULL ) {
                if( send(s, message, strlen(message), 0) < 0) {
                    perror("send failed");
                    return 1;
                }
                bzero(message, MESSAGE_LENGTH);
            }
        }

        if(FD_ISSET(s, &readfds)) {
            if( recv(s, server_message, MESSAGE_LENGTH, 0) < 0) {
                perror("recv failed");
                return 1;
            }
            printf("%s", server_message);
            bzero(server_message, MESSAGE_LENGTH);
        }
         
    }
     
    close(s);
    return 0;
}