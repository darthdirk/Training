#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>


#include "libshuffle.h"


int shuffle_array(char **arr, int length) {
    printf("called a function:\n");
    // set seed based on current time
    srand(time(NULL));
    int generated_numbers[length];
    int counter;
    int value;
    bool is_unique;

    // Initialize the array to hold generated numbers
    for(counter = 0; counter < length; counter++) {
        generated_numbers[counter] = -1;
    }

    for(counter = 0; counter < length; counter ++) {
        do{
            value = rand() % length;
            is_unique = true;

            // Check if the value has allready been generated
            for(int j = 0; j < counter; j++) {
                if (generated_numbers[j] == value) {
                    is_unique = false;
                    break;
                }
            }

        } while (!is_unique);
        generated_numbers[counter] = value;
        printf("Random Number:%d: %d\n", counter + 1, value);
        
    }
    // create another arr to hold the shuffled pointers
    char *shuffled_arr[length];
    for(int i = 0; i < length; i++) {
        //populates the new array and uses the generated_numbers[i] to 
        // provids the index to populate the new array with the randomized index
        shuffled_arr[i] = arr[generated_numbers[i]];
    }
    for(int i = 0; i < length; i++){
        // print out i and the ith value
        printf("shuffled_arr:%d\t%p\t%s\n", i, shuffled_arr[i], shuffled_arr[i]);
    }

    
    return 0;
}