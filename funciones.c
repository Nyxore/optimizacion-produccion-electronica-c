#include <stdio.h>
#include <string.h>
#include "funciones.h"

char nombreProducto[5][20];
int cantidad[5];
float tiempo[5];
int numRecursos = 0;
char nombresRecursos[20][20];
int recursos[5][20];
int registrados = 0;

void leercadena(char *cadena, int n) {
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    cadena[len] = '\0';
}

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

    if (numRecursos == 0) {
        printf("Ingrese cuantos tipos de recursos tiene: ");
        validarNumero(&numRecursos);
        for (int j = 0; j < numRecursos; j++) {
            printf("Ingrese el nombre del recurso %d: ", j + 1);
            leercadena(nombresRecursos[j], 20);
        }
    }

    char nombreBuscado[20];
    int cantidadProducto;
    float tiempoProducto;
    int recursosProducto[20];

    printf("Ingrese el nombre del producto: ");
    leercadena(nombreBuscado, 20);

    if (buscarProducto(nombreBuscado) != -1) {
        printf("El producto ya esta registrado.\n");
        return;
    }

    printf("Ingrese la cantidad del producto: ");
    validarNumero(&cantidadProducto);

    printf("Ingrese el tiempo del producto: ");
    validarFloat(&tiempoProducto);

    for (int j = 0; j < numRecursos; j++) {
        printf("Ingrese la cantidad de %s del producto: ", nombresRecursos[j]);
        validarNumero(&recursosProducto[j]);
    }

    strcpy(nombreProducto[registrados], nombreBuscado);
    cantidad[registrados] = cantidadProducto;
    tiempo[registrados] = tiempoProducto;
    for (int j = 0; j < numRecursos; j++) {
        recursos[registrados][j] = recursosProducto[j];
    }

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
    printf("#\t\tNombre\t\tCantidad\t\tTiempo");
    for (int j = 0; j < numRecursos; j++) {
        printf("\t\t%s", nombresRecursos[j]);
    }
    printf("\n");

    for (int i = 0; i < registrados; i++) {
        printf("%d\t\t%s\t\t%d\t\t%.2f", i + 1, nombreProducto[i], cantidad[i], tiempo[i]);
        for (int j = 0; j < numRecursos; j++) {
            printf("\t\t%d", recursos[i][j]);
        }
        printf("\n");
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
    leercadena(nombreBuscado, 20);

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
            leercadena(nuevoNombre, 20);

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
            for (int j = 0; j < numRecursos; j++) {
                printf("Ingrese la nueva cantidad de %s: \n", nombresRecursos[j]);
                validarNumero(&recursos[posicion][j]);
            }
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
    leercadena(nombreBuscado, 20);

    posicion = buscarProducto(nombreBuscado);

    if (posicion == -1) {
        printf("El producto no se encuentra registrado\n");
        return;
    }

    for (int i = posicion; i < registrados - 1; i++) {
        strcpy(nombreProducto[i], nombreProducto[i + 1]);
        cantidad[i] = cantidad[i + 1];
        tiempo[i] = tiempo[i + 1];
        for (int j = 0; j < numRecursos; j++) {
            recursos[i][j] = recursos[i + 1][j];
        }
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
    float tiempoDisponible;
    int recursosTotalesRequeridos[20];
    int recursosDisponibles[20];

    for (int j = 0; j < numRecursos; j++) {
        recursosTotalesRequeridos[j] = 0;
    }

    for (int i = 0; i < registrados; i++) {
        tiempoTotalRequerido += (cantidad[i] * tiempo[i]);
        for (int j = 0; j < numRecursos; j++) {
            recursosTotalesRequeridos[j] += (cantidad[i] * recursos[i][j]);
        }
    }

    printf("\n--- RESULTADOS DE PRODUCCION ---\n");
    printf("Tiempo total requerido: %.2f\n", tiempoTotalRequerido);
    printf("Recursos totales requeridos:\n");
    for (int j = 0; j < numRecursos; j++) {
        printf("- %s: %d\n", nombresRecursos[j], recursosTotalesRequeridos[j]);
    }

    printf("\n--- DISPONIBILIDAD DE LA FABRICA ---\n");
    printf("Ingrese el tiempo de produccion disponible: ");
    validarFloat(&tiempoDisponible);

    for (int j = 0; j < numRecursos; j++) {
        printf("Ingrese los recursos disponibles de %s: ", nombresRecursos[j]);
        validarNumero(&recursosDisponibles[j]);
    }

    int cumpleRecursos = 1;
    for (int j = 0; j < numRecursos; j++) {
        if (recursosTotalesRequeridos[j] > recursosDisponibles[j]) {
            cumpleRecursos = 0;
        }
    }

    printf("\n--- ANALISIS DE FACTIBILIDAD ---\n");
    if (tiempoTotalRequerido <= tiempoDisponible && cumpleRecursos == 1) {
        printf("La fabrica si puede cumplir con la demanda.\n");
    } else {
        printf("La fabrica no puede cumplir con la demanda.\n");

        if (tiempoTotalRequerido > tiempoDisponible) {
            printf("Faltan %.2f unidades de tiempo\n", tiempoTotalRequerido - tiempoDisponible);
        }
        for (int j = 0; j < numRecursos; j++) {
            if (recursosTotalesRequeridos[j] > recursosDisponibles[j]) {
                printf("Faltan %d unidades de %s\n", 
                       recursosTotalesRequeridos[j] - recursosDisponibles[j], 
                       nombresRecursos[j]);
            }
        }
    }
}