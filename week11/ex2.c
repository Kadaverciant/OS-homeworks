#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void doSmthWithDir(char *dir)
{
    DIR *dp;
    struct dirent *entry;
    struct dirent *array[256];
    int index=0;

    dp = opendir(dir);
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    while((entry = readdir(dp)) != NULL) {
        array[index]=entry;
        index++;
    }
    closedir(dp);
    for (int i=0; i<index; i++) {
        printf("%s\n",array[i]->d_name);
    }
}

int main() {
    doSmthWithDir("/");
}