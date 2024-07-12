#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>

int main(void) {

    uint8_t a = 12;
    uint8_t b = getMyNumber();
    if (a == b) {
        printf("My numbers are the same\n");
    } else {
        printf("My numbers are not the same\n");
    }
    return 0;
    }

    uint8_t getMyNumber() {

        uint8_t c = 1;
        uint8_t d = 2;
        uint8_t e = 6;
        uint8_t myNumber = c * d * e;

        return myNumber;
    }
