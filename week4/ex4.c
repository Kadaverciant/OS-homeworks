#include <stdio.h>
#include "unistd.h"
#include "sys/wait.h"
#include "string.h"

int main(void) {
    int id;
    char *command, *parameters[128], input[128];
    while (1) {
        printf("\n>");
        fgets(input,128,stdin);
        if (input[0]=='\n') //check empty input ('\n')
            continue; //if we face it, then start new loop
        // Now we break our input string on words
        char *token;
        token = strtok(input," ");
        id=0;
        while(token!=NULL){
            parameters[id]=token;
            token = strtok(NULL," ");
            id++;
        }
        parameters[id-1][strlen(parameters[id-1])-1]='\0';//removing '\n' from the last word
        parameters[id]=NULL;
        command=parameters[0];//our command lies in first word that we receive after separation of input string
        if (strcmp(command,"")!=0) {//check on existence of command, since case with string numerous spaces might happen.
            if (strcmp(command,"exit")==0)
                break;
            if (fork()!=0) {
                if (strcmp(parameters[id-1],"&")!=0)//we won't wait a child process if it works in background.
                    wait (NULL);//wait for child
            } else {
                if (execvp(command, parameters) < 0) {//I used execvp instead of execve in order to let the system determine the PATH by itself.
                    printf("Error");//if there is something wrong with command or parameters we'll receive error
                }
            }
        }
    }
}