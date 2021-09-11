#include <stdio.h>
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"

int main() {
    for (int i=0; i<5; i++) {
        printf("%d\n",i);
        fork();
    }        sleep(10);
}

/*
For 3 loops 8 processes are created, because our fork() works 3 times, and
every time it works - it double the number of our processes:

                                     0
                                    / \
                                   /   \
                                  /     \
                                 /       \
                                /         \
                               /           \
                              0             1           1st fork
                             / \           / \
                            /   \         /   \
                           0     2       1     3       2nd fork
                          / \   / \     / \   / \
                         0   4 2   5   1   6 7   8     3rd fork
So the in that case number of processes is 2^n where n - number of loops
2^3=8
ex2─┬─ex2─┬─ex2───ex2
    │     └─ex2
    ├─ex2───ex2
    └─ex2


For 5 loops 32 processes are created, since 2^5=32
ex2─┬─ex2─┬─ex2─┬─ex2─┬─ex2───ex2
    │     │     │     └─ex2
    │     │     ├─ex2───ex2
    │     │     └─ex2
    │     ├─ex2─┬─ex2───ex2
    │     │     └─ex2
    │     ├─ex2───ex2
    │     └─ex2
    ├─ex2─┬─ex2─┬─ex2───ex2
    │     │     └─ex2
    │     ├─ex2───ex2
    │     └─ex2
    ├─ex2─┬─ex2───ex2
    │     └─ex2
    ├─ex2───ex2
    └─ex2
 */
