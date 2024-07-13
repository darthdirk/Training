#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

void whereis(void *addr, char *name) {
    printf("%s is at %p\n", name, addr);
}

uint8_t x = 0;

int main() {
    while(x < 100) {
        whereis(&x, "x");
        sleep(1);
        x++;
    }
}