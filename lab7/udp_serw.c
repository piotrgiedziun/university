#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

#include "static.h"

void blad(char *s) {
    perror(s);
    _exit(1);
}

int main(void) {
   struct sockaddr_in adr_moj, adr_cli;
   int s, i, slen=sizeof(adr_cli),snd, rec, blen=sizeof(msgt);
   char buf[BUFLEN];
   msgt msg;
   DIR *dp;
   struct dirent *ep; 

   gethostname(buf,sizeof(buf));
   printf("Host: %s\n",buf);

   s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if(s < 0) blad("socket");

   // Ustalenie adresu IP nadawcy
   memset((char *) &adr_moj, 0, sizeof(adr_moj));
   adr_moj.sin_family = AF_INET;
   adr_moj.sin_port = htons(PORT);
   adr_moj.sin_addr.s_addr = htonl(INADDR_ANY);
   if (bind(s,(struct sockaddr *) &adr_moj, sizeof(adr_moj))==-1)
       blad("bind");

   // Odbior komunikatow ------------
   while(1) {
      rec = recvfrom(s, &msg, blen, 0,(struct sockaddr *) &adr_cli, &slen);
      if(rec < 0) blad("recvfrom()");
      printf("Odebrano komunikat z %s:%d res %d\n  Typ: %d\n",
            inet_ntoa(adr_cli.sin_addr), ntohs(adr_cli.sin_port), rec,msg.typ);
      switch(msg.typ) {
        case OPENR:
            printf("OPENR %s\n", msg.buf);
            msg.fd = open(msg.buf, O_RDONLY);
        break;
        
        case OPENW:
            printf("OPENW %s\n", msg.buf);
            remove( msg.buf );
            msg.fd = open(msg.buf, O_WRONLY | O_CREAT, 0666);
        break;
        
        case WRITE:
            printf("WRITE %d\n", msg.fd);
            msg.ile = write(msg.fd, msg.buf, msg.ile);
        break;
        
        case READ:
            printf("READ %d\n", msg.fd);
            memset(msg.buf, 0, sizeof(msg.buf));
            msg.ile = read(msg.fd, msg.buf,BUFLEN);
        break;
        
        case CLOSE:
            printf("CLOSE %d\n", msg.fd);
            close(msg.fd);
        break;
        
        case OPEN_DIR:
            printf("OPENDIR %s\n", msg.buf);
            dp = opendir (msg.buf);
        break;
        
        case READ_DIR:
            printf("READ_DIR %d\n", msg.fd);
            ep = readdir(dp);
            if( ep ) {
                memset(msg.buf, 0, sizeof(msg.buf));
                strcpy(msg.buf, ep->d_name);
            }
            msg.ile = ep ? 1 : 0;
        break;
        
        case CLOSE_DIR:
            printf("CLOSE_DIR %d\n", msg.fd);
            closedir (dp);
        break;
      }
      snd = sendto(s, &msg, blen, 0,(struct sockaddr *) &adr_cli, slen);
      if(snd < 0) blad("sendto()");
      printf("wyslano odpowiedz -res %d\n",snd);
   }
   close(s);
   return 0;
}


