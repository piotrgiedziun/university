#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SEMAPHORES
#define SEMKEYPATH "/dev/null"
#define SEMKEYID 1
#define SHARED_MEMORY_NAME "shared_memory"

typedef struct {
    int value;
} shared_struct_t;

int main(int argc, char* argv[]) {
	int fd, rc, res, pid, i, j, status, semid, semkey, count=100;
	struct sembuf sops;
	short  sarray[1];
	shared_struct_t *sh;

	// remove memory segment
	shm_unlink(SHARED_MEMORY_NAME);

	// create memeory segment
	if((fd = shm_open(SHARED_MEMORY_NAME, O_RDWR|O_CREAT, 0664)) == -1) {
		perror("shm_open error");
		exit(1);
	}

	// resize memory segment
	if((res = ftruncate(fd, sizeof(shared_struct_t))) == -1) {
		perror("ftrunc error");
		exit(1);
	}

	// copy shared segment to internal memory
	sh = (shared_struct_t *) mmap(0, sizeof(shared_struct_t), PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	if(sh == NULL) {
		perror("mmap error");
		exit(1);
	}

	#ifdef SEMAPHORES
		// init semaphore
		semkey = ftok(SEMKEYPATH,SEMKEYID);
		if ( semkey == (key_t)-1 )
		{
			printf("ftok error");
			exit(1);
		}
		semid = semget( semkey, 1, 0666 | IPC_CREAT);
		if ( semid == -1 )
		{
			printf("semget error");
			exit(1);
		}

		sarray[0] = 1;
		rc = semctl( semid, 1, SETALL, sarray);
		if(rc == -1)
		{
			printf("semctl error");
			exit(1);
		}
    #endif

	for(j=0; j<2; j++) {
		switch(pid = fork()) {
		case -1:
			perror("fork error");
			exit(1);

		case 0:
			for(i=0; i<count; i++) {
				#ifdef SEMAPHORES
					sops.sem_num = 0;
					sops.sem_op = -1;
					sops.sem_flg = 0;
					if (semop(semid, &sops, 1) == -1) {
						perror("semop error");
						exit(1);
				    }
				#endif
				sh->value = 1;
				usleep(10000);
				sh->value += 1;
				printf("id=%d, value = %d\n", j, sh->value);
				#ifdef SEMAPHORES
					sops.sem_num = 0;
					sops.sem_op = 1;
					sops.sem_flg = 0;
					if (semop(semid, &sops, 1) == -1) {
						perror("semop error");
						exit(1);
				    }
				#endif
			}

			close(fd);
			exit(0);
		}
	}

	for(j=0; j<2; j++) {
		pid = wait(&status);
		printf("pid = %d\nstatus = %d\n", pid, WEXITSTATUS(status));
	}
	
	#ifdef SEMAPHORES
		rc = semctl( semid, 1, IPC_RMID );
    	if (rc==-1)
	    {
	    	printf("semctl error");
	    	exit(1);
	    }
	#endif

	close(fd);
	return 0;
}