#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <memory.h>

int main() {
    struct rusage usage;
    for (int i=0; i<10; i++) {
        memset(calloc(500 * 1024*1024, 1), 0, 200 * 1024*1024);
        getrusage(RUSAGE_SELF,&usage);
        printf("System time used = %ld.%06ld\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
        printf("Max resident set size = %ld\n",usage.ru_maxrss);
        printf("integral shared memory size = %ld\n",usage.ru_ixrss);
        printf("integral unshared data size = %ld\n",usage.ru_idrss);
        printf("integral shared stack size = %ld\n",usage.ru_isrss);

        sleep(1);
    }
    return 0;
}

