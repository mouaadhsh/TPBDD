#include <stdio.h>

#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

int main(void)
{
    printf("this is " RED("red") "!\n");

    // a somewhat more complex ...
    printf("this is " BLUE("%s") "!\n","blue");

    return 0;
}