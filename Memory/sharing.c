

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <stdint.h>
#include <bits/mman-linux.h>

#define PAGESIZE 4096

int v = 5;

int main(int argc, char** argv) {

    uint8_t *shared_memory = mmap(NULL, PAGESIZE,
                                  PROT_READ | PROT_WRITE,
                                  MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *shared_memory = 34;

    if (fork() == 0) {
        *shared_memory = 15;
        v = 80;
    } else {
        wait(NULL);
    }
    printf("Not shared. %i\n", v);
    printf("Shared. %i\n", shared_memory);

}