#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "libshuffle.h"

#define ARRLENGTH 6


int main(void) {
    char *mystrings[ARRLENGTH] = {"Hello?", "Is", "there", "anybody", "in", "there?"};
    shuffle_array(mystrings, 6);
    printf("Old strings for comparison \n");
    // print out the strings and confirm that they are shuffled and that none are lost.
    for(int i = 0; i < ARRLENGTH; i++) {
        
        printf("mystrings:%d\t%p\t%s\n", i, mystrings[i], mystrings[i]);
    }
   
}
