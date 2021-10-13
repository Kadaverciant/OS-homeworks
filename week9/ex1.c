#include <stdio.h>

#define NUMBER_BITS 16

struct Page {
    int id;
    int counter;
};


int main() {
    int n=0;
    printf("Enter the number of page frames: \n");
    scanf("%d",&n);
    int hits=0;
    int miss=0;
    double ratio;
    struct Page pages[n];

    for (int i=0; i<n; i++) {
        pages[i].id=0;
        pages[i].counter=0;
    }

    FILE *fptr= fopen("input.txt","r");
    int k;
    int count=0;
    while (fscanf(fptr, "%d", &k) != EOF) {
        count++;
    }
    fclose(fptr);

    int requests[count];

    fptr = fopen("input.txt","r");
    int i=0;
    while (fscanf(fptr, "%d", requests+i) != EOF) {
        i++;
    }
    fclose(fptr);

    for (int i=0; i<count; i++) {
        int missed=1;
        for (int j=0; j<n; j++) {
            if(requests[i]==pages[j].id) {
                missed=0;
                pages[j].counter>>=1;
                pages[j].counter |= 1 << (NUMBER_BITS-1);
            } else {
                pages[j].counter>>=1;
            }
        }
        if (missed==1) {
            int min=65536;
            int minID=0;
            for (int j=0; j<n; j++) {
                if (pages[j].counter<min) {
                    min=pages[j].counter;
                    minID=j;
                }
            }
            pages[minID].id=requests[i];
            pages[minID].counter=0;
            pages[minID].counter |= 1 << (NUMBER_BITS-1);
            miss++;
        } else {
            hits++;
        }
        printf("current page number %d\n", requests[i]);
        for (int j=0; j<n; j++) {
            printf("i =% d id = %d counter = %d\n",j+1,pages[j].id,pages[j].counter);
        }
    }
    ratio=(double )hits/(double )miss;
    printf("Hits = %d Misses = %d Ration = %f", hits, miss, ratio );
}

/*
    For number of page frames 10 we'll have:
    Hits = 10 Misses = 990 Ration = 0.010101
    For number of page frames 50 we'll have:
    Hits = 18 Misses = 982 Ration = 0.018330
    For number of page frames 100 we'll have:
    Hits = 18 Misses = 982 Ration = 0.018330

    It happens since we gave only 16 bits for page counter =>
    we would be able to track only 16 pages since some page,
    because counter of page after 15th shifts without hitting that page would be 1
    => on 16th, and later  it would be 0 and might be easily substituted by new page.
 */