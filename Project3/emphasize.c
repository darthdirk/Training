#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


int main(void) {

    FILE *wordsFile;

    char readBuf[64];
    char writeBuf[64];
    int c;
    uint8_t lineCount = 0;

    wordsFile = fopen("words.txt", "r+");
    if (wordsFile == NULL) {
        perror("File not found");
        fclose(wordsFile);
        return EXIT_FAILURE;
    } 

    while(fgets(readBuf, sizeof(readBuf), wordsFile) != NULL) {
        char *next = strchr(readBuf, '.');
        *next = '!';
        printf("%d:[%p]--- %s\n",++lineCount, next, readBuf);

    }

    fclose(wordsFile);

    return EXIT_SUCCESS;
}