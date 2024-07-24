#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>


int shuffle_array(char **arr, int length) {
    printf("called a function:\n");
    // set seed based on current time
    srand(time(NULL));
    int num = 5;
    int generated_numbers[5];
    int counter;
    int value;
    bool is_unique;

    // Initialize the array to hold generated numbers
    for(counter = 0; counter < num; counter++) {
        generated_numbers[counter] = -1;
    }

    for(counter = 0; counter < num; counter ++) {
        do{
            value = rand() % num;
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
        strncpy(*generated_numbers, *arr, sizeof(*arr));
    }
    return 0;
}

int main(void) {
    char *mystrings[6] = {"Hello?", "Is", "there", "anybody", "in", "there?"};
    shuffle_array(mystrings, 6);
    // print out the strings and confirm that they are shuffled and that none are lost.
    printf("mystrings[0]:%p %s\n", mystrings[0], mystrings[0]);
    printf("mystrings[1]:%p %s\n", mystrings[1], mystrings[1]);
    printf("mystrings[2]:%p %s\n", mystrings[2], mystrings[2]);
    printf("mystrings[3]:%p %s\n", mystrings[3], mystrings[3]);
    printf("mystrings[4]:%p %s\n", mystrings[4], mystrings[4]);
    printf("mystrings[5]:%p %s\n", mystrings[5], mystrings[5]);

}
