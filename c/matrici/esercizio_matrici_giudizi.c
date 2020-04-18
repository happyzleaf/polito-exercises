#include <stdio.h>
#include <stdlib.h>

#define MAX_PLAYERS 100
#define MAX_JUDGES 10

void printMatrix(int maxColumns, int maxRows, int columns, int rows, int matrix[maxColumns][maxRows]) {
    printf("{\n");
    for (int x = 0; x < columns; x++) {
        printf("\t[");
        for (int y = 0; y < rows; y++) {
            printf("%d", matrix[x][y]);
            if (y + 1 != rows) {
                printf(", ");
            }
        }
        printf("]");
        if (x + 1 != columns) {
            printf(",");
        }
        printf("\n");
    }
    printf("}\n");
}

int readInteger() {
    char raw[32];
    scanf("%s", raw);
    return strtol(raw, NULL, 10);
}

int check(int test, char *error) {
    if (!test) {
        puts(error);
    }

    return test;
}

int *calculateBestPlayer(int players, int judges, int judgments[MAX_PLAYERS][MAX_JUDGES], int *maxVotes) {
    int *bestPlayer = NULL;

    for (int x = 0; x < players; x++) {
        int totalVotes = 0;
        for (int y = 0; y < judges; y++) {
            totalVotes += judgments[x][y];
        }
        if (!bestPlayer || totalVotes > *maxVotes) {
            bestPlayer = malloc(sizeof(int));
            *bestPlayer = x;
            *maxVotes = totalVotes;
        }
    }

    return bestPlayer;
}

int *calculateHarshestJudge(int players, int judges, int judgments[MAX_PLAYERS][MAX_JUDGES], int *minVotes) {
    int *harshestJudge = NULL;

    for (int y = 0; y < judges; y++) {
        int totalVotes = 0;
        for (int x = 0; x < players; x++) {
            totalVotes += judgments[x][y];
        }
        if (!harshestJudge || totalVotes < *minVotes) {
            harshestJudge = malloc(sizeof(int));
            *harshestJudge = y;
            *minVotes = totalVotes;
        }
    }

    return harshestJudge;
}

int main() {
    // Sarebbe più intelligente con delle struct ma fa niente.
    int judgments[MAX_PLAYERS][MAX_JUDGES]; // (100) giocatori -> (10) giudizi

    printf("Inserisci il numero di giocatori: ");
    int players = readInteger();
    if (!check(players <= 100, "I giocatori non possono superare i 100.")) {
        return 1;
    }

    printf("Inserisci il numero di giudici: ");
    int judges = readInteger();
    if (!check(judges <= 10, "I giudici non possono superare i 10.")) {
        return 1;
    }

    for (int x = 0; x < players; x++) {
        printf("Giocatore %d [\n", x + 1);
        for (int y = 0; y < judges; y++) {
            printf("\tGiudice %d = ", y + 1);
            judgments[x][y] = readInteger();
        }
        printf("]\n");
    }

    int *bestPlayerVotes = malloc(sizeof(int));
    int *bestPlayer = calculateBestPlayer(players, judges, judgments, bestPlayerVotes);
    if (!check(bestPlayer != NULL, "Non e' stato possibile trovare il giocatore migliore.")) {
        return 1;
    }
    printf("Il giocatore col punteggio piu' alto e' il giocatore numero %d con un totale di %d voti.\n", *bestPlayer + 1, *bestPlayerVotes);

    int *harshestJudgeVotes = malloc(sizeof(int));
    int *harshestJudge = calculateHarshestJudge(players, judges, judgments, harshestJudgeVotes);
    if (!check(harshestJudge != NULL, "Non e' stato possibile trovare il giudice più severo.")) {
        return 1;
    }
    printf("Il giudice piu' severo e' il giudice numero %d con un totale di %d voti.\n", *harshestJudge + 1, *harshestJudgeVotes);

    return 0;
}
