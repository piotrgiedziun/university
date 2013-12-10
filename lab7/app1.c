#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define THREADS_COUNT 30
#define RACE 0
#define EOK 0

pthread_mutex_t mutex_trans = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond_trans = PTHREAD_COND_INITIALIZER;

typedef struct {
  pthread_mutex_t* mutex;
  pthread_cond_t* count;
  int* account_trans;
  int* account_value;
  int account_id;
} args_struct;

typedef struct {
  pthread_mutex_t* mutex_to;
  pthread_mutex_t* mutex_from;
  pthread_cond_t* count_to;
  pthread_cond_t* count_from;
  int* account_to_trans;
  int* account_from_trans;
  int* account_to_value;
  int* account_from_value;
  int account_to_id;
  int account_from_id;
} args_extended_struct;

void *wplata( void *ptr ) {
    args_struct *data = (args_struct *) ptr;

    // decyzyjny
    if(!RACE) {
        pthread_mutex_lock( &mutex_trans );

        while( *(data->account_trans) == 1 ) {
            pthread_cond_wait(&cond_trans, &mutex_trans);
        }
        *(data->account_trans) = 1;

        pthread_mutex_unlock( &mutex_trans );
    }

    pthread_mutex_lock( data->mutex );

    printf("acc%d\t\t+\t%d\t%d\n", data->account_id, *(data->account_value),*(data->account_value)+100);
    *(data->account_value) += 100;
    pthread_cond_signal( data->count );

    if(!RACE) {
        pthread_mutex_unlock( data->mutex );
        
        pthread_mutex_lock( &mutex_trans );
        *(data->account_trans) = 0;
        pthread_mutex_unlock( &mutex_trans );

        pthread_cond_signal(&cond_trans);
    }
}

void *wyplata( void *ptr ) {
    args_struct *data = (args_struct *) ptr;

    if(!RACE) {
        pthread_mutex_lock( &mutex_trans );

        while( *(data->account_trans) == 1 ) {        
            pthread_cond_wait(&cond_trans, &mutex_trans);
        }
        *(data->account_trans) = 1;

        pthread_mutex_unlock( &mutex_trans );
    }

    pthread_mutex_lock( data->mutex );

    while(1) {

        if( *(data->account_value) >= 100) {
            printf("acc%d\t\t-\t%d\t%d\n", data->account_id, *(data->account_value), *(data->account_value)-100);
            *(data->account_value) -= 100;
            break;
        } else {
            // brak kasy
            pthread_mutex_lock( &mutex_trans );
            *(data->account_trans) = 0;
            pthread_mutex_unlock( &mutex_trans );
            
            pthread_cond_signal(&cond_trans);

            pthread_cond_wait(data->count, data->mutex);
        }

    }

    if(!RACE) {
        pthread_mutex_unlock( data->mutex );
        
        pthread_mutex_lock( &mutex_trans );
        *(data->account_trans) = 0;
        pthread_mutex_unlock( &mutex_trans );
        
        pthread_cond_signal(&cond_trans);
    }
}

void *przelew( void *ptr ) {
    args_extended_struct *data = (args_extended_struct *) ptr;

    if(!RACE) {
        pthread_mutex_lock( &mutex_trans );

        while( *(data->account_from_trans) == 1 || *(data->account_to_trans) == 1 ) {
            if( *(data->account_from_trans) == 0 ) {
                pthread_cond_wait(&cond_trans, &mutex_trans);
            }else if( *(data->account_to_trans) == 0 ) {
                pthread_cond_wait(&cond_trans, &mutex_trans);
            }else{
                // czekaj na koncie to
                pthread_cond_wait(&cond_trans, &mutex_trans);
            }
        }

        *(data->account_from_trans) = 1;
        *(data->account_to_trans) = 1;

        pthread_mutex_unlock( &mutex_trans );
    }

    pthread_mutex_lock( data->mutex_to );
    pthread_mutex_lock( data->mutex_from );

    while(1) {
        if( *(data->account_from_value) >= 100) {
            printf("acc%d->acc%d\t%d %d\n", data->account_from_id, data->account_to_id, *(data->account_from_value), *(data->account_to_value));
            *(data->account_from_value) -= 100;
            *(data->account_to_value) += 100;
            pthread_cond_signal( data->count_to );
            break;
        } else {
            pthread_mutex_lock( &mutex_trans );
            *(data->account_from_trans) = 0;
            *(data->account_to_trans) = 0;
            pthread_mutex_unlock( &mutex_trans );
            //printf("brak kasy 2\n");

            pthread_mutex_unlock( data->mutex_from );
            pthread_mutex_unlock( data->mutex_to );

            pthread_cond_broadcast(data->count_to);
            pthread_cond_broadcast(data->count_from);

            pthread_cond_wait(data->count_from, NULL);
        }
    }

    pthread_mutex_unlock( data->mutex_from );
    pthread_mutex_unlock( data->mutex_to );

    if(!RACE) {
        pthread_mutex_lock( &mutex_trans );
        *(data->account_from_trans) = 0;
        *(data->account_to_trans) = 0;
        pthread_mutex_unlock( &mutex_trans );
        pthread_cond_signal(&cond_trans);
        pthread_cond_signal(&cond_trans);
    }
}

int main() {
    int acc1 = 440;
    int acc2 = 440;
    int acc1trans = 0;
    int acc2trans = 0;
    pthread_mutex_t mutex_acc1 = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutex_acc2 = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t  cond_acc1 = PTHREAD_COND_INITIALIZER;
    pthread_cond_t  cond_acc2 = PTHREAD_COND_INITIALIZER;

    // inicjalizacja zmiennej warunkowej
    pthread_cond_init(&cond_acc1, NULL);
    pthread_cond_init(&cond_acc2, NULL);
    pthread_cond_init(&cond_trans, NULL);

    pthread_t thread[THREADS_COUNT];

    args_struct args[2] = { 
        { &mutex_acc2, &cond_acc2, &acc2trans, &acc2, 2 }, 
        { &mutex_acc1, &cond_acc1, &acc1trans, &acc1, 1 }
    };

    args_extended_struct argse[2] = {
        { &mutex_acc1, &mutex_acc2, &cond_acc1, &cond_acc2, &acc1trans, &acc2trans, &acc1, &acc2, 1, 2 }, 
        { &mutex_acc2, &mutex_acc1, &cond_acc2, &cond_acc1, &acc2trans, &acc1trans, &acc2, &acc1, 2, 1 }
    };

    int i;

    for(i=0; i<=50;) {
        // wplata
        pthread_create( &thread[i++], NULL, wplata, (void*) &args[1]);
        pthread_create( &thread[i++], NULL, wplata, (void*) &args[0]);
    }

    for(i=0; i<=4;) {
        // wyplata
        pthread_create( &thread[i++], NULL, wyplata, (void*) &args[1]);
        pthread_create( &thread[i++], NULL, wyplata, (void*) &args[0]);
    }

    for(i=0; i<=5;) {
        // przelewy
        pthread_create( &thread[i++], NULL, przelew, (void*) &argse[1]);
        pthread_create( &thread[i++], NULL, przelew, (void*) &argse[0]);
    }

    for(i=0; i<4+50; i++) {
        pthread_join( thread[i], NULL);
    }

    printf("acc1=%d, acc2=%d\n", acc1, acc2);

    return 0;
}