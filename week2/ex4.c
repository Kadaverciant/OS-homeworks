#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
void swap(int* first,int* second) {
    int temp=*first;
    *first=*second;
    *second=temp;
}

int main() {
    int a,b;
    printf("insert first integer value: \n");
    char c[100];
    gets(c);
    int ok = 1;
    for (int i=0; i<strlen(c)-1; i++) {
        if (isdigit(c[i])==0) {
            ok=0;
            //printf("%d",ok);
        }

    }
    if (ok==0) {
        printf("ERROR: you should insert integer value!\n");
    } else if (atoi(c)<0) {
        printf("ERROR: your value should be positive or it is too big\n");
    }  else {
        a= atoi(c);
        printf("insert second integer value:\n");
        char c1[100];
        gets(c1);
        ok = 1;
        for (int i=0; i<strlen(c1)-1; i++) {
            if (isdigit(c1[i])==0) {
                ok=0;
                //                printf("%d",ok);
            }

        }
        if (ok==0) {
            printf("ERROR: you should insert integer value!\n");
        } else if (atoi(c1)<0) {
            printf("ERROR: your value should be positive or it is too big\n");
        }  else {
            b= atoi(c1);
            swap(&a,&b);
            printf("after swap we'll have:\n");
            printf("%d %d",a,b);
        }
    }
}
