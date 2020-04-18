# Esercizi Matrici

In un concorso di intelligenza, N giudici esprimono il loro giudizio su K candidati:
 - `N` e `K` sono interi inseriti dall’utente tramite tastiera.
 - [`N` e `K` sono] rispettivamente minori di `10` e `100`.
 - Il giudizio è un valore numerico tra `0` e `5`.
<br>Si scriva un programma in linguaggio C che:
 - acquisisca da tastiera i giudizi espressi da ciascun giudice per ciascun candidato.
 - determini il candidato più intelligente (i.e. con somma dei giudizi massima).
 - il giudice più severo (i.e. con somma dei giudizi minima).

[Soluzione](esercizio_matrici_giudizi.c)
<br>[Candidato più intelligente](esercizio_matrici_giudizi.c#L40-L56)
```c
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
```
<br>[Giudice più severo](esercizio_matrici_giudizi.c#L58-L74)
```c
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
```

---
Si scriva un programma C che:
 - acquisisca da tastiera un testo libero, composto da più righe (massimo `1000`).
 - di un numero di caratteri non superiore a `100` ciascuna.
 - l'inserimento termina quando l’utente inserisce una riga uguale a `FINE`.
<br>Al termine dell’acquisizione del testo, il programma dovrà stampare le seguenti statistiche:
 - il numero totale di righe inserite.
 - il numero totale di caratteri inseriti.
 - il numero totale di caratteri alfanumerici inseriti.
 - il numero totale di parole inserite.

[Soluzione](esercizio_matrici_testo.c)
<br>[Conteggio statistiche](esercizio_matrici_test.c#L40-L55)
```c
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
```

---
Un’azienda deve tenere traccia dei beni presenti in un magazzino.
<br>L’utente inserisce da tastiera i comandi in questo formato:
 - `<prodotto> [E, U] <quantità>`.
<br>Dove:
 - `<prodotto>` è il nome di un prodotto privo di spazi e di massimo `29` caratteri.
 - massimo `100` prodotti diversi.
 - `<EU>` è la lettera `E` per entrata, `U` per uscita
 - `<quantità>` è la quantità di bene in entrata o in uscita.
<br>L’utente termina il caricamento inserendo un comando pari a `FINE`.
<br>In tal caso il programma stampa le quantità di prodotti presenti a magazzino.
<br>Esempio:
```
Viti E 10
Dadi E 50
Viti U 5
Viti E 3
FINE
```

[Soluzione](esercizio_matrici_prodotti.c)

---
Si realizzi un programma in linguaggio C in grado di gestire una rubrica di nomi e numeri telefonici:
 - la rubrica deve contenere fino a `100` voci diverse.
 - ciascuna [entry] composta da un nome e da un numero di telefono.
 - rispettivamente, massimo 40 e 20 caratteri.
<br>Il programma deve fornire all’utente un menù di scelta, con le seguenti voci:  
 - `1) Aggiungi una nuova voce in rubrica`.
 - `2) Ricerca esatta per nome`.
 - `3) Ricerca approssimata per nome`.
 - `4) Stampa completa della rubrica`.
 - `0) Esci dal programma`.
<br>Una volta che l’utente ha scelto l’operazione desiderata `[1, 2, 3, 4, 0]`, il programma acquisirà i dati necessari dall’utente ed eseguirà il comando.
_Nota: nella rubrica non possono esistere due voci con lo stesso nome._

[Soluzione](esercizio_matrici_rubrica.c)
<br>[Ricerca esatta e approssimata per nome](esercizio_matrici_rubrica.c#L62-L96)
```c
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
```
_Ho voluto sperimentare coi puntatori di funzioni per la seconda e terza opzione._
