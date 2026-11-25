#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[]) {
    int opcion;

    do {
        printf("\n=============================================\n");
        printf("   SISTEMA DE PRODUCCION Y OPTIMIZACION\n");
        printf("=============================================\n");
        printf(" 1. Ingresar nuevos productos (Ficha Tecnica)\n");
        printf(" 2. Mostrar listado de productos\n");
        printf(" 3. Editar datos de un producto\n");
        printf(" 4. Eliminar producto del catalogo\n");
        printf(" 5. Evaluar produccion, viabilidad y finanzas\n");
        printf(" 6. Salir del sistema\n");
        printf("=============================================\n");
        printf(">> Seleccione una opcion: ");

        validarNumero(&opcion, 1);

        switch (opcion) {
            case 1:
                ingresarProductos();
                break;
            case 2:
                mostrarProductos();
                break;
            case 3:
                editarProductos();
                break;
            case 4:
                eliminarProductos();
                break;
            case 5:
                calcularProduccion();
                break;
            case 6:
                printf("\nSaliendo del sistema. Hasta pronto!\n\n");
                return 0;
            default:
                printf("\n[!] ERROR. Ingrese una opcion valida (1 - 6)\n");
                break;
        }

    } while (opcion != 6);

    return 0;
}