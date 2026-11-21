#include <stdio.h>
#include <string.h>
#include "funciones.h"

char nombreProducto[5][200];
int cantidad[5];
float tiempo[5];
float precioVenta[5];
int numRecursos = 0;
float costoHora = 0;
char nombresRecursos[20][200];
float costoRecurso[20];
int recursos[5][20];
int registrados = 0;

void leercadena(char *cadena, int n) {
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    cadena[len] = '\0';
}

int buscarProducto(char nombreBuscado[200]) {
    for (int i = 0; i < registrados; i++) {
        if (compararNombres(nombreProducto[i], nombreBuscado) == 0) {
            return i;
        }
    }
    return -1;
}

void validarNumero(int *numero, int min) {
    int l;

    l = scanf("%d", numero);

    while (l != 1 || *numero < min) {
        while (getchar() != '\n');
        if (min == 1) {
            printf("ERROR. Ingrese solo numeros enteros mayores a cero: ");
        } else {
            printf("ERROR. Ingrese cero o un numero entero positivo: ");
        }
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

float sugerirPrecio(int pos) {
    float costoMateriales = 0;

    for (int j = 0; j < numRecursos; j++) {
        costoMateriales += (recursos[pos][j] * costoRecurso[j]);
    }

    return (costoMateriales + (tiempo[pos] * costoHora)) * 1.30;
}

void ingresarProductos() {
    if (registrados >= 5) {
        printf("No se pueden registrar mas productos.\n");
        return;
    }

    if (numRecursos == 0) {
        printf("Ingrese el costo operativo por unidad de tiempo: ");
        validarFloat(&costoHora);
        printf("Ingrese cuantos tipos de recursos tiene: ");
        validarNumero(&numRecursos, 1);

        for (int j = 0; j < numRecursos; j++) {
            printf("Ingrese el nombre del recurso %d: ", j + 1);
            leercadena(nombresRecursos[j], 200);
            printf("Ingrese el costo unitario de %s: ", nombresRecursos[j]);
            validarFloat(&costoRecurso[j]);
        }
    }

    char nombreBuscado[200];
    int cantidadProducto, recursosProducto[20];
    float tiempoProducto, precioSugerido, precioFinal;

    printf("Ingrese el nombre del producto: ");
    leercadena(nombreBuscado, 200);

    if (buscarProducto(nombreBuscado) != -1) {
        printf("El producto ya esta registrado.\n");
        return;
    }

    printf("Ingrese la cantidad del producto: ");
    validarNumero(&cantidadProducto, 1);
    printf("Ingrese el tiempo del producto: ");
    validarFloat(&tiempoProducto);

    for (int j = 0; j < numRecursos; j++) {
        printf("Ingrese la cantidad de %s del producto: ", nombresRecursos[j]);
        validarNumero(&recursosProducto[j], 0);
    }

    strcpy(nombreProducto[registrados], nombreBuscado);
    cantidad[registrados] = cantidadProducto;
    tiempo[registrados] = tiempoProducto;
    for (int j = 0; j < numRecursos; j++) {
        recursos[registrados][j] = recursosProducto[j];
    }

    precioSugerido = sugerirPrecio(registrados);
    printf("Precio sugerido (+30%% ganancia): %.2f\n", precioSugerido);
    printf("Ingrese el precio de venta unitario: ");
    validarFloat(&precioFinal);
    precioVenta[registrados] = precioFinal;

    registrados++;
    printf("Producto registrado exitosamente.\n");
}

void mostrarProductos() {
    if (registrados == 0) {
        printf("No hay productos registrados.\n");
        return;
    }

    printf("Productos registrados:\n");
    printf("#\t\tNombre\t\tCantidad\tTiempo\t\tPrecio");
    for (int j = 0; j < numRecursos; j++) {
        printf("\t\t%s", nombresRecursos[j]);
    }
    printf("\n");

    for (int i = 0; i < registrados; i++) {
        printf("%d\t\t%s\t\t%d\t\t%.2f\t\t%.2f", i + 1, nombreProducto[i], cantidad[i], tiempo[i], precioVenta[i]);
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

    char nombreBuscado[200];
    int posicion, opc;

    printf("Ingrese el nombre del producto que desea editar\n");
    leercadena(nombreBuscado, 200);

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
    printf("5. Precio de venta\n");
    printf(">> ");
    validarNumero(&opc, 1);

    switch (opc) {
        case 1: {
            char nuevoNombre[200];
            printf("Ingrese el nuevo nombre del producto: \n");
            leercadena(nuevoNombre, 200);

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
            validarNumero(&cantidad[posicion], 1);
            printf("Producto editado exitosamente\n");
            break;
        case 3:
            printf("Ingrese el nuevo tiempo del producto: \n");
            validarFloat(&tiempo[posicion]);
            printf("Producto editado exitosamente (Sugerido +30%%: %.2f)\n", sugerirPrecio(posicion));
            break;
        case 4:
            for (int j = 0; j < numRecursos; j++) {
                printf("Ingrese la nueva cantidad de %s: \n", nombresRecursos[j]);
                validarNumero(&recursos[posicion][j], 0);
            }
            printf("Producto editado exitosamente (Sugerido +30%%: %.2f)\n", sugerirPrecio(posicion));
            break;
        case 5:
            printf("Precio sugerido (+30%% ganancia): %.2f\n", sugerirPrecio(posicion));
            printf("Ingrese el nuevo precio de venta: \n");
            validarFloat(&precioVenta[posicion]);
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

    char nombreBuscado[200];
    int posicion;

    printf("Ingrese el nombre del producto que desea eliminar:\n");
    leercadena(nombreBuscado, 200);

    posicion = buscarProducto(nombreBuscado);

    if (posicion == -1) {
        printf("El producto no se encuentra registrado\n");
        return;
    }

    for (int i = posicion; i < registrados - 1; i++) {
        strcpy(nombreProducto[i], nombreProducto[i + 1]);
        cantidad[i] = cantidad[i + 1];
        tiempo[i] = tiempo[i + 1];
        precioVenta[i] = precioVenta[i + 1];
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

    float tiempoTotalRequerido = 0, costoTotalMateriales = 0, ingresosTotales = 0, tiempoDisponible;
    float costoTotalOperativo, costoTotalProduccion, gananciaNeta;
    int recursosTotalesRequeridos[20], recursosDisponibles[20];
    int cumpleRecursos = 1;

    for (int j = 0; j < numRecursos; j++) {
        recursosTotalesRequeridos[j] = 0;
    }
    for (int i = 0; i < registrados; i++) {
        tiempoTotalRequerido += (cantidad[i] * tiempo[i]);
        ingresosTotales += (cantidad[i] * precioVenta[i]);
        for (int j = 0; j < numRecursos; j++) {
            recursosTotalesRequeridos[j] += (cantidad[i] * recursos[i][j]);
        }
    }

    for (int j = 0; j < numRecursos; j++) {
        costoTotalMateriales += (recursosTotalesRequeridos[j] * costoRecurso[j]);
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
        validarNumero(&recursosDisponibles[j], 0);
    }
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
                printf("Faltan %d unidades del recurso %s\n",
                       recursosTotalesRequeridos[j] - recursosDisponibles[j],
                       nombresRecursos[j]);
            }
        }
    }

    costoTotalOperativo = tiempoTotalRequerido * costoHora;
    costoTotalProduccion = costoTotalMateriales + costoTotalOperativo;
    gananciaNeta = ingresosTotales - costoTotalProduccion;

    printf("\n--- ANALISIS FINANCIERO ---\n");
    printf("Costo total de materiales: %.2f\n", costoTotalMateriales);
    printf("Costo operativo total: %.2f\n", costoTotalOperativo);
    printf("Costo total de produccion: %.2f\n", costoTotalProduccion);
    printf("Ingresos estimados por ventas: %.2f\n", ingresosTotales);
    if (gananciaNeta >= 0) {
        printf("Ganancia neta proyectada: %.2f\n", gananciaNeta);
    } else {
        printf("Perdida neta proyectada: -%.2f\n", -gananciaNeta);
    }
}