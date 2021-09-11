#include <stdio.h>
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"
/*
 * At the beginning of the program, the initial process has pid = 0.
 * As soon as we made pid=fork (); our parent process stored the index of
 * the child process in the pid.
 * At the same time, the child process does not have its own child processes
 * and therefore has pid = 0.
 */
int main() {
    pid_t pid;
    pid=fork();
    int n=10;
    for (int i=1; i<=n; i++)
    {
        if (pid>0) {
            printf("Hello from parent [%d - %d]\n", pid,i);
        } else if (pid==0) {
            printf("Hello from child [%d - %d]\n", pid,i);
        } else {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
