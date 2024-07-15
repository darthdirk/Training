#ifndef __SHARED_MEMORY_H
#define __SHARED_MEMORY_H

#include <stdbool.h>

// all of the programs will share these same values
#define BLOCK_SIZE 4096
#define FILENAME "writeshmem.c"

//attach a shared memory block
// associated with filename
// create it if it doesnt exist

char * attach_memory_block(char *filename, int size);
bool detach_memory_block(char *block);
bool destroy_memory_block(char *filename);

#endif