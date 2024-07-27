
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ARRLENGTH 10


// void pointer can point to anything so we can compare anything
// qsort requires us to define a compare function and needs the funtion to point to
int compare(const void *pa, const void *pb) {
    int a = *((int *)pa);
    int b = *((int *)pb);
    // a - b compare smallest to largest or b-a largest to smallest
    return a - b;

}

int main() {


    // create some int to sort
    int values[ARRLENGTH];
    for (int i = 0; i < ARRLENGTH; i++) {
        // set the ith value  between 0 and 9999
        values[i] = rand() % 2000;
    }

    qsort(values, ARRLENGTH, sizeof(int), compare);

    for (int i = 0; i < ARRLENGTH; i++) {
        // print out i and the ith value
        printf("%d: \t%d\n", i, values[i]);
    }



}