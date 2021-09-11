#include <stdio.h>
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"

int main(void) {
    char c[128];
    while(1) {
        printf("\n>");
        scanf("%s",c);
        system(c);
    }
}