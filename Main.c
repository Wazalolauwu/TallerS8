#include <stdio.h>
#include "funciones.h"

int main() {
    char names[MAX_PRODUCTS][NAME_LEN];
    double tiempoUnidad[MAX_PRODUCTS];
    int recursosUnidad[MAX_PRODUCTS];
    int cantidadDemandada[MAX_PRODUCTS];
    int count = 0;
    int opcion;

    do {
        printf("\n=== MENÚ PRINCIPAL ===\n");
        printf("1. Ingresar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Mostrar productos\n");
        printf("5. Verificar capacidad\n");
        printf("6. Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        limpiar_buffer();

        switch (opcion) {
            case 1:
                agregar_producto(names, tiempoUnidad, recursosUnidad, cantidadDemandada, &count);
                break;
            case 2:
                editar_producto(names, tiempoUnidad, recursosUnidad, cantidadDemandada, count);
                break;
            case 3:
                eliminar_producto(names, tiempoUnidad, recursosUnidad, cantidadDemandada, &count);
                break;
            case 4:
                mostrar_productos(names, tiempoUnidad, recursosUnidad, cantidadDemandada, count);
                break;
            case 5:
                verificar_capacidad(tiempoUnidad, recursosUnidad, cantidadDemandada, count);
                break;
            case 6:
                printf("Finalizando programa...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }

    } while (opcion != 6);

    return 0;
}