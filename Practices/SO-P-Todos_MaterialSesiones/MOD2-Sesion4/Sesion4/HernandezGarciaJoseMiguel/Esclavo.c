#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

int esPrimo(int n){

    int i;
    int limite = n / 2;
    int es_primo = 1;

    for (i = 2; i <= limite && es_primo; i++)

        if (n % i == 0)
            es_primo = 0;

    return es_primo;
};

int main(int argc, char *argv[]){

    int min, max, i;
    min = atoi(argv[1]);
    max = atoi(argv[2]);

    for (i = min; i < max; i++)

        if (esPrimo(i))
            write(STDOUT_FILENO, &i, sizeof(int));

    return 0;
}
