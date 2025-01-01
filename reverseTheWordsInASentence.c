#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    
    char str[1000];
    char words[50][50];
    int wordCount = 0, charIndex = 0;
    fgets(str, sizeof(str), stdin);

    for (int i = 0; i < strlen(str); i++) {

        if (str[i] != ' ' && str[i] != '\n') {
            words[wordCount][charIndex++] = str[i];
        }

        else if (charIndex > 0) {
            words[wordCount][charIndex] = '\0';
            wordCount++;
            charIndex = 0;
        }
    }

    if (charIndex > 0) {
        words[wordCount][charIndex] = '\0';
        wordCount++;
    }
    
    for (int i = wordCount - 1; i >= 0; i--) {
        printf("%s", words[i]);
        if (i != 0) {
            printf(" ");
        }
    }
}
