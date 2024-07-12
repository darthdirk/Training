#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <cstdint>

#define BITVALUE(X, N) (((X) >> (N)) & 0x1)

const char *error_strings[] = {
    "Error 1 current is to low to operate.",
    "Error 2 current is to high to operate.",
    "Error 4 current read failure.",
    "Error 8 system did not shut off."
};

int main(void) {

uint8_t error_bits = 1;
uint8_t num_error_bits = sizeof(error_bits);

for (uint8_t i = 0; i < num_error_bits; i++) {
    if (BITVALUE(error_bits, i)) {
        const char *error_str = error_strings[i];
        for (const char *d = error_str; *d != '\0'; d++) {
            printf(*d);
        }
    }
}
}

