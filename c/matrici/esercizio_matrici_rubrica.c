#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUMBERS 100
#define MAX_NAME_LENGTH 40
#define MAX_NUMBER_LENGTH 20

char *names[MAX_NUMBERS];
char *numbers[MAX_NUMBERS];

int readString(FILE *input, char **string, int max) {
    char *buffer = NULL;
    if (getline(&buffer, malloc(sizeof(int)), input) == -1) {
        return -1;
    }

    unsigned int length = strlen(buffer) - 1;
    buffer[length] = '\0';
    if (max > 0 && length >= max) {
        return -1;
    }

    *string = buffer;

    return 0;
}

int readInt(FILE *input, int *number) {
    char *buffer = NULL;
    if (readString(input, &buffer, 0) == -1) {
        return -1;
    }

    char *ptrEnd;
    int result = strtol(buffer, &ptrEnd, 10);
    if (buffer == ptrEnd || *ptrEnd != '\0') {
        return -1;
    }

    *number = result;

    return 0;
}

char *toLowerCase(char *input) {
    if (input == NULL) {
        return NULL;
    }

    unsigned int length = strlen(input);
    char *lowered = malloc(sizeof(char) * length);
    for (int i = 0; i < length; i++) {
        lowered[i] = (char) tolower(input[i]);
    }
    lowered[length] = '\0';

    return lowered;
}

int compareExact(char *s1, char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return s1 == s2;
    }

    return strcmp(s1, s2) == 0;
}

int compareInclude(char *parent, char *child) {
    if (parent == NULL) {
        return child == NULL;
    } else if (child == NULL) {
        return 0;
    }

    return strstr(parent, child) != NULL;
}

/**
 * @param query The name to search, or NULL if seeking for an available index.
 * @param exactSearch 1 if the query must match exactly the given query, 0 if it's just part of the query.
 * @return The index for the given query, or else -1.
 */
int findNumber(char *query, int exactSearch) {
    query = toLowerCase(query);

    int (*compare)(char *, char *) = exactSearch ? &compareExact : &compareInclude;
    for (int i = 0; i < MAX_NUMBERS; i++) {
        if (compare(toLowerCase(names[i]), query)) {
            return i;
        }
    }

    return -1;
}

void printNumbers(FILE *output) {
    fprintf(output, "Rubrica: [\n");
    for (int i = 0; i < MAX_NUMBERS; i++) {
        if (names[i]) {
            fprintf(output, "\t'%s' => %s\n", names[i], numbers[i]);
        }
    }
    fprintf(output, "]\n");
}

int main() {
    int command = 0;
    do {
        printf("1) Aggiungi una nuova voce in rubrica\n"
               "2) Ricerca esatta per nome\n"
               "3) Ricerca approssimata per nome\n"
               "4) Stampa completa della rubrica\n"
               "0) Esci dal programma\n");

        printf("Opzione: ");
        if (readInt(stdin, &command) == -1) {
            printf("Input errato.\n");
            command = -1;
        } else {
            switch (command) {
                case 0: // Exit
                    break;
                case 1: { // Add number
                    printf("Stai aggiungendo un numero alla rubrica.\n");
                    int index = findNumber(NULL, 1);
                    if (index == -1) {
                        printf("Non c'e' spazio per salvare un nuovo contatto.\n");
                    } else {
                        printf("Nome: ");
                        char *name = NULL;
                        readString(stdin, &name, MAX_NAME_LENGTH);
                        printf("Numero: ");
                        char *number = NULL;
                        readString(stdin, &number, MAX_NUMBER_LENGTH);
                        if (!name || !number) {
                            printf("Nome o numero non valido.\n");
                        } else {
                            names[index] = name;
                            numbers[index] = number;

                            printf("'%s' aggiunto con successo alla rubrica.\n", name);
                        }
                    }
                    break;
                }
                case 2: // Find by exact name
                case 3:; // Find by name
                    printf("Nome: ");
                    char *nome;
                    if (readString(stdin, &nome, MAX_NAME_LENGTH)) {
                        printf("Input errato.\n");
                    } else {
                        int index = findNumber(nome, command == 2);
                        if (index == -1) {
                            printf("Nessun contatto e' stato trovato col nome '%s'.\n", nome);
                        } else {
                            printf("'%s': => %s\n", names[index], numbers[index]);
                        }
                    }
                    break;
                case 4: { // Print all numbers
                    printNumbers(stdout);
                    break;
                }
                default:
                    printf("Opzione non valida.\n");
            }
        }
    } while (command != 0);

    return 0;
}
