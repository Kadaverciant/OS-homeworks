#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <linux/input.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void checkForShortcuts (int *buff) {
    if (buff[1]==25 && buff[0]==18)
        printf("\n -I passed the Exam!\n");
    if (buff[2]==46 && buff[1]==30 && buff[0]==20)
        printf("\n -Get some cappucino!\n");
    if (buff[3]==38 && buff[2]==23 && buff[1]==24 && buff[0]==49)
        printf("\n -Gaoo!\n");
    if (buff[5]==17 && buff[4]==23 && buff[3]==49 && buff[2]==20 && buff[1]==18 && buff[0]==19)
        printf("\n -PADORU-PADORU!!!\n");
}


int main() {
    const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    struct input_event event;
    ssize_t n;
    int fd;
    int bufferSize=6;
    int buffer[bufferSize];
    for (int i=0; i<bufferSize; i++) {
        buffer[i]=0;
    }
    printf("List of shortcuts:\n");
    printf("1) pe\n");
    printf("2) cat\n");
    printf("3) lion\n");
    printf("4) winter\n");

    fd=open(dev, O_RDONLY);
    if (fd==-1) {
        fprintf(stderr, "Can't open %s: %s. \n",dev, strerror(errno));
        return EXIT_FAILURE;
    }

    while (1) {
        n=read(fd, &event, sizeof event);
        if (event.value==1) {
            for (int i=bufferSize-1; i>0; i--) {
                buffer[i]=buffer[i-1];
            }
            buffer[0]=event.code;
            checkForShortcuts(buffer);
        }
    }
    fflush(stdout);
}
