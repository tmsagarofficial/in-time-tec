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
    
    int found = 0;
    for (int i = 0; i < wordCount; i++) {
        int count = 0;
        for (int j = 0; j < wordCount; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                count++;
            }
        }

        if (count == 1) {
            printf("%s\n", words[i]);
            found = 1;
            break;
        }
    }
    if(!found){
        printf("");
    }
    return 0;
}
