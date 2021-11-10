#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int n,m;
    n=5;
    m=3;
    int e[m];
    int a[m];
    int c[n][m];
    int r[n][m];

    FILE *fptr = fopen("input.txt","r");
    if(fptr == NULL){
        printf("error with opening file\n");
        return 0;
    }

    for (int i=0; i<m; i++) {
        fscanf(fptr,"%d",&e[i]);
        //printf("%d",e[i]);
    }

    for (int i=0; i<m; i++) {
        fscanf(fptr,"%d",&a[i]);
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            fscanf(fptr,"%d",&c[i][j]);
            //printf("%d",c[i][j]);
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            fscanf(fptr,"%d",&r[i][j]);
        }
    }

    int r_list[n];
    for (int i=0; i<n; i++) {
        r_list[i]=1;
    }
    int need=1;
    int dead=1;
    int wasDead=0;
    for (int k=0; k<n; k++) {
        dead=1;
        for (int i = 0; i < n; i++) {
            if (r_list[i]==1) {
                need = 1;
                for (int j = 0; j < m; j++) {
                    if (a[j] >= r[i][j]) {
                        need *= 1;
                    } else {
                        need *= 0;
                    }
                }
                //printf("%d\n",need);
                if (need == 1) {
                    dead=0;
                    r_list[i]=0;
                    printf("R = {");
                    for (int j = 0; j < m - 1; j++) {
                        printf("%d, ", r[i][j]);

                    }
                    printf("%d}, process -> %d\n", r[i][m - 1], i+1);
                    printf("A1 = {");
                    for (int j = 0; j < m - 1; j++) {
                        printf("%d, ", a[j]);
                    }
                    printf("%d}\n", a[m - 1]);
                    printf("Al = {");
                    for (int j = 0; j < m - 1; j++) {
                        printf("%d, ", c[i][j]);
                        a[j]+=c[i][j];
                    }
                    printf("%d}\n", c[i][m - 1]);
                    a[m-1]+=c[i][m - 1];
                    printf("A2 = {");
                    for (int j = 0; j < m - 1; j++) {
                        printf("%d, ", a[j]);
                    }
                    printf("%d}\n\n", a[m - 1]);
                    break;
                }
            }
        }
        if (dead==1) {
            printf("Deadlock.\n");
            wasDead=1;
            break;
        }
    }
    if (wasDead==0) {
        printf("No deadlocks were found.\n");
    }

    fclose(fptr);
}
