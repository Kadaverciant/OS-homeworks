#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "sys/wait.h"
#include "string.h"

/*
 * This solution doesn't use semaphores and mutex.
 * if you'll comment all sleep(), then in output, you may see, that we consume some number, and some lines later we
 * produce it, but it's only because printing takes some time ( I/O could affect the race conditions).
 * In order to see that all is ok I recommend using sleep also in order to simulate the situation that
 * producing and consuming takes some time.
 */
int buff[10];//buffer of objects
int indexForBuff=0;
int check=20;//number of objects that we'll produce & consume
int amount=0;//counter for amount of objects

void* producer(void *arg) {
    int forCheck=check;
    while(forCheck>0) {
        if (amount==10)
            sleep(4);
        forCheck--;
        int r = rand()%100+1;
        sleep(1);
        int id=indexForBuff;
        buff[id]=r;
        indexForBuff=(id+1)%10;
        amount++;
        printf("Produced number %d in buffer %d\n",r,id);
    }
}

void* consumer(void *arg) {
    int forCheck=check;
    while(forCheck>0) {
        if (amount==0)
            sleep(4);
        forCheck--;
        int id=(indexForBuff-1);
        if (id<0)
            id+=10;
        int o = buff[id];
        buff[id]=-1;//put -1 in order to see if we'll try to consume number that was already consumed
        indexForBuff=id;
        amount--;
        printf("Consumed number %d from buffer %d\n",o,id);
        sleep(1);
    }
}



int main() {
    srand(time(NULL));
    pthread_t pthread[2];

    pthread_create(&pthread[0], NULL, producer, NULL);
    pthread_create(&pthread[1], NULL, consumer, NULL);

    pthread_join(pthread[0],NULL);
    pthread_join(pthread[1],NULL);

    pthread_exit(NULL);
}