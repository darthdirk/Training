#include <stdio.h>
#include <stdlib.h>


long count, i;
char *keystr;
int elementlen, len;
char c;
int irng = 1;
/* Initial random number generator. */
srand(irng);

/* Create keys using only lowercase characters */
len = 0;
for (i=0; i<count; i++) {
    while (len < elementlen) {
        c = (char) (rand() % 128);
        if (islower(c))
            keystr[len++] = c;
           }
        keystr[len] = '\0';
        printf("%s Element%0*ld\n", keystr, elementlen, i);
        len = 0;
        }