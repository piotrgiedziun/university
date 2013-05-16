#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include "struct.h"

int main(int argc,char *argv[]) {
	int fd, size, i;
	bufor_t *buf;
	int nr = atoi(argv[1]),
       	    kroki = atoi(argv[2]);

	fd=shm_open(BUFFER_NAME, O_RDWR , 0774);
	if(fd == -1){
		perror("open");
		exit(-1);
	}

	buf = (bufor_t *)mmap(0, sizeof(bufor_t),PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	if(buf == 0) {
		perror("map");
		exit(-1);
	}

	for(i=0;i<kroki;i++) {
		printf("producent[%d] krok %d \n",nr,i);
		sem_wait(&(buf->empty));
		sem_wait(&(buf->mutex));
		sprintf(buf->text[buf->head],"Komunikat %d",i);
		buf->count++;
		buf->head = (buf->head +1) % BSIZE;
		sem_post(&(buf->mutex));
		sem_post(&(buf->full));
		sleep(1);
	}
	return 0;
}
