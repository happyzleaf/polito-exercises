#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 1000
#define MAX_CHARS_PER_LINE 100
#define ENDING_LINE "FINE"

char *readLine() {
    char *buffer = NULL;
    if (getline(&buffer, malloc(sizeof(int)), stdin) == -1) {
        return NULL;
    }
    int length = strlen(buffer) - 1;
    buffer[length] = '\0';
    return length >= MAX_CHARS_PER_LINE ? NULL : buffer;
}

int main() {
    char lines[MAX_LINES][MAX_CHARS_PER_LINE];
    int totalLines = 0;

    int line = 0;
    int hasReachedEnd = 0;
    while (line < MAX_LINES && !hasReachedEnd) {
        printf("[%d] ", line++);
        char *content = readLine();
        if (!content) {
            printf("Il testo non deve superare i %d caratteri.\n", MAX_CHARS_PER_LINE);
            line--;
        } else if (strcmp(content, ENDING_LINE) == 0) {
            hasReachedEnd = 1;
        } else {
            strcpy(lines[line], content);
        }
    }
    totalLines = line;

    int totalCharacters = 0;
    int totalAlnumCharacters = 0;
    int totalWords = 0;
    for (int x = 0; x < totalLines; x++) {
        int length = strlen(lines[x]);

        for (int y = 0; y < length; y++) {
            totalCharacters++;
            if (isalnum(lines[x][y])) {
                totalAlnumCharacters++;
                if (y + 1 == length || !isalnum(lines[x][y + 1])) {
                    totalWords++;
                }
            }
        }
    }

    printf("Righe inserite: %d.\n"
           "Caratteri inseriti: %d\n"
           "Caratteri alfanumerici inseriti: %d\n"
           "Parole inserite: %d\n",
           totalLines, totalCharacters, totalAlnumCharacters, totalWords);

    return 0;
}
