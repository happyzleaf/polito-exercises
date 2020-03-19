#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int power(int base, unsigned int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

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

void sum(int a, int b, int *s) {
    *s = a + b;
}

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

int main() {
//    unsigned int number;
//    do {
//        char rawNumber[32];
//        printf("Inserisci un numero: ");
//        if (scanf("%s", rawNumber) == EOF) {
//            return 1;
//        }
//        number = strtol(rawNumber, NULL, 10);
//    } while (isPrime(number));
//    printf("%d non e' un numero primo.\n", number);

//    int a, b;
//    printf("(a + b): ");
//    scanf("%d + %d", &a, &b);
//    int *sPtr = malloc(sizeof(int));
//    sum(a, b, sPtr);
//    printf("Sum: %d\n", *sPtr);

//    int array[10] = {31, 43, 511, 26, 4, 21, 3, 45, 842, 123};
//    int x = 17;
//    int min, max;
//    int found = minMax(array, 10, x, &min, &max);
//    printf("%d %s in the array. Min: %d. Max: %d.\n", x, found ? "found" : "not found", min, max);

    return 0;
}
