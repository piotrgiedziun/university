#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_SIZE 50
#define BUFFER_NAME "bname" 

typedef struct result_t {
    int pocz;
    int koniec;
    int ile;
} result_t;

typedef struct {
    int size;
    result_t results[MAX_SIZE];
} buf_t;

int pierwsza(int n) {
    int i;
    if(n==1) return 0;
    for(i=2;i*i<=n;i++) {
        if(n%i == 0) return 0;
    }
    return 1;
}

int main(int argc,char *argv[]) {
 int i,stat,pid,k,res;
 buf_t  *buf;
 int  fd;
 int start=atoi(argv[1])-1,
        end=atoi(argv[2]),
        process_count=atoi(argv[3]),
        tasks=end-start,
        tasks_per_process = (tasks/process_count),
        tasks_additional = tasks-(tasks_per_process*process_count),
	poczatek, koniec, pierwszych=0, status;

 if ( process_count >  MAX_SIZE ) {
    perror("You can't do that..");
    exit(-1);
 }

 shm_unlink(BUFFER_NAME);   

 // Utworzenie segmentu pamieci  --------------------- 
 if((fd=shm_open(BUFFER_NAME,O_RDWR|O_CREAT,0664))==-1) {
    perror("shm_open");
    exit(-1);
 }

 // Okreslenie rozmiaru obszaru pamieci ---------------    
 res = ftruncate(fd,sizeof(buf_t));
 if(res < 0) { perror("ftrunc"); return 0; }

 // Odwzorowanie segmentu fd w obszar pamieci procesow 
 buf = (buf_t *) mmap(0,sizeof(buf_t), PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
 if(buf == NULL) { perror("mmap"); exit(-1); }

for(i = 0; i<process_count; i++) {
    int j;
    poczatek = start+(i*tasks_per_process)+1;
    koniec = start+(i+1)*tasks_per_process;
    if(i+1==process_count) {
        koniec += tasks_additional;
    }
    if(fork() == 0) {
        buf->results[i].pocz = poczatek;
        buf->results[i].koniec = koniec;
        buf->results[i].ile=0;
        for(j = poczatek; j<koniec; j++) {
            if(pierwsza(j)==1) {
                buf->results[i].ile++;
            }
        }
        exit(0);
    }
}

// gather output
for(i = 0; i<process_count; i++) {
    pid = wait(&status);
}

// count output
for(i = 0; i<process_count; i++) {
    pierwszych += buf->results[i].ile;
}

printf("pierwszych = %d\n", pierwszych);

return 0;
}
