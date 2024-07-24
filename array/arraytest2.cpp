
#include <stdio.h>
#include <stdlib.h>

const int  ARRAY_LENGTH = 5;

void printarray(int *myarray, int length) {
    for(int i = 0; i < length; i++) {
        printf("%i", myarray[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    int a[ARRAY_LENGTH] = {1, 2, 3, 4, 5};
    int b[ARRAY_LENGTH] = {5, 4, 3, 2, 1};

    //int *p = (int*)malloc(sizeof(int) * 15);
    int *p = new int[15];
    for(int i = 0; i < 15; i++) {
        p[i] = 0;
    }
    
    a[0] = 76;
    int x = a[1];

    printarray(a, ARRAY_LENGTH);
    printarray(b, ARRAY_LENGTH);
    printarray(p, 15);

    delete[] p;


}