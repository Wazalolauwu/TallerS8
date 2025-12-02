#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTS 5
#define NAME_LEN 50

void limpiar_buffer();
int buscar_producto(char names[][NAME_LEN], int count, const char *buscado);
void agregar_producto(char names[][NAME_LEN], double tiempoUnidad[], int recursosUnidad[], int cantidadDemandada[], int *count);
void editar_producto(char names[][NAME_LEN], double tiempoUnidad[], int recursosUnidad[], int cantidadDemandada[], int count);
void eliminar_producto(char names[][NAME_LEN], double tiempoUnidad[], int recursosUnidad[], int cantidadDemandada[], int *count);
void mostrar_productos(char names[][NAME_LEN], double tiempoUnidad[], int recursosUnidad[], int cantidadDemandada[], int count);
double calcular_tiempo_total(double tiempoUnidad[], int cantidadDemandada[], int count);
int calcular_recursos_totales(int recursosUnidad[], int cantidadDemandada[], int count);
void verificar_capacidad(double tiempoUnidad[], int recursosUnidad[], int cantidadDemandada[], int count);

#endif
