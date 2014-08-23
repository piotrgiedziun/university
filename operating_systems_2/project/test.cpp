#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t dead_mutex; 
pthread_cond_t dead; 
int licznik = 0; 
int threads_ids[3] = {1,2,3}; 
pthread_t threads[3];

void* thread_function( void* arg ) {
	int thread_id = *((int *)arg);
	sleep( thread_id*3 ); 

		pthread_mutex_lock( &dead_mutex );
			licznik = 0;
			pthread_cond_signal(&dead); 
			printf("snake #%d is dead\n", thread_id);

			while( licznik == 0 ) {
				licznik = 1;
				printf("snake #%d sleep\n", thread_id);
				pthread_cond_wait(&dead,&dead_mutex);
			}

			licznik = 0;
			printf("snake #%d up\n", thread_id);

			pthread_cond_signal(&dead); 
		pthread_mutex_unlock( &dead_mutex ); 
}

int main() {
	// init
	pthread_mutex_init(&dead_mutex,NULL); 
	pthread_cond_init(&dead,NULL);

	// start threads
	for(int i=0; i<3; i++) {
		pthread_create( &threads[i], NULL, thread_function, (void*)&threads_ids[i]);
	}

	// join
	for(int i=0; i<3; i++) {
		pthread_join( threads[i], NULL);
	}
}