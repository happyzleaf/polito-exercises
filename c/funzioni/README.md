# Tracce
*Tutte le soluzioni sono contenute nel file `esercizi_funzioni.c`.*

Scrivere un programma in C che chiami una funzione Max che:
	- Riceva in ingresso due numeri interi a e b
	- Restituisca il valore massimo tra a e b
Soluzione:
```c
int max(int a, int b) {
    return a > b ? a : b;
}
```
	
Scrivere un programma in C che chiami una funzione power che, ricevuti due parametri interi b ed e (e sicuramente positivo), calcoli la potenza b^e
Soluzione:
```c
int power(int base, unsigned int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}
```

Scrivere un programma in C che legga da tastiera una sequenza di numeri interi positivi primi. Il programma si interrompe quando l’utente inserisce da tastiera un numero NON primo.
NB: Si implementi una funzione isPrime che, ricevuto un numero intero come parametro di ingresso, restituisca
	- 1 se il numero è primo
	- 0 se il numero non è primo
Soluzione:
```c
int isPrime(unsigned int number) {
    // Se il numero è minore o uguale a tre
    if (number <= 3) {
        // Allora è primo se è anche maggiore di 1. Quindi 2 e 3 sono primi. 0 e 1 no.
        return number > 1;
    }

    // Imposto un limite fino a dove controllare. Siamo sicuri che un numero non è mai divisibile per un numero maggiore della sua radice quadrata
    int limit = (int) ceil(sqrt(number));

    // Testo tutti i numeri da 2 al limite.
    for (int i = 2; i <= limit; i++) {
        // Se number è divisibile per i, allora non è primo.
        if (number % i == 0) {
            return 0;
        }
    }

    // Se arrivo fino a qui, number non è stato divisibile per nessun numero precedente a lui. Quindi è primo
    return 1;
}

void main() {
    unsigned int number;
    do {
        char rawNumber[32];
        printf("Inserisci un numero: ");
        if (scanf("%s", rawNumber) == EOF) {
            return 1;
        }
        number = strtol(rawNumber, NULL, 10);
    } while (isPrime(number));
    printf("%d non e' un numero primo.\n", number);
}
```
*Lessi che scanf non andava bene per la produzione visto che l'input non viene mai controllato, quindi ho provato lo standard costituito da scanf di una stringa e strtol. A pensarci ora sembra che 32 caratteri siano anche troppi per una uint ma fa niente.*


Scrivere un programma in C che legga due interi a e b da tastiera e ne calcoli e visualizzi a video la somma.
Tale operazione deve essere svolta richiamando una funzione Somma che:
	- riceva in ingresso i valori a e b (passaggio per valore)
	- riceva in ingresso il puntatore ad una variabile s (passaggio per riferimento)
	- calcoli la somma di a e b e salvi tale risultato nella variabile s
Soluzione:
```c
void sum(int a, int b, int *s) {
    *s = a + b;
}

void main() {
    int a, b;
    printf("(a + b): ");
    scanf("%d + %d", &a, &b);
    int *sPtr = malloc(sizeof(int));
    sum(a, b, sPtr);
    printf("Sum: %d\n", *sPtr);
}
```
*Ho voluto provate a risolverlo con una variabile puntatore invece che una variabile normale, in che significa usare il `malloc` per creare spazio dove salvare il vero valore.*

Scrivere un programma in C che
	- legga un vettore vett di 10 interi introdotti da tastiera
	- legga un intero x da tastiera
	- richiami una funzione MinMax che, ricevuti il vettore vett e l’intero x come parametri di input, restituisca:
		• un valore di ritorno pari a 1 se il valore x è presente all’interno di vett, 0 in caso contrario
		• il valore massimo presente all’interno del vettore
		• il valore minimo presente all’interno del vettore 
Soluzione:
```c
int minMax(const int array[], int size, int x, int *min, int *max) {
    if (size == 0) {
        return -1;
    }

    int found = 0;

    *min = array[0];
    *max = array[0];
    for (int i = 0; i < size; i++) {
        int number = array[i];
        if (number == x) {
            found = 1;
        }

        if (number < *min) {
            *min = number;
        }

        if (number > *max) {
            *max = number;
        }
    }

    return found;
}

void main() {
    int array[10] = {31, 43, 511, 26, 4, 21, 3, 45, 842, 123};
    int x = 17;
    int min, max;
    int found = minMax(array, 10, x, &min, &max);
    printf("%d %s in the array. Min: %d. Max: %d.\n", x, found ? "found" : "not found", min, max);
}
```
