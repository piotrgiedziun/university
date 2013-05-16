#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include "struct.h"

int main(int argc,char *argv[]) {
	int fd, size;
	bufor_t *buf;

	// Utworzenie segmentu ---------------------------
	shm_unlink(BUFFER_NAME);
	fd=shm_open(BUFFER_NAME, O_RDWR|O_CREAT , 0774);
	if(fd == -1){
		perror("open");
		exit(-1);
	}

	size = ftruncate(fd,sizeof(bufor_t));
	if(size < 0) {
		perror("trunc");
		exit(-1);
	}

	// Odwzorowanie segmentu fd w obszar pamieci procesow
	buf = (bufor_t *)mmap(0, sizeof(bufor_t),PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	if(buf == 0) {
		perror("map");
		exit(-1);
	}

	// Inicjacja obszaru --------------------------------
	buf->count = 0;
	buf->head = 0;
	buf->tail = 0;

	if(sem_init(&(buf->mutex),1,1)){
		perror("mutex");
		exit(-1);
	}
	if(sem_init(&(buf->empty),1,BSIZE)) {
		perror("empty");
		exit(-1);
	}
	if(sem_init(&(buf->full),1,0)) {
		perror("full");
		exit(-1);
	}
	return 0;
}

