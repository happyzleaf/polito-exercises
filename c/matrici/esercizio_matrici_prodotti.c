#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 29

#define END_COMMAND "FINE"
#define READ_COMMAND "LEGGI"

char *products[MAX_PRODUCTS];
int quantities[MAX_PRODUCTS];

char *readLine(unsigned int size) {
    char *content = NULL;
    if (getline(&content, malloc(sizeof(int)), stdin) == -1) {
        return NULL;
    }

    unsigned int length = strlen(content) - 1;
    content[length] = '\0';
    return length < size ? content : NULL;
}

int compareNullable(char *s1, char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return s1 == s2;
    }

    return strcmp(s1, s2) == 0;
}

int findProduct(char *name) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (compareNullable(name, products[i])) {
            return i;
        }
    }

    return -1;
}

void readProducts() {
    printf("Prodotti: [\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i]) {
            printf("\t%s %d\n", products[i], quantities[i]);
        }
    }
    printf("]\n");
}

int parseInput(char *input, char *name[], int *add, int *quantity) {
    // Check if the input is empty
    if (strlen(input) == 0) {
        return 1;
    }

    // Get the first string before the space, this always works.
    *name = strtok(input, " ");

    // Get the second string
    char *actionString = strtok(NULL, " ");
    // Check if it has been found, then check if it's a single character
    if (!actionString || strlen(actionString) != 1) {
        return 2;
    }

    char action = (char) toupper(actionString[0]);
    if (action == 'E') {
        *add = 1;
    } else if (action == 'U') {
        *add = 0;
    } else {
        return 3;
    }

    // Get the third string, the quantity
    char *quantityString = strtok(NULL, " ");
    // Store where strtol stops reading
    char *endPtr;
    *quantity = strtol(quantityString, &endPtr, 0);
    // Check if anything has been processed (quantityString != endPtr)
    // Then check if nothing has been left of the original string, therefore, the value of endPtr is '\0'
    if (quantityString == endPtr || *endPtr != '\0') {
        return 4;
    }

    if (*quantity <= 0) {
        return 5;
    }

    return 0;
}

int main() {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        quantities[i] = 0;
    }

    int hasReachedEnd = 0;
    while (!hasReachedEnd) {
        printf("Inserisci o rimuovi un prodotto: ");
        char *input = readLine(MAX_NAME_LENGTH);
        if (!input || strlen(input) == 0) {
            printf("L'input non e' valido.\n");
        } else if (strcmp(input, END_COMMAND) == 0) {
            hasReachedEnd = 1;
        } else if (strcmp(input, READ_COMMAND) == 0) {
            readProducts();
        } else {
            char *name;
            int add;
            int quantity;
            if (parseInput(input, &name, &add, &quantity) > 0) {
                printf("L'input non e' valido.\n");
            } else {
                int index = findProduct(name);
                if (add) {
                    if (index == -1) {
                        index = findProduct(NULL);
                        if (index == -1) {
                            printf("Non c'e' spazio per inserire nuovi prodotti.\n");
                        } else {
                            products[index] = name;
                            quantities[index] = quantity;

                            printf("%d %s sono state aggiunte al database.\n", quantity, name);
                        }
                    } else {
                        quantities[index] += quantity;

                        printf("%d %s sono state aggiunte. Totale: %d\n", quantity, name, quantities[index]);
                    }
                } else {
                    if (index == -1) {
                        printf("Il prodotto non e' stato trovato.\n");
                    } else {
                        int total = quantities[index] - quantity;
                        if (total < 0) {
                            printf("Non e' possibile rimuovere %d %s da un totale di %d.\n", quantity, name, quantities[index]);
                        } else if (total == 0) {
                            products[index] = NULL;
                            quantities[index] = 0;
                            printf("%s e' stato rimosso dal dal database.\n", name);
                        } else {
                            quantities[index] = total;
                            printf("%d %s sono stati rimossi dal database. Totale: %d\n", quantity, name, total);
                        }
                    }
                }
            }
        }
    }

    readProducts();

    return 0;
}
