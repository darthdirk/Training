#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <wait.h>

enum {SEGMENT_SIZE = 0x6400};

const char *data = "Hello World";


int main(int argc, char *argv[]) {
    int status;
    int segment_id;
    
    segment_id = shmget(IPC_PRIVATE, SEGMENT_SIZE, IPC_CREAT | IPC_EXCL);
    char *sh_mem = (char *)shmat(segment_id, NULL, 0);

    printf("Segment ID %d\n", segment_id);
    printf("Attached at %p\n", sh_mem);
    memmove(sh_mem, data, strlen(data) + 1);
    printf("%s\n", sh_mem);

    shmdt(sh_mem);
    shmctl(segment_id, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
}