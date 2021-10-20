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
    printf("File -- Hard Links\n");
    for (int i=0; i<index; i++) {
        int counter=0;//counter for number of links
        for (int k=0; k<index; k++) {
            if(array[i]->d_ino == array[k]->d_ino){
                counter++;
            }
        }
        if (counter>1) {
            printf("%s -- ", array[i]->d_name);
            for (int k=0; k<index; k++) {
                if (array[i]->d_ino==array[k]->d_ino) {
                    if (counter!=1) {
                        printf("%s, ",array[k]->d_name);
                        counter--;
                    } else {
                        printf("%s",array[k]->d_name);
                    }
                }
            }
            printf("\n");
        }
    }
}

int main() {
    doSmthWithDir("tmp/");
}