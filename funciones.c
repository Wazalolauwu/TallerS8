#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int buscar_producto(char names[][NAME_LEN], int count, const char *buscado) {
    for (int i = 0; i < count; i++) {
        if (strcmp(names[i], buscado) == 0) {
            return i;
        }
    }
    return -1;
}

void agregar_producto(char names[][NAME_LEN], double tiempoUnidad[], int recursosUnidad[], int cantidadDemandada[], int *count) {
    if (*count >= MAX_PRODUCTS) {
        printf("Máximo de productos alcanzado.\n");
        return;
    }

    char tempName[NAME_LEN];
    double t;
    int r, q;

    printf("Nombre del producto: ");
    fgets(tempName, NAME_LEN, stdin);
    tempName[strcspn(tempName, "\n")] = '\0';

    if (buscar_producto(names, *count, tempName) != -1) {
        printf("Ese nombre ya existe.\n");
        return;
    }

    printf("Tiempo por unidad: ");
    scanf("%lf", &t);
    printf("Recursos por unidad: ");
    scanf("%d", &r);
    printf("Cantidad demandada: ");
    scanf("%d", &q);
    limpiar_buffer();

    strncpy(names[*count], tempName, NAME_LEN);
    tiempoUnidad[*count] = t;
    recursosUnidad[*count] = r;
    cantidadDemandada[*count] = q;

    (*count)++;
    printf("Producto agregado.\n");
}

void editar_producto(char names[][NAME_LEN], double tiempoUnidad[], int recursosUnidad[], int cantidadDemandada[], int count) {
    if (count == 0) {
        printf("No hay productos.\n");
        return;
    }

    char buscado[NAME_LEN], linea[100];
    printf("Nombre del producto a editar: ");
    fgets(buscado, NAME_LEN, stdin);
    buscado[strcspn(buscado, "\n")] = '\0';

    int idx = buscar_producto(names, count, buscado);
    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    printf("Nuevo nombre (ENTER para no cambiar): ");
    fgets(linea, 100, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    if (strlen(linea) > 0) {
        strncpy(names[idx], linea, NAME_LEN);
    }

    printf("Nuevo tiempo (-1 para no cambiar): ");
    fgets(linea, 100, stdin);
    double t = atof(linea);
    if (t > 0) tiempoUnidad[idx] = t;

    printf("Nuevos recursos (-1 para no cambiar): ");
    fgets(linea, 100, stdin);
    int r = atoi(linea);
    if (r >= 0) recursosUnidad[idx] = r;

    printf("Nueva cantidad (-1 para no cambiar): ");
    fgets(linea, 100, stdin);
    int q = atoi(linea);
    if (q >= 0) cantidadDemandada[idx] = q;

    printf("Producto editado.\n");
}

void eliminar_producto(char names[][NAME_LEN], double tiempoUnidad[], int recursosUnidad[], int cantidadDemandada[], int *count) {
    if (*count == 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }

    char buscado[NAME_LEN];
    printf("Producto a eliminar: ");
    fgets(buscado, NAME_LEN, stdin);
    buscado[strcspn(buscado, "\n")] = '\0';

    int idx = buscar_producto(names, *count, buscado);
    if (idx == -1) {
        printf("No encontrado.\n");
        return;
    }

    for (int i = idx; i < (*count) - 1; i++) {
        strcpy(names[i], names[i+1]);
        tiempoUnidad[i] = tiempoUnidad[i+1];
        recursosUnidad[i] = recursosUnidad[i+1];
        cantidadDemandada[i] = cantidadDemandada[i+1];
    }

    (*count)--;
    printf("Producto eliminado.\n");
}

void mostrar_productos(char names[][NAME_LEN], double tiempoUnidad[], int recursosUnidad[], int cantidadDemandada[], int count) {
    if (count == 0) {
        printf("No hay productos.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nProducto %d: %s\n", i + 1, names[i]);
        printf("Tiempo/u: %.2f | Recursos/u: %d | Cantidad: %d\n",
               tiempoUnidad[i], recursosUnidad[i], cantidadDemandada[i]);
    }

    double tiempoTotal = calcular_tiempo_total(tiempoUnidad, cantidadDemandada, count);
    int recursosTotales = calcular_recursos_totales(recursosUnidad, cantidadDemandada, count);

    printf("\nTiempo total: %.2f\n", tiempoTotal);
    printf("Recursos totales: %d\n", recursosTotales);
}

double calcular_tiempo_total(double tiempoUnidad[], int cantidadDemandada[], int count) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += tiempoUnidad[i] * cantidadDemandada[i];
    }
    return total;
}

int calcular_recursos_totales(int recursosUnidad[], int cantidadDemandada[], int count) {
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += recursosUnidad[i] * cantidadDemandada[i];
    }
    return total;
}

void verificar_capacidad(double tiempoUnidad[], int recursosUnidad[], int cantidadDemandada[], int count) {
    double tiempoDisponible;
    int recursosDisponibles;

    printf("Tiempo disponible: ");
    scanf("%lf", &tiempoDisponible);
    printf("Recursos disponibles: ");
    scanf("%d", &recursosDisponibles);
    limpiar_buffer();

    double tTotal = calcular_tiempo_total(tiempoUnidad, cantidadDemandada, count);
    int rTotal = calcular_recursos_totales(recursosUnidad, cantidadDemandada, count);

    printf("\nTiempo requerido: %.2f\nRecursos requeridos: %d\n", tTotal, rTotal);

    if (tTotal <= tiempoDisponible && rTotal <= recursosDisponibles) {
        printf("La fábrica SÍ puede cumplir con la demanda.\n");
    } else {
        printf("NO puede cumplir con la demanda.\n");
    }
}