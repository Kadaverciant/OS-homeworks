#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "sys/wait.h"
#include "string.h"
#include "semaphore.h"

pthread_mutex_t mutex;
sem_t semEmpty;
sem_t semFull;
int buff[10];//buffer of objects
int indexForBuff=0;
int check=20;//number of objects that we'll produce & consume

/*
 * if you'll comment all sleep(), then in output, you may see, that we consume some number, and some lines later we
 * produce it, but it's only because printing takes some time ( I/O could affect the race conditions).
 * In order to see that all is ok I recommend using sleep also in order to simulate the situation that
 * producing and consuming takes some time.
 */
void* producer(void *arg) {
    int forCheck=check;
    while(forCheck) {
        forCheck--;
        int r = rand()%100+1;//generate some positive number
        sleep(1);

        sem_wait(&semEmpty);//semaphore that wait until buffer is full
        pthread_mutex_lock(&mutex);//close access to id until we haven't finished the operations with buffer and index
        int id=indexForBuff;
        buff[id]=r;
        indexForBuff=(id+1);
        pthread_mutex_unlock(&mutex);//open access to sheared objects
        sem_post(&semFull);

        printf("Produced number %d in %d\n",r,id);

    }
}

void* consumer(void *arg) {
    int forCheck=check;
    while(forCheck) {
        forCheck--;

        sem_wait(&semFull);//semaphore that wait until buffer is empty
        pthread_mutex_lock(&mutex);//close access to sheared objects
        int id=(indexForBuff-1);
        if (id<0)
            id+=10;
        int o = buff[id];
        buff[id]=-1;//put -1 in order to see if we'll try to consume number that was already consumed
        indexForBuff=id;
        pthread_mutex_unlock(&mutex);//open access to sheared objects
        sem_post(&semEmpty);

        printf("Consumed number %d from %d\n",o,id);
        sleep(2);
    }
}



int main() {
    pthread_mutex_init(&mutex,NULL);
    sem_init(&semEmpty,0,10);
    sem_init(&semFull,0,0);
    srand(time(NULL));

    pthread_t pthread[2];
    pthread_create(&pthread[0], NULL, producer, NULL);
    pthread_create(&pthread[1], NULL, consumer, NULL);

    pthread_join(pthread[0],NULL);
    pthread_join(pthread[1],NULL);

    sem_destroy(&semFull);
    sem_destroy(&semEmpty);

    pthread_mutex_destroy(&mutex);

    pthread_exit(NULL);
}