// This program calculates and prints out the factorials of 5 and 17


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint16_t factorial(uint16_t n);

int main(void) {
    
    uint16_t n = 5;
    uint16_t f = factorial(n);
    printf("The factorial of %d is %d.\n", n, f);
    n = 17;
    f = factorial(n);
    printf(" The factorial of %d is %d.\n", n, f);

    return 0;

}
    // factorial is calculated by n! = n * (n-1) * (n-2) *....*1
    // E.G. 5! = 5 * 4 * 3 * 2 * 1 = 120
    uint16_t factorial(uint16_t n) {
        uint16_t f = 1;
        uint16_t i = 1;
        while (i <= n) {
            f = f * i;
            i++;
        }
        return f;
    } 