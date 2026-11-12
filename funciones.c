#include <stdio.h>
#include <string.h>
#include "funciones.h"

char nombreProducto[5][20];
int cantidad[5];
float tiempo[5];
int recursos[5];
int registrados = 0;

int buscarProducto(char nombreBuscado[20]) {
    for (int i = 0; i < registrados; i++) {
        if (compararNombres(nombreProducto[i], nombreBuscado) == 0) {
            return i;
        }
    }
    return -1;
}

void ingresarProductos() {
    if (registrados >= 5) {
        printf("No se pueden registrar mas productos.\n");
        return;
    }

    char nombreBuscado[20];
    int cantidadProducto;
    float tiempoProducto;
    int recursosProducto;

    printf("Ingrese el nombre del producto: ");
    scanf(" %19s", nombreBuscado);
    while (getchar() != '\n');

    if (buscarProducto(nombreBuscado) != -1) {
        printf("El producto ya esta registrado.\n");
        return;
    }

    printf("Ingrese la cantidad del producto: ");
    validarNumero(&cantidadProducto);

    printf("Ingrese el tiempo del producto: ");
    validarFloat(&tiempoProducto);

    printf("Ingrese los recursos del producto: ");
    validarNumero(&recursosProducto);

    strcpy(nombreProducto[registrados], nombreBuscado);
    cantidad[registrados] = cantidadProducto;
    tiempo[registrados] = tiempoProducto;
    recursos[registrados] = recursosProducto;

    registrados++;

    printf("Producto registrado exitosamente.\n");
}

void validarNumero(int *numero) {
    int l;

    l = scanf("%d", numero);

    while (l != 1 || *numero <= 0) {
        while (getchar() != '\n');
        printf("ERROR. Ingrese solo numeros enteros: ");
        l = scanf("%d", numero);
    }
    while (getchar() != '\n');
}

void validarFloat(float *numero) {
    int l;

    l = scanf("%f", numero);

    while (l != 1 || *numero <= 0) {
        while (getchar() != '\n');
        printf("ERROR. Ingrese solo numeros positivos: ");
        l = scanf("%f", numero);
    }
    while (getchar() != '\n');
}

void mostrarProductos() {
    if (registrados == 0) {
        printf("No hay productos registrados.\n");
        return;
    }

    printf("Productos registrados:\n");
    printf("#\t\tNombre\t\tCantidad\t\tTiempo\t\tRecursos\n");
    for (int i = 0; i < registrados; i++) {
        printf("%d\t\t%s\t\t%d\t\t%.2f\t\t%d\n", i + 1, nombreProducto[i], cantidad[i], tiempo[i], recursos[i]);
    }
}

void editarProductos() {
    if (registrados == 0) {
        printf("No hay productos registrados\n");
        return;
    }

    char nombreBuscado[20];
    int posicion;
    int opc;

    printf("Ingrese el nombre del producto que desea editar\n");
    scanf(" %19s", nombreBuscado);
    while (getchar() != '\n');

    posicion = buscarProducto(nombreBuscado);

    if (posicion == -1) {
        printf("El producto no se encuentra registrado\n");
        return;
    }

    printf("¿Que dato desea editar?\n");
    printf("1. Nombre\n");
    printf("2. Cantidad\n");
    printf("3. Tiempo\n");
    printf("4. Recursos\n");
    printf(">> ");
    validarNumero(&opc);

    switch (opc) {
        case 1: {
            char nuevoNombre[20];
            printf("Ingrese el nuevo nombre del producto: \n");
            scanf(" %19s", nuevoNombre);
            while (getchar() != '\n');

            if (buscarProducto(nuevoNombre) != -1) {
                printf("El producto ya esta registrado\n");
            } else {
                strcpy(nombreProducto[posicion], nuevoNombre);
                printf("Producto editado exitosamente\n");
            }
            break;
        }
        case 2:
            printf("Ingrese la nueva cantidad del producto: \n");
            validarNumero(&cantidad[posicion]);
            printf("Producto editado exitosamente\n");
            break;
        case 3:
            printf("Ingrese el nuevo tiempo del producto: \n");
            validarFloat(&tiempo[posicion]);
            printf("Producto editado exitosamente\n");
            break;
        case 4:
            printf("Ingrese los nuevos recursos del producto: \n");
            validarNumero(&recursos[posicion]);
            printf("Producto editado exitosamente\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
    }
}

int compararNombres(char *cadena1, char *cadena2) {
    int i = 0;

    while (cadena1[i] == cadena2[i] && cadena1[i] != '\0' && cadena2[i] != '\0') {
        i++;
    }

    return cadena1[i] - cadena2[i];
}

void eliminarProductos() {
    if (registrados == 0) {
        printf("No hay productos registrados para eliminar\n");
        return;
    }

    char nombreBuscado[20];
    int posicion;

    printf("Ingrese el nombre del producto que desea eliminar:\n");
    scanf(" %19s", nombreBuscado);
    while (getchar() != '\n');

    posicion = buscarProducto(nombreBuscado);

    if (posicion == -1) {
        printf("El producto no se encuentra registrado\n");
        return;
    }

    for (int i = posicion; i < registrados - 1; i++) {
        strcpy(nombreProducto[i], nombreProducto[i + 1]);
        cantidad[i] = cantidad[i + 1];
        tiempo[i] = tiempo[i + 1];
        recursos[i] = recursos[i + 1];
    }

    registrados--;

    printf("Producto eliminado\n");
}

void calcularProduccion() {
    if (registrados == 0) {
        printf("No hay productos registrados para calcular la produccion\n");
        return;
    }

    float tiempoTotalRequerido = 0;
    int recursosTotalesRequeridos = 0;

    float tiempoDisponible;
    int recursosDisponibles;

    for (int i = 0; i < registrados; i++) {
        tiempoTotalRequerido += (cantidad[i] * tiempo[i]);
        recursosTotalesRequeridos += (cantidad[i] * recursos[i]);
    }

    printf("\n--- RESULTADOS DE PRODUCCION ---\n");
    printf("Tiempo total requerido: %.2f\n", tiempoTotalRequerido);
    printf("Recursos totales requeridos: %d\n", recursosTotalesRequeridos);

    printf("\n--- DISPONIBILIDAD DE LA FABRICA ---\n");
    printf("Ingrese el tiempo de produccion disponible: ");
    validarFloat(&tiempoDisponible);

    printf("Ingrese los recursos disponibles: ");
    validarNumero(&recursosDisponibles);

    printf("\n--- ANALISIS DE FACTIBILIDAD ---\n");
    if (tiempoTotalRequerido <= tiempoDisponible && recursosTotalesRequeridos <= recursosDisponibles) {
        printf("La fabrica si puede cumplir con la demanda.\n");
    } else {
        printf("La fabrica no puede cumplir con la demanda.\n");

        if (tiempoTotalRequerido > tiempoDisponible) {
            printf("Faltan %.2f unidades de tiempo\n", tiempoTotalRequerido - tiempoDisponible);
        }
        if (recursosTotalesRequeridos > recursosDisponibles) {
            printf("Faltan %d unidades de recursos\n", recursosTotalesRequeridos - recursosDisponibles);
        }
    }
}