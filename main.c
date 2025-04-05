#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metrics.h"
#include "orders.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <archivo.csv> <metrica1> <metrica2> ...\n", argv[0]);
        return 1;
    }

    int size = 1000;
    order* orders = NULL;
    structcsv(argv[1], &orders, &size);

    char* metricas[] = {"pms", "pls", "dms", "dls", "dmsp", "dlsp", "apo", "apd", "ims", "hp"};
    char* (*funciones[])(int*, order*) = {pms, pls, dms, dls, dmsp, dlsp, apo, apd, ims, hp};

    for (int i = 2; i < argc; i++) {
        for (int j = 0; j < 10; j++) {
            if (strcmp(argv[i], metricas[j]) == 0) {
                char* resultado = funciones[j](&size, orders);
                printf("%s\n", resultado);
                free(resultado);
            }
        }
    }

    free(orders);
    return 0;
}