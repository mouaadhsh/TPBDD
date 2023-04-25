#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRandomNumber() {
    int num;
    srand(time(NULL));
    num = rand() % 1000;
    return num;
}

int main() {
    int randomNum = generateRandomNumber();
    printf("Random number between 0 and 999: %d\n", randomNum);
    return 0;
}
