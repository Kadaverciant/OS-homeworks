#include <stdio.h>
int main() {
    int n;
    scanf("%d",&n);
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
