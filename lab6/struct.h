#define BSIZE 10
#define LSIZE 80
#define BUFFER_NAME "bname" 

typedef struct {
	char text[BSIZE][LSIZE];
	int head, tail, count;
	sem_t empty, full, mutex;
} bufor_t;
