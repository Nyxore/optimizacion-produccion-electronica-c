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
float porcentajeGanancia = -1;

void leercadena(char *cadena, int n) {
    fgets(cadena, n, stdin);
    int len = strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n') {
        cadena[len - 1] = '\0';
    }
}

int buscarProducto(char nombreBuscado[200]) {
    int pos = 0;
    int esn = 1;

    if (nombreBuscado[0] == '\0') return -1;

    for (int i = 0; nombreBuscado[i] != '\0'; i++) {
        if (nombreBuscado[i] < '0' || nombreBuscado[i] > '9') {
            esn = 0;
            break;
        }
        pos = pos * 10 + (nombreBuscado[i] - '0');
    }

    if (esn == 1) {
        if (pos >= 1 && pos <= registrados) {
            return pos - 1;
        }
        return -1;
    }

    for (int i = 0; i < registrados; i++) {
        if (compararNombres(nombreProducto[i], nombreBuscado) == 0) {
            return i;
        }
    }
    return -1;
}

void validarNumero(int *numero, int min) {
    int l = scanf("%d", numero);
    while (l != 1 || *numero < min) {
        while (getchar() != '\n');
        if (min == 1) {
            printf("  >> ERROR: Ingrese un numero entero mayor a cero: ");
        } else {
            printf("  >> ERROR: Ingrese cero o un numero entero positivo: ");
        }
        l = scanf("%d", numero);
    }
    while (getchar() != '\n');
}

void validarFloat(float *numero) {
    int l = scanf("%f", numero);
    while (l != 1 || *numero <= 0) {
        while (getchar() != '\n');
        printf("  >> ERROR: Ingrese solo valores numericos positivos: ");
        l = scanf("%f", numero);
    }
    while (getchar() != '\n');
}

float sugerirPrecio(int pos) {
    float costoMateriales = 0;
    float tl;

    if (porcentajeGanancia < 0) {
        printf("\nConfiguracion de Ganancia Global:\n");
        printf("Ingrese el porcentaje de ganancia deseado (ej. 30 para 30%%): ");
        validarFloat(&porcentajeGanancia);
    }

    tl = (porcentajeGanancia / 100.0f) + 1.0f;

    for (int j = 0; j < numRecursos; j++) {
        costoMateriales += (recursos[pos][j] * costoRecurso[j]);
    }

    return (costoMateriales + (tiempo[pos] * costoHora)) * tl;
}

void ingresarProductos() {
    if (registrados >= 5) {
        printf("\n[!] ALERTA: Catalogo lleno. Limite de 5 productos alcanzado.\n");
        return;
    }

    if (numRecursos == 0) {
        printf("\n=== CONFIGURACION INICIAL DE LA FABRICA ===\n");
        printf("Ingrese el costo operativo de la fabrica por 1 hora ($): ");
        validarFloat(&costoHora);
        printf("Ingrese la cantidad de tipos de materiales a utilizar en total: ");
        validarNumero(&numRecursos, 1);
        printf("-------------------------------------------\n");

        for (int j = 0; j < numRecursos; j++) {
            do {
                printf("Nombre del material %d (Ej. Lana, Tela, Arcilla): ", j + 1);
                leercadena(nombresRecursos[j], 200);
            } while (nombresRecursos[j][0] == '\0');

            printf("Costo unitario de '%s' ($): ", nombresRecursos[j]);
            validarFloat(&costoRecurso[j]);
            printf("\n");
        }
    }

    char nombreBuscado[200];
    int cantidadProducto, recursosProducto[20];
    float tiempoProducto, precioSugerido, precioFinal;

    printf("\n=== REGISTRO DE NUEVO PRODUCTO ===\n");
    do {
        printf("Nombre del producto (Ej. Peluche, Flor, Vasija): ");
        leercadena(nombreBuscado, 200);
    } while (nombreBuscado[0] == '\0');

    if (buscarProducto(nombreBuscado) != -1) {
        printf("\n[!] El producto '%s' ya se encuentra registrado.\n", nombreBuscado);
        return;
    }

    printf("Cantidad planificada a producir (unidades): ");
    validarNumero(&cantidadProducto, 1);
    printf("Tiempo de produccion por unidad (en horas): ");
    validarFloat(&tiempoProducto);
    printf("-------------------------------------------\n");
    printf("Receta de Materiales para 1 unidad de '%s':\n", nombreBuscado);

    for (int j = 0; j < numRecursos; j++) {
        printf("  - Cantidad de '%s' requerida: ", nombresRecursos[j]);
        validarNumero(&recursosProducto[j], 0);
    }

    strcpy(nombreProducto[registrados], nombreBuscado);
    cantidad[registrados] = cantidadProducto;
    tiempo[registrados] = tiempoProducto;
    for (int j = 0; j < numRecursos; j++) {
        recursos[registrados][j] = recursosProducto[j];
    }

    precioSugerido = sugerirPrecio(registrados);
    printf("\n>> PRECIO DE VENTA SUGERIDO (Incluye materiales, operacion y ganancia): $%.2f\n", precioSugerido);
    printf("Ingrese el Precio de Venta Unitario Final ($): ");
    validarFloat(&precioFinal);
    precioVenta[registrados] = precioFinal;

    registrados++;
    printf("\n[OK] Producto '%s' registrado exitosamente.\n", nombreBuscado);
}

void mostrarProductos() {
    if (registrados == 0) {
        printf("\n[!] No hay productos registrados en el sistema.\n");
        return;
    }

    printf("\n=================================================================================================\n");
   
    printf("%-5s %-20s %-10s %-15s %-12s", "ID", "NOMBRE PRODUCTO", "CANTIDAD", "TIEMPO (Hrs)", "PRECIO ($)");
    for (int j = 0; j < numRecursos; j++) {
        printf(" %-12s", nombresRecursos[j]);
    }
    printf("\n-------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < registrados; i++) {
        printf("%-5d %-20s %-10d %-15.2f %-12.2f",
               i + 1, nombreProducto[i], cantidad[i], tiempo[i], precioVenta[i]);
        for (int j = 0; j < numRecursos; j++) {
            printf(" %-12d", recursos[i][j]);
        }
        printf("\n");
    }
    printf("=================================================================================================\n");
}

void editarProductos() {
    if (registrados == 0) {
        printf("\n[!] No hay productos registrados para editar.\n");
        return;
    }

    char nombreBuscado[200];
    int posicion, opc;

    printf("\n=== EDICION DE PRODUCTO ===\n");
    printf("Ingrese el nombre exacto del producto a modificar: ");
    leercadena(nombreBuscado, 200);

    posicion = buscarProducto(nombreBuscado);

    if (posicion == -1) {
        printf("\n[!] Producto no encontrado en la base de datos.\n");
        return;
    }

    printf("\nSeleccione el campo a editar del producto '%s':\n", nombreProducto[posicion]);
    printf("1. Nombre\n2. Cantidad planificada\n3. Tiempo de fabricacion (Horas)\n4. Receta de Materiales\n5. Precio de Venta al publico\n");
    printf(">> Opcion: ");
    validarNumero(&opc, 1);

    switch (opc) {
        case 1: {
            char nuevoNombre[200];
            printf("\nNuevo nombre del producto: ");
            leercadena(nuevoNombre, 200);
            if (buscarProducto(nuevoNombre) != -1) {
                printf("\n[!] Error: Ya existe un producto con ese nombre.\n");
            } else {
                strcpy(nombreProducto[posicion], nuevoNombre);
                printf("\n[OK] Nombre actualizado correctamente.\n");
            }
            break;
        }
        case 2:
            printf("\nNueva cantidad a producir (unidades): ");
            validarNumero(&cantidad[posicion], 1);
            printf("\n[OK] Cantidad actualizada.\n");
            break;
        case 3:
            printf("\nNuevo tiempo de fabricacion (en horas): ");
            validarFloat(&tiempo[posicion]);
            printf("\n[OK] Tiempo actualizado. (Nuevo precio sugerido: $%.2f)\n", sugerirPrecio(posicion));
            break;
        case 4:
            printf("\n");
            for (int j = 0; j < numRecursos; j++) {
                printf("Nueva cantidad de '%s' requerida: ", nombresRecursos[j]);
                validarNumero(&recursos[posicion][j], 0);
            }
            printf("\n[OK] Materiales actualizados. (Nuevo precio sugerido: $%.2f)\n", sugerirPrecio(posicion));
            break;
        case 5:
            printf("\nPrecio sugerido por el sistema: $%.2f\n", sugerirPrecio(posicion));
            printf("Nuevo precio de venta final ($): ");
            validarFloat(&precioVenta[posicion]);
            printf("\n[OK] Precio actualizado exitosamente.\n");
            break;
        default:
            printf("\n[!] Opcion no valida.\n");
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
        printf("\n[!] No hay productos registrados para eliminar.\n");
        return;
    }

    char nombreBuscado[200];
    int posicion;

    printf("\n=== ELIMINACION DE PRODUCTO ===\n");
    printf("Ingrese el nombre del producto que desea eliminar: ");
    leercadena(nombreBuscado, 200);

    posicion = buscarProducto(nombreBuscado);

    if (posicion == -1) {
        printf("\n[!] El producto no se encuentra registrado.\n");
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
    printf("\n[OK] Producto eliminado del catalogo exitosamente.\n");
}

void calcularProduccion() {
    if (registrados == 0) {
        printf("\n[!] Registre productos primero para realizar los calculos.\n");
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

    printf("\n=======================================================\n");
    printf("        REPORTE GERENCIAL: PRODUCCION Y FINANZAS\n");
    printf("=======================================================\n");
    printf("[1] REQUERIMIENTOS TOTALES DE PRODUCCION\n");
    printf("  >> Tiempo Total Operativo : %.2f horas\n", tiempoTotalRequerido);
    printf("  >> Materiales Totales Requeridos:\n");
    for (int j = 0; j < numRecursos; j++) {
        printf("     - %-15s : %d unidades\n", nombresRecursos[j], recursosTotalesRequeridos[j]);
    }

    printf("\n-------------------------------------------------------\n");
    printf("[2] DISPONIBILIDAD DE PLANTA (VALIDACION)\n");
    printf("  Ingrese las HORAS de produccion disponibles: ");
    validarFloat(&tiempoDisponible);

    for (int j = 0; j < numRecursos; j++) {
        printf("  Ingrese la cantidad en bodega disponible de '%s': ", nombresRecursos[j]);
        validarNumero(&recursosDisponibles[j], 0);
        if (recursosTotalesRequeridos[j] > recursosDisponibles[j]) {
            cumpleRecursos = 0;
        }
    }
    
    printf("\n-------------------------------------------------------\n");
    printf("[3] ANALISIS DE FACTIBILIDAD LOGISTICA\n");

    if (tiempoTotalRequerido <= tiempoDisponible && cumpleRecursos == 1) {
        printf("  >>> ESTADO: [VIABLE] La fabrica SI puede cumplir con la demanda.\n");
    } else {
        printf("  >>> ESTADO: [NO VIABLE] La fabrica NO puede cumplir con la demanda.\n");
        if (tiempoTotalRequerido > tiempoDisponible) {
            printf("      - DEFICIT TIEMPO: Faltan %.2f horas de produccion.\n", tiempoTotalRequerido - tiempoDisponible);
        }
        for (int j = 0; j < numRecursos; j++) {
            if (recursosTotalesRequeridos[j] > recursosDisponibles[j]) {
                printf("      - DEFICIT MATERIAL: Faltan %d unidades del recurso '%s'.\n",
                       recursosTotalesRequeridos[j] - recursosDisponibles[j], nombresRecursos[j]);
            }
        }
    }

    costoTotalOperativo = tiempoTotalRequerido * costoHora;
    costoTotalProduccion = costoTotalMateriales + costoTotalOperativo;
    gananciaNeta = ingresosTotales - costoTotalProduccion;

    printf("\n-------------------------------------------------------\n");
    printf("[4] ANALISIS FINANCIERO Y RENTABILIDAD\n");
    printf("  %-32s $%-10.2f\n", "Costo Total de Materiales:", costoTotalMateriales);
    printf("  %-32s $%-10.2f\n", "Costo Operativo Total (Horas):", costoTotalOperativo);
    printf("  %-32s $%-10.2f\n", "COSTO TOTAL DE PRODUCCION:", costoTotalProduccion);
    printf("  %-32s $%-10.2f\n", "INGRESOS ESTIMADOS POR VENTAS:", ingresosTotales);
    
    printf("\n");
    if (gananciaNeta >= 0) {
        printf("  >>> GANANCIA NETA PROYECTADA:    $%.2f <<<\n", gananciaNeta);
    } else {
        printf("  >>> PERDIDA NETA PROYECTADA:    -$%.2f <<<\n", -gananciaNeta);
    }
    printf("=======================================================\n");
}