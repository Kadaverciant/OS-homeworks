#include <stdio.h>
void swap(int* first,int* second) {
    int temp=*first;
    *first=*second;
    *second=temp;
}

int main() {
    int a,b;
    printf("insert two integer numbers: \n");
    scanf("%d %d",&a,&b);
    swap(&a,&b);
    printf("%d %d",a,b);
}