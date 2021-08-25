#include <stdio.h>
#include "string.h"
int main() {
    char c[1000];
    fgets(c,sizeof (c),stdin);
    //    printf("%d", strlen(c)); //some check
    //  We output \n symbol too, since it is the last symbol in the initial array,
    //  so if we don't want to print it, then our loop should start from 1.
    for (int i=0; i<strlen(c);i++) {
        printf("%c",c[strlen(c)-i-1]);
    }
}
