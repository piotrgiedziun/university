/*
 * instructions:
 * ls [path]
 * write [input] [output]
 * cat [file]
 */
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "static.h"

struct sockaddr_in adr_moj, adr_serw, adr_x;
int s, i, slen=sizeof(adr_serw), snd, blen=sizeof(msgt),rec;

void blad(char *s) {
     perror(s);
     _exit(1);
}

void ftp_openr(msgt* msg, char* file) {
   msg->typ = OPENR;
   strcpy(msg->buf, file);
   snd = sendto(s, msg, blen, 0,(struct sockaddr *) &adr_serw,(socklen_t) slen);
   if(snd < 0) blad("sendto()");
   rec = recvfrom(s, msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
   if(rec < 0) blad("recvfrom()");
}

void ftp_open_dir(msgt* msg, char* dir) {
   msg->typ = OPEN_DIR;
   strcpy(msg->buf, dir);
   snd = sendto(s, msg, blen, 0,(struct sockaddr *) &adr_serw,(socklen_t) slen);
   if(snd < 0) blad("sendto()");
   rec = recvfrom(s, msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
   if(rec < 0) blad("recvfrom()");
}

void ftp_openw(msgt* msg, int* fd, char* file_in, char* file_out) {
   msg->typ = OPENW;
   memcpy(msg->buf, file_out, sizeof(file_out));
   *fd = open(file_in, O_RDONLY);
   snd = sendto(s, msg, blen, 0,(struct sockaddr *) &adr_serw,(socklen_t) slen);
   if(snd < 0) blad("sendto()");
   rec = recvfrom(s, msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
   if(rec < 0) blad("recvfrom()");
}

void ftp_write(msgt* msg, int *fd) {
   int size;
   do {
       msg->ile = read(*fd,msg->buf,BUFLEN);
       msg->typ = WRITE;
       snd = sendto(s, msg, blen, 0,(struct sockaddr *) &adr_serw,(socklen_t) slen);
       if(snd < 0) blad("sendto()");
       rec = recvfrom(s, msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
       if(rec < 0) blad("recvfrom()");
    } while(msg->ile == BUFLEN);
}

void ftp_read(msgt* msg) {
   printf("\n====FILE CONTENT====\n");
   do {
       msg->typ = READ;
       snd = sendto(s, msg, blen, 0,(struct sockaddr *) &adr_serw,(socklen_t) slen);
       if(snd < 0) blad("sendto()");
       rec = recvfrom(s, msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
       if(rec < 0) blad("recvfrom()");
       // display file
       printf("%s", msg->buf);
   } while( msg->ile == BUFLEN );
   printf("\n====END OF FILE CONTENT====\n");
}

void ftp_read_dir(msgt* msg) {
   printf("\n====DIR LIST====\n");
   do {
       msg->typ = READ_DIR;
       snd = sendto(s, msg, blen, 0,(struct sockaddr *) &adr_serw,(socklen_t) slen);
       if(snd < 0) blad("sendto()");
       rec = recvfrom(s, msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
       if(rec < 0) blad("recvfrom()");
       printf("%s\n", msg->buf);
   } while( msg->ile == 1 );
   printf("\n====END OF DIR LIST====\n");
}

void ftp_closew(msgt* msg, int* fd) {
   close(*fd);
   msg->typ = CLOSE;
   snd = sendto(s, msg, blen, 0,(struct sockaddr *) &adr_serw,(socklen_t) slen);
   if(snd < 0) blad("sendto()");
   rec = recvfrom(s, msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
   if(rec < 0) blad("recvfrom()");
}

void ftp_closer(msgt* msg) {
   msg->typ = CLOSE;
   snd = sendto(s, msg, blen, 0,(struct sockaddr *) &adr_serw,(socklen_t) slen);
   if(snd < 0) blad("sendto()");
   rec = recvfrom(s, msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
   if(rec < 0) blad("recvfrom()");
}

void ftp_close_dir(msgt* msg) {
   msg->typ = CLOSE_DIR;
   snd = sendto(s, msg, blen, 0,(struct sockaddr *) &adr_serw,(socklen_t) slen);
   if(snd < 0) blad("sendto()");
   rec = recvfrom(s, msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
   if(rec < 0) blad("recvfrom()");
}

int main(int argc, char * argv[]) {
   char command[50],
        parm1[50],
        parm2[50];
   msgt open_msg, 
        write_msg, 
        dir_msg;
  
   s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if(s < 0) blad("socket");
   printf("Gniazdko %d utworzone\n",s);
   memset((char *) &adr_serw, 0, sizeof(adr_serw));
   adr_serw.sin_family = AF_INET;
   adr_serw.sin_port = htons(PORT);
   
   if (inet_aton(argv[1], &adr_serw.sin_addr)==0) {
        fprintf(stderr, "inet_aton() failed\n");
        _exit(1);
   }

   // shell
   do {
    printf("> ");
    scanf("%s", command);
    if( strcmp(command, "read") == 0 || strcmp(command, "cat") == 0 ) {
        scanf("%s", parm1);
        ftp_openr(&open_msg, parm1);
        ftp_read(&open_msg);
        ftp_closer(&open_msg);
    } else if ( strcmp(command, "write") == 0 ) {
        scanf("%s", parm1);
        scanf("%s", parm2);
        int write_fd = 0;
        ftp_openw(&write_msg, &write_fd, parm1, parm2);
        ftp_write(&write_msg, &write_fd);
        ftp_closew(&write_msg, &write_fd);
        printf("file %s send to server as %s\n", parm1, parm2);
    } else if ( strcmp(command, "dir") == 0 || strcmp(command, "ls") == 0 ) {
        scanf("%s", parm1);
        ftp_open_dir(&dir_msg, parm1);
        ftp_read_dir(&dir_msg);
        ftp_close_dir(&dir_msg);
    } else {
        printf("invalid parm\n");
    }
    
   } while( strcmp(command, "close") != 0 );
   printf("bye\n");
   
   close(s);
   return 0;
}


