#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int* myRealloc(int* ptr, size_t size) {
    printf("sizeof new array in bytes: %ld\n",size);
    if (size==0) {
        printf("Since size is 0 free invokes and NULL returns\n");
        free(ptr);
        return NULL;
    } else {
        if (ptr!=NULL) {
            printf("sizeof 1st element: %ld\n", sizeof(ptr[0]));
        } else {
            printf("point on the array is initially a NULL pointer\n");
        }

        int* newPtr= malloc(size);//create new pointer
        newPtr=memcpy(newPtr,ptr,size);//copy data
        free(ptr);
        printf("new size of the array: %ld\n", size / sizeof(ptr[0]));
        return newPtr;
    };
}

int main() {//for check
    printf("Enter size of the array: ");
    int n;
    scanf("%d",&n);
    int *array=calloc(n,sizeof(int));
    for (int i=0; i<n; i++) {
        array[i]+=i;
        printf("array[%d]=%d\n",i,array[i]);
    }
    printf("Enter size of the new array: ");
    scanf("%d",&n);
    array=myRealloc(array,n*sizeof (int));
    if (array==NULL) {
        free(array);
    } else {
        printf("Let's check new array: \n");
        for (int i=0; i<n; i++) {
            printf("array[%d]=%d\n",i,array[i]);
        }
    }

}
