
#include <stdio.h>

int main() {
    int v[5] = {1,2,3,4,5};

    int counter = 0;
    do {
        printf("v[%i] = %i\n", counter, v[counter]);
        counter = counter +1;
    } while (counter < 5);
    return 0;
}