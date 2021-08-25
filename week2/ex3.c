#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
int main(int argc, char *argv[]) {
    int n;
    if (argc==2) {
        int ok = 1;
        for (int i=0; i<strlen(argv[1]); i++) {
            if (isdigit(argv[1][i])==0)
                ok=0;
        }
        if (ok==0) {
            printf("ERROR: you should insert integer value!\n");
        } else if (atoi(argv[1])<0) {
            printf("ERROR: your value should be positive or it is too big\n");
        } else {
            n= atoi(argv[1]);
            int spaces=n-1;
            int stars=1;
            for (int i=0; i<n; i++) {
                for (int j=0; j<spaces; j++) {
                    printf("%c",' ');
                }
                for (int j=0; j<stars; j++) {
                    printf("%c",'*');
                }
                for (int j=0; j<spaces; j++) {
                    printf("%c",' ');
                }
                spaces--;
                stars+=2;
                printf("%c",'\n');
            }
        }
    } else if (argc==1) {
        printf("Enter a height:\n");
        char c[1000];
        fgets(c,sizeof (c),stdin);
        int ok = 1;
        for (int i=0; i<strlen(c); i++) {
            if (isdigit(c[i])==0) {
                ok=0;
                //                printf("%d",ok);
            }

        }
        if (ok==0) {
            printf("ERROR: you should insert integer value!\n");
        } else if (atoi(c)<0) {
            printf("ERROR: your value should be positive or it is too big\n");
        } else {
            n= atoi(c);
            int spaces=n-1;
            int stars=1;
            for (int i=0; i<n; i++) {
                for (int j=0; j<spaces; j++) {
                    printf("%c",' ');
                }
                for (int j=0; j<stars; j++) {
                    printf("%c",'*');
                }
                for (int j=0; j<spaces; j++) {
                    printf("%c",' ');
                }
                spaces--;
                stars+=2;
                printf("%c",'\n');
            }
        }
    } else {
        printf("ERROR: too many arguments\n");
    }
}
