#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>



int main(void) {
    
    FILE *questionsFile;       // Variable to represent an input file
    FILE *answersFile;      // Variable to represent an output file

    
    char readBuf[64];    
    char writeBuf[64];
         
    
    questionsFile = fopen("questions.txt", "r");   // Open file for reading
    if (questionsFile == NULL) {
        perror("failed to open questions file");
        return EXIT_FAILURE;
    }
    
    answersFile = fopen("answers.txt", "w");    // Open a file for writing 
    if (answersFile == NULL) {
        perror("Failed to open answers file");
        fclose(questionsFile);
        return EXIT_FAILURE;
    }

    uint8_t lineCount = 0;

    printf("Are you ready for the survey: ");
    if (fgets(writeBuf, sizeof(writeBuf), stdin) != NULL) {
        printf("%s", writeBuf);
        fwrite(writeBuf, sizeof(stdin), strlen(writeBuf), answersFile);
    }
    // Read and process each question
    while (fgets(readBuf, sizeof(readBuf), questionsFile) != NULL) {
        printf("%d: %s", ++lineCount, readBuf);
        if (fgets(writeBuf, sizeof(writeBuf), stdin) != NULL) {
            printf("%s", writeBuf);
            fwrite(writeBuf, sizeof(stdin), strlen(writeBuf), answersFile);
        }
    }
    fclose(questionsFile);
    fclose(answersFile);

    return EXIT_SUCCESS;

}