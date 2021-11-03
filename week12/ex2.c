#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <linux/input.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static const char *const evval[3] = {
        "RELEASED",
        "PRESSED",
        "REPEATED"
};

int main() {
    const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    struct input_event event;
    ssize_t n;
    int fd;

    fd=open(dev, O_RDONLY);
    if (fd==-1) {
        fprintf(stderr, "Can't open %s: %s. \n",dev, strerror(errno));
        return EXIT_FAILURE;
    }

    while (1) {
        n=read(fd,&event,sizeof event);
        switch (event.value) {
            case 0:
                if (event.code!=0)
                    printf("\n%s, %d\n", evval[0], event.code);
                break;
            case 1:
                printf("\n%s, %d\n", evval[1], event.code);
                break;
            case 2:
                printf(" %s, %d\n", evval[2], event.code);
                break;
        }

    }
    fflush(stdout);
}
