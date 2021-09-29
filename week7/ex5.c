#include <stdio.h>
#include "stdlib.h"
int main() {
    //we create array of pointers on strings(array of chars)
    char **s = malloc(sizeof (char*));
    char foo[] = "Hello World";//array of chars - string
    *s = foo;//Put string through pointer in a first cell of our array,
             // since pointer to an array = pointer to a first element in this array
    printf("s is %s\n",*s);//dereference a pointer to an array and receive
                                  // first element in it - string
    s[0] = foo;//Same as ' *s = foo; '
    printf("s[0] is %c\n",*s[0]);//receive 1st char in 1st element in array -
                                        //1st char in a string that lies in the array.
    free(s);
    return (0);
}