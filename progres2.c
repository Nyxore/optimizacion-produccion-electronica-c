#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[]) {
    int opcion;

    do {
        printf("\n-----------MENU-------------\n");
        printf("1. Ingresar productos.\n");
        printf("2. Mostrar productos.\n");
        printf("3. Editar productos.\n");
        printf("4. Eliminar producto.\n");
        printf("5. Calcular produccion y demanda.\n");
        printf("6. salir.\n");
        printf(">> ");

        validarNumero(&opcion);

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
                printf("\nSaliendo......\n");
                return 0;
            default:
                printf("\nERROR. Ingrese una opcion valida\n");
                break;
        }

    } while (opcion != 6);

    return 0;
}
