#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREADS_COUNT 20
#define RACE 0

int global_value = 0;
pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;

void *race( void *ptr ) {
	if(!RACE) {
    	pthread_mutex_lock( &global_mutex );
	}
    
    int *id = (int *) ptr;

    global_value = *id;
    usleep(1);

    printf("%d=%d\n", *id, global_value);

    if(!RACE) {
    	pthread_mutex_unlock( &global_mutex );
    }
}

int main() {
    pthread_t thread[THREADS_COUNT];
    int ids[THREADS_COUNT];
    int thread_value[THREADS_COUNT];
    int i=0;

    printf("program iterujacy 0,0,0,0...\n");

    int value = 0;

    for(i=0; i<THREADS_COUNT; i++) {
    	ids[i] = i+1;
    }

    for(i=0; i<THREADS_COUNT; i++) {
    	thread_value[i] = pthread_create( &thread[i], NULL, race, (void*) &ids[i]);
    }

    for(i=0; i<THREADS_COUNT; i++) {
    	pthread_join( thread[i], NULL);
    }

    for(i=0; i<THREADS_COUNT; i++) {
    	//printf("Thread %d returns: %d\n", i, thread_value[i]);
    }

    return 0;
}