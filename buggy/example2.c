


#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define NUM_COLORS 6
#define BUFSIZE 1024

#define COLOR_RED 0
#define COLOR_GREEN 1
#define COLOR_YELLOW 2
#define COLOR_BLUE 3
#define COLOR_MAGENTA 4
#define COLOR_CYAN 5

char *colors[NUM_COLORS] = {
    "31m", //red
    "32m", //green
    "33m", //yellow
    "34m", //blue
    "35m", //magenta
    "36m" //cyan
};

#define NUM_TYPES 5
char *types[NUM_TYPES] = {
    "int",
    "float",
    "double",
    "char",
    "void"
};

#define NUM_KEYWORDS 6
char *keywords[NUM_KEYWORDS] = {
    "main",
    "if",
    "while",
    "break",
    "do",
    "typedef"
};

char *colortext(bool bold, int color, char *text) {
    assert(color < NUM_COLORS);
    if(text == NULL) {
        fprintf(stderr, "Error: text is NULL\n");
        exit(EXIT_FAILURE);
    }
    char *result = malloc(BUFSIZE+strlen(text));
    size_t allocation_size = BUFSIZE + strlen(text);
    if(result == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    result[0] = 0;

    char bold_char = '0'; //not bold
    if (bold) {
        bold_char = '1'; //bold
    }
    sprintf(result,"\033[%c;%s%s\033[0m",bold_char, colors[color],text);
    return result;
}

// replace a string with another string
char *replaceText(const char *s, const char *oldW, 
                                 const char *newW) { 
    char *result; 
    int i, cnt = 0; 
    // Error was here sizeof(newW) and sizeof(oldW) return the size of the pointer, not the length of the string
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
  
    // Counting the number of times old word 
    // occur in the string 
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
            // Jumping to index after the old word. 
            i += oldWlen - 1; 
        } 
    } 
  
    // Making new string of enough length 
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);
    if(result == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    i = 0; 
    while (*s) {
        // compare the substring with the result 
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } else {
            result[i++] = *s++; 
    }
    }
    result[i] = '\0'; 
    return result; 
}

char *colorize( char * text ) {
    char *result = malloc(strlen(text)+1);
    strcpy(result, text);

    for (int i=0; i < NUM_TYPES; i++) {
        char *ctext = colortext(true, COLOR_BLUE, types[i]);
        char *oldtext = result;
        result = replaceText(oldtext, types[i],ctext);
        free(ctext);
        free(oldtext);
    }
    for (int i=0; i < NUM_KEYWORDS; i++) {
        char *ctext = colortext(true, COLOR_GREEN, keywords[i]);
        char *oldtext = result;
        result = replaceText(oldtext, keywords[i],ctext);
        free(ctext);
        free(oldtext);
    }
    return result;
}

int main(int argc, char **argv) {
    FILE *fp;
    char buffer[BUFSIZE];
    int c;
   
    if (argc <= 1) {
        // open the current input file
        fp = fopen(__FILE__,"r");
        printf("I was created by this code. (%s)\n\n",__FILE__);
    } else {
        fp = fopen(argv[1],"r");
        printf("Colorizing code. (%s)\n\n",argv[1]);
    }
    if (fp == NULL) {
        perror("File error");
        exit(EXIT_FAILURE);
    }
    
    while (fgets(buffer, BUFSIZE, fp) != NULL) {
        char *colorized_text = colorize(buffer);
        printf("%s",colorized_text);
        free(colorized_text);
    }
    
    fclose(fp);
    return EXIT_SUCCESS;
}