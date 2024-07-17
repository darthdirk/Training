#include <stdio.h>
#include <stdint.h>

typedef struct {
    int8_t hours;
    uint32_t micros;
    uint16_t seconds;
} timestuff_t;

int main() {
    timestuff_t t = {.hours=6, .micros= 0x12345678, .seconds = 0xDEAD};
    printf("%lu", sizeof(t));
    
}