#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

void swap(int* first,int* second) {
    int temp=*first;
    *first=*second;
    *second=temp;
}

void bubbleSort(int* a, int size) {
    for (int i=0; i<size-1; i++) {
        for (int j=i+1; j<size; j++) {
            if (a[i]>a[j])
                swap(&a[i],&a[j]);
        }
    }
}

int checkForElements(char *c, int length) {
    int ok = 1;
    //    printf("%c",c[0]);
    if (isdigit(c[0])!=1) {
        if(c[0]!='-') {
            ok=0;
        }
    }

    for (int i=1; i<length-1; i++) {
        if (isdigit(c[i])==0) {
            ok=0;
            //                            printf("%d",ok);
        }
    }  if (ok==0) {
        printf("ERROR: you should insert integer value!\n");
        return 0;
    } else  {
        return 1;
    }
}

int checkForSize(char *c, int length) {
    int ok = 1;
    for (int i=0; i<length-1; i++) {
        if (isdigit(c[i])==0) {
            ok=0;
            //                printf("%d",ok);
        }
    } if (atoi(c)<0) {
        printf("ERROR: your value should be positive or it is too big\n");
        return 0;
    } else if (ok==0) {
        printf("ERROR: you should insert integer value!\n");
        return 0;
    } else  {
        return 1;
    }
}

int main() {
    int n;
    printf("Insert the size of your array:");

    char c2[100];
    int ok =1;
    scanf("%s",c2);
    if (checkForSize(c2, strlen(c2)) == 1) {
        n= atoi(c2);
        int a[n];
        for (int i=0; i<n; i++) {
            char c1[100];
            scanf("%s",c1);
            if (checkForElements(c1, strlen(c1)) == 1) {
                a[i]= atoi(c1);
            } else {
                ok=0;
                break;
            }
        }
        if (ok==1) {
            printf("Your array before sort:\n");
            for (int i=0; i<n; i++)
                printf("%d ",a[i]);
            bubbleSort(a,n);
            printf("\nYour array after bubble sort:\n");
            for (int i=0; i<n; i++)
                printf("%d ",a[i]);
        }
    }
    return 0;
}