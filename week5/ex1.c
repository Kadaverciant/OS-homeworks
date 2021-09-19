#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "sys/wait.h"
#include "string.h"

void *myThread(void *arg) {
    printf(">>Hello from MyThread!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t pthread[5];
    int n=5;
    for (int i=0; i<n; i++) {
        if (pthread_create(&pthread[i], NULL, myThread, NULL)) {
            printf(" >>Error in creating thread %d!\n",i);
            pthread_exit(NULL);
            return 1;
        } else {
            printf("Thread %d created!\n",i);
            int ok=0;

        }

        pthread_join(pthread[i],NULL);
    }
    pthread_exit(NULL);
    return 0;
}