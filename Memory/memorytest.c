
#include <stdlib.h>
#include <stdio.h>

void whereis(void *addr, char *name) {
    printf("%s is at %p\n",name, addr);
}

int gx = 56;

int main() {
    int x;
    int *px = malloc(sizeof(int));

    whereis(&x, "x");
    whereis(&gx, "gx");
    whereis(px, "px");
    whereis(main, "main");
    whereis(whereis, "whereis");

}