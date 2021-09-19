#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "sys/wait.h"
#include "string.h"

/*
 * This solution doesn't use semaphores and mutex.
 * if you'll comment all sleep(), then in output, you may see, that we consume some number, and some lines later we
 * produce it, but it's only because printing take some time ( I/O could affect the race conditions).
 * In order to see that all is ok I recommend to use sleep also in order to simulate the situation that
 * producing and consuming takes some time.
 */
int buff[10];
int indexForBuff=0;
int check=20;
int amount=0;//counter for amount of objects

void* producer(void *arg) {
    int forCheck=check;
    while(forCheck>0) {
        if (amount==10)
            sleep(2);
        forCheck--;
        int r = rand()%100+1;
        sleep(1);
        int id=indexForBuff;
        buff[id]=r;
        indexForBuff=(id+1)%10;
        amount++;
        printf("Produced number %d in %d\n",r,id);
    }
}

void* consumer(void *arg) {
    int forCheck=check;
    while(forCheck>0) {
        if (amount==0)
            sleep(2);
        forCheck--;
        int id=(indexForBuff-1);
        if (id<0)
            id+=10;
        int o = buff[id];
        buff[id]=-1;//put -1 in order to see if we'll try to consume number that was already consumed
        indexForBuff=id;
        amount--;
        printf("Consumed number %d from %d\n",o,id);
        sleep(2);
    }
}



int main() {
    pthread_t pthread[2];
    int n=2;
    for (int i=0; i<n; i++) {
        if (i%2==0) {
            if (pthread_create(&pthread[i], NULL, producer, NULL)) {
                printf(" >>Error in creating producer thread!\n");
                pthread_exit(NULL);
                return 1;
            } else {
                printf("Thread for producer is created!\n");
                int ok=0;

            }
        } else {
            if (pthread_create(&pthread[i], NULL, consumer, NULL)) {
                printf(" >>Error in creating consumer thread!\n");
                pthread_exit(NULL);
                return 1;
            } else {
                printf("Thread for consumer is created!\n");
                int ok=0;

            }
        }


        //pthread_join(pthread[i],NULL);
    }
    pthread_exit(NULL);
    return 0;
}