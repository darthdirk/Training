#include <stdio.h>

int main() {
    int value = 10; 
    int *ptr  = &value;     // a pointer that holds the address of 'value'

    printf("Value: %d\n", value);           // Prints the value directly
    printf("Pointer: %p\n", (void *)(ptr)); // Prints the address stored in the pointer
    printf("Dereferenced: %d\n", *ptr);     // Dereferences the pointer to access the value

    return 0;
}