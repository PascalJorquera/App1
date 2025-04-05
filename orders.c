#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orders.h"

void structcsv(const char *filename, order **orders, int *size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    char lineas[1024];
    int cantidad = 0;
    *orders = malloc(*size * sizeof(order));
    if (*orders == NULL) {
        printf("Error al asignar memoria\n");
        fclose(file);
        return;
    }

    fgets(lineas, sizeof(lineas), file); // Saltar cabecera

    while (fgets(lineas, sizeof(lineas), file)) {
        int read = sscanf(lineas, "%f,%f,%29[^,],%f,%14[^,],%9[^,],%f,%f,%4[^,],%19[^,],\"%99[^\"]\",%49[^\n]",
            &((*orders)[cantidad].pizza_id), &((*orders)[cantidad].order_id), ((*orders)[cantidad].pizza_name_id),
            &((*orders)[cantidad].quantity), ((*orders)[cantidad].order_date), ((*orders)[cantidad].order_time),
            &((*orders)[cantidad].unit_price), &((*orders)[cantidad].total_price),
            ((*orders)[cantidad].pizza_size), ((*orders)[cantidad].pizza_category),
            ((*orders)[cantidad].pizza_ingredients), ((*orders)[cantidad].pizza_name));
        

        if (read == 12) {
            cantidad++;
            if (cantidad >= *size) {
                *size *= 2;
                *orders = realloc(*orders, *size * sizeof(order));
                if (*orders == NULL) {
                    printf("Error al expandir memoria\n");
                    fclose(file);
                    return;
                }
            }
        } else if (!feof(file)) {
            printf("Formato incorrecto de archivo\n");
            fclose(file);
            return;
        }
    }

    *size = cantidad;
    fclose(file);   
}