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
#include <time.h>

#define SEMAPHORES
#define SEMKEYPATH "/dev/null"
#define SEMKEYID 66
#define SHARED_MEMORY_NAME "shared_memory"

#define BRAK_KASY_1 0
#define BRAK_KASY_2 1
#define MUTEX_1		2
#define MUTEX_2		3

typedef struct {
    int acc1_value;
    int acc2_value;
} shared_struct_t;

void jd_sem_up(int semid, int id) {
	struct sembuf sops;
	sops.sem_num = id;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    if (semop(semid, &sops, 1) == -1) {
	    perror("semop error");
	    exit(1);
	}
}

void jd_sem_down(int semid, int id) {
	struct sembuf sops;
	sops.sem_num = id;
    sops.sem_op = 1;
    sops.sem_flg = 0;
    if (semop(semid, &sops, 1) == -1) {
	    perror("semop error");
	    exit(1);
	}
}

void jd_sem_up2(int semid, int id1, int id2) {
	struct sembuf sops[2];
	sops[0].sem_num = id1;
	sops[1].sem_num = id2;
    sops[0].sem_op = sops[1].sem_op = -1;
    sops[0].sem_flg = sops[1].sem_flg = 0;
    if (semop(semid, &sops, 2) == -1) {
	    perror("semop error");
	    exit(1);
	}
}

void jd_sem_down2(int semid, int id1, int id2) {
	struct sembuf sops[2];
	sops[0].sem_num = id1;
	sops[1].sem_num = id2;
    sops[0].sem_op = sops[1].sem_op = 1;
    sops[0].sem_flg = sops[1].sem_flg = 0;
    if (semop(semid, &sops, 2) == -1) {
	    perror("semop error");
	    exit(1);
	}
}

void jd_sem_lidl2(int semid, int down1, int down2, int up) {
	struct sembuf sops[3];
	// down 1
	sops[0].sem_num = down1;
    sops[0].sem_op = 1;
    sops[0].sem_flg = 0;
	// down 2
	sops[1].sem_num = down2;
    sops[1].sem_op = 1;
    sops[1].sem_flg = 0;

    // up
    sops[2].sem_num = up;
    sops[2].sem_op = -1;
    sops[2].sem_flg = 0;

    if (semop(semid, &sops, 3) == -1) {
	    perror("semop error");
	    exit(1);
	}
}

void jd_sem_lidl(int semid, int down, int up) {
	struct sembuf sops[2];
	// down
	sops[0].sem_num = down;
    sops[0].sem_op = 1;
    sops[0].sem_flg = 0;

    // up
    sops[1].sem_num = up;
    sops[1].sem_op = -1;
    sops[1].sem_flg = 0;

    if (semop(semid, &sops, 2) == -1) {
	    perror("semop error");
	    exit(1);
	}
}

void jd_sem_close(int semid, int count) {
	int rc;
	rc = semctl(semid, count, IPC_RMID);
    if (rc==-1)
    {
        printf("semctl error");
        exit(1);
    }
}

int jd_sem_init(int count) {
	int i, semid, semkey, rc;
	short *sarray;

	// alloc starting values
	sarray = (short*) calloc(count, sizeof(short));

    // init semaphore
    semkey = ftok(SEMKEYPATH, SEMKEYID);
    if ( semkey == (key_t)-1 )
    {
        printf("ftok error");
        exit(1);
    }
    semid = semget( semkey, count, 0666 | IPC_CREAT);
    if ( semid == -1 )
    {
        printf("semget error");
        exit(1);
    }

    for(i=0; i<count; i++) {
    	sarray[i] = 1;
    }

    rc = semctl( semid, 1, SETALL, sarray);
    if(rc == -1)
    {
        printf("semctl error");
        exit(1);
    }

    return semid;
}
 
void wplata(int* value, int fd, int semid, int brak_kasy, int mutex, int count, int count_i ) {
	int j, i, pid, trans;
	for(j=0; j<count; j++) {
		switch(pid = fork()) {
		case -1:
			perror("fork error");
			exit(1);
		case 0:
			for(i=0; i<count_i; i++) {
				jd_sem_up(semid, mutex);
				printf("wplata %d\n", *value);
				trans = 100;
				(*value)+=trans;
				usleep(10000);
				jd_sem_down(semid, brak_kasy);
				jd_sem_down(semid, mutex);
				usleep(30000);
			}
			close(fd);
			exit(0);
		}
	}
}

void wyplata(int* value, int fd, int semid, int brak_kasy, int mutex, int count, int count_i) {
	int j, i, pid, trans;
	for(j=0; j<count; j++) {
		switch(pid = fork()) {
		case -1:
			perror("fork error");
			exit(1);
		case 0:
			for(i=0; i<count_i; i++) {
				while(1) {
					jd_sem_up(semid, mutex);
					printf("wyplata -100 %d\n", *value);
					trans = 100;
					if( *value-100 >= 0 ) {
						(*value)-=trans;
						usleep(10000);
						break;
					}else{
						jd_sem_lidl(semid, mutex, brak_kasy);
					}
				}
				jd_sem_down(semid, mutex);
				usleep(30000);
			}
			close(fd);
			exit(0);
		}
	}
}

void przelew(int* acc_form, int* acc_to, int fd, int semid, int brak_kasy_from, int brak_kasy_to, int count, int count_i) {
	int j, i, pid, trans;
	for(j=0; j<count; j++) {
		switch(pid = fork()) {
		case -1:
			perror("fork error");
			exit(1);
		case 0:
			for(i=0; i<count_i; i++) {
				while(1) {
					jd_sem_up2(semid, MUTEX_1, MUTEX_2);
					printf("przelew %d -> %d\n", *acc_form, *acc_to);
					trans = 100;
					if( *acc_form-100 >= 0 ) { 
						(*acc_form)-=trans;
						(*acc_to)+=trans;
						jd_sem_down(semid, brak_kasy_to);
						break;
					}else{
						jd_sem_lidl2(semid, MUTEX_1, MUTEX_2, brak_kasy_from);
					}
					usleep(10000);
				}
				jd_sem_down2(semid, MUTEX_1, MUTEX_2);
			}
			close(fd);
			exit(0);
		}
	}
}

int main(int argc, char* argv[]) {
	int fd, i, res, pid, status, semid;
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

	// create semaphores
	semid = jd_sem_init(4);

	// konto 1
	wplata(&(sh->acc1_value), fd, semid, BRAK_KASY_1, MUTEX_1, 2, 10);
	wyplata(&(sh->acc1_value), fd, semid, BRAK_KASY_2, MUTEX_1, 2, 10);

	// konto 2
	wplata(&(sh->acc2_value), fd, semid, BRAK_KASY_1, MUTEX_2, 2, 10);
	wyplata(&(sh->acc2_value), fd, semid, BRAK_KASY_2, MUTEX_2, 2, 10);

	// przelewy k1 <-> k2
	przelew(&(sh->acc1_value), &(sh->acc2_value), fd, semid, BRAK_KASY_1, BRAK_KASY_2, 1, 5);
	przelew(&(sh->acc2_value), &(sh->acc1_value), fd, semid, BRAK_KASY_2, BRAK_KASY_1, 1, 5);

	for(i=0; i<200; i++) {
		pid = wait(&status);
		//printf("pid = %d\nstatus = %d\n", pid, WEXITSTATUS(status));
	}

	printf("acc1: %d\nacc2: %d\n", sh->acc1_value, sh->acc2_value);

	jd_sem_close(semid, 4);

	close(fd);
	return 0;
}