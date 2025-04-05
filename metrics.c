#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metrics.h"

char* pms(int* size, order* orders) {
    char* most_sold = NULL;
    int max = 0;

    for (int i = 0; i < *size; i++) {
        int count = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].pizza_name, orders[j].pizza_name) == 0) {
                count += orders[j].quantity;
            }
        }
        if (count > max) {
            max = count;
            most_sold = orders[i].pizza_name;
        }
    }

    char* result = malloc(200);
    sprintf(result, "Pizza más vendida: %s\n", most_sold);
    return result;
}

char* pls(int* size, order* orders) {
    int min = 1000000;
    char* worst = NULL;
    for (int i = 0; i < *size; i++) {
        int count = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].pizza_name, orders[j].pizza_name) == 0) {
                count += orders[j].quantity;
            }
        }
        if (count < min) {
            min = count;
            worst = orders[i].pizza_name;
        }
    }
    char* result = malloc(256);
    sprintf(result, "Pizza menos vendida: %s", worst);
    return result;
}

char* dms(int* size, order* orders) {
    float max = 0;
    char fecha[20];
    for (int i = 0; i < *size; i++) {
        float total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                total += orders[j].total_price;
            }
        }
        if (total > max) {
            max = total;
            strcpy(fecha, orders[i].order_date);
        }
    }
    char* result = malloc(256);
    sprintf(result, "Fecha con mas ventas (dinero): %s con %.2f", fecha, max);
    return result;
}

char* dls(int* size, order* orders) {
    float min = 1000000;
    char fecha[20];
    for (int i = 0; i < *size; i++) {
        float total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                total += orders[j].total_price;
            }
        }
        if (total < min) {
            min = total;
            strcpy(fecha, orders[i].order_date);
        }
    }
    char* result = malloc(256);
    sprintf(result, "Fecha con menos ventas (dinero): %s con %.2f", fecha, min);
    return result;
}

char* dmsp(int* size, order* orders) {
    int max = 0;
    char fecha[20];
    for (int i = 0; i < *size; i++) {
        int total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                total += orders[j].quantity;
            }
        }
        if (total > max) {
            max = total;
            strcpy(fecha, orders[i].order_date);
        }
    }
    char* result = malloc(256);
    sprintf(result, "Fecha con mas ventas (pizzas): %s con %d", fecha, max);
    return result;
}

char* dlsp(int* size, order* orders) {
    int min = 1000000;
    char fecha[20];
    for (int i = 0; i < *size; i++) {
        int total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                total += orders[j].quantity;
            }
        }
        if (total < min) {
            min = total;
            strcpy(fecha, orders[i].order_date);
        }
    }
    char* result = malloc(256);
    sprintf(result, "Fecha con menos ventas (pizzas): %s con %d", fecha, min);
    return result;
}

char* apo(int* size, order* orders) {
    int total_pizzas = 0;
    int total_ordenes = 0;
    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
        total_ordenes++;
    }
    float promedio = (float) total_pizzas / total_ordenes;
    char* result = malloc(256);
    sprintf(result, "Promedio de pizzas por orden: %.2f", promedio);
    return result;
}

char* apd(int* size, order* orders) {
    int total_pizzas = 0;
    int dias = 0;
    for (int i = 0; i < *size; i++) {
        int encontrado = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) dias++;
        total_pizzas += orders[i].quantity;
    }
    float promedio = (float) total_pizzas / dias;
    char* result = malloc(256);
    sprintf(result, "Promedio de pizzas por dia: %.2f", promedio);
    return result;
}

char* ims(int* size, order* orders) {
    typedef struct {
        char ingrediente[100];
        int cantidad;
    } Ingrediente;

    Ingrediente* ingredientes = malloc((*size) * 10 * sizeof(Ingrediente));
    int count = 0;

    for (int i = 0; i < *size; i++) {
        char* token = strtok(orders[i].pizza_ingredients, ",");
        while (token != NULL) {
            // Quitar espacios
            while (*token == ' ') token++;

            int found = 0;
            for (int j = 0; j < count; j++) {
                if (strcmp(ingredientes[j].ingrediente, token) == 0) {
                    ingredientes[j].cantidad += orders[i].quantity;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strncpy(ingredientes[count].ingrediente, token, 100);
                ingredientes[count].cantidad = orders[i].quantity;
                count++;
            }
            token = strtok(NULL, ",");
        }
    }

    int max = 0;
    char mas_vendido[100];
    for (int i = 0; i < count; i++) {
        if (ingredientes[i].cantidad > max) {
            max = ingredientes[i].cantidad;
            strcpy(mas_vendido, ingredientes[i].ingrediente);
        }
    }

    free(ingredientes);
    char* result = malloc(256);
    sprintf(result, "Ingrediente mas vendido: %s", mas_vendido);
    return result;
}

char* hp(int* size, order* orders) {
    typedef struct {
        char categoria[30];
        int cantidad;
    } Categoria;

    Categoria* categorias = malloc((*size) * sizeof(Categoria));
    int count = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(categorias[j].categoria, orders[i].pizza_category) == 0) {
                categorias[j].cantidad += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            strncpy(categorias[count].categoria, orders[i].pizza_category, 30);
            categorias[count].cantidad = orders[i].quantity;
            count++;
        }
    }

    char* result = malloc(512);
    strcpy(result, "Cantidad de pizzas por categoria:\n");
    for (int i = 0; i < count; i++) {
        char linea[100];
        sprintf(linea, "- %s: %d\n", categorias[i].categoria, categorias[i].cantidad);
        strcat(result, linea);
    }

    free(categorias);
    return result;
}
