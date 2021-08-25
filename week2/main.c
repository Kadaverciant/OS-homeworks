#include <stdio.h>
#include "limits.h"
#include "float.h"
int main() {
    int a=INT_MAX;
    float b=FLT_MAX;
    double c = DBL_MAX;
    printf("Variable 'a' of type int has maximum value %d and size %d bytes\n", a, sizeof(a));
    printf("Variable 'b' of type float has maximum value %e and size %d bytes\n", b, sizeof(b));
    printf("Variable 'c' of type double has maximum value %e and size %d bytes\n", c, sizeof(c));
}
