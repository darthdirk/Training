
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct person {
    int age;
    int height;
    char name[10];
} person_t;

int main() {
    void *p = malloc(100);

    bzero(p, 100);
    person_t *pp = (person_t*)p; //preforms a typecast and assigns a pointer to a person_t struct.

    pp->age = 99;
    pp->height = 245;
    strncpy(pp->name, "Greg", sizeof(pp->name)-1);

    int *iptr = (int*)(pp+1); // Stick the int after the struct
    *iptr = 0xFEEDBEEF;

    printf("Done!\n");

}