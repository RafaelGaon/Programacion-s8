#include <stdio.h>
#include <string.h>

#define MAX 5


void ingresarProductos(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int *n);                       
void mostrarProductos(char nombres[][50], int cantidades[],  float tiempos[], float recursos[], int n);                    
int buscarProducto(char nombres[][50], int n, char nombre[]);
void editarProducto(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int n);
void eliminarProducto(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int *n);
void calcularProduccion(int cantidades[], float tiempos[], float recursos[], int n);

int main() {

    char nombres[MAX][50];
    int cantidades[MAX];
    float tiempos[MAX];
    float recursos[MAX];

    int n = 0;
    int opcion;

    do {

        printf("\n====== FABRICA ELECTRONICA ======\n");
        printf("1. Ingresar productos\n");
        printf("2. Mostrar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Calcular produccion\n");
        printf("6. Salir\n");

        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {

            case 1:
                ingresarProductos(nombres, cantidades,
                                  tiempos, recursos, &n);
                break;

            case 2:
                mostrarProductos(nombres, cantidades,
                                 tiempos, recursos, n);
                break;

            case 3:
                editarProducto(nombres, cantidades,
                               tiempos, recursos, n);
                break;

            case 4:
                eliminarProducto(nombres, cantidades,
                                 tiempos, recursos, &n);
                break;

            case 5:
                calcularProduccion(cantidades, tiempos,
                                   recursos, n);
                break;

            case 6:
                printf("\nFin del programa.\n");
                break;

            default:
                printf("\nOpcion incorrecta.\n");
        }

    } while (opcion != 6);

    return 0;
}


void ingresarProductos(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int *n){
                        

    int cantidad;

    if (*n == MAX) {
        printf("\nNo hay espacio para mas productos.\n");
        return;
    }

    printf("\n Productos a ingresar: ");
    scanf("%d", &cantidad);
    getchar();

    if (cantidad <= 0 || cantidad > MAX - *n) {
        printf("\nCantidad no valida. Espacios disponibles: %d\n", MAX - *n);
        return;
    }

    for (int i = 0; i < cantidad; i++) {

        printf("\nNombre del producto: ");
        fgets(nombres[*n], 50, stdin);
        nombres[*n][strcspn(nombres[*n], "\n")] = '\0';

        printf("Cantidad demandada: ");
        scanf("%d", &cantidades[*n]);

        printf("Tiempo por unidad: ");
        scanf("%f", &tiempos[*n]);

        printf("Recursos por unidad: ");
        scanf("%f", &recursos[*n]);

        getchar();

        (*n)++;

        printf("\nProducto registrado.\n");
    }
}


void mostrarProductos(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int n) {
                    

    if (n == 0) {
        printf("\nNo hay productos registrados.\n");
        return;
    }

    for (int i = 0; i < n; i++) {

        printf("\nProducto: %s\n", nombres[i]);
        printf("Cantidad: %d\n", cantidades[i]);
        printf("Tiempo por unidad: %.2f\n", tiempos[i]);
        printf("Recursos por unidad: %.2f\n", recursos[i]);
    }
}

int buscarProducto(char nombres[][50], int n, char nombre[]) {

    for (int i = 0; i < n; i++) {

        if (strcmp(nombres[i], nombre) == 0) {
            return i;
        }
    }

    return -1;
}


void editarProducto(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int n) {
                    

    char nombre[50];
    int posicion;

    printf("\nIngrese el nombre del producto que desea editar: ");
    fgets(nombre, 50, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    posicion = buscarProducto(nombres, n, nombre);

    if (posicion == -1) {
        printf("\nProducto no encontrado.\n");
        return;
    }

    printf("\nIngrese los nuevos datos:\n");

    printf("Nuevo nombre: ");
    fgets(nombres[posicion], 50, stdin);
    nombres[posicion][strcspn(nombres[posicion], "\n")] = '\0';

    printf("Nueva cantidad: ");
    scanf("%d", &cantidades[posicion]);

    printf("Nuevo tiempo por unidad: ");
    scanf("%f", &tiempos[posicion]);

    printf("Nuevos recursos por unidad: ");
    scanf("%f", &recursos[posicion]);

    getchar();

    printf("\nProducto actualizado.\n");
}


void eliminarProducto(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int *n) {
                      
    char nombre[50];
    int posicion;

    printf("\nIngrese el nombre del producto que desea eliminar: ");
    fgets(nombre, 50, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    posicion = buscarProducto(nombres, *n, nombre);

    if (posicion == -1) {
        printf("\nProducto no encontrado.\n");
        return;
    }

    for (int i = posicion; i < *n - 1; i++) {

        strcpy(nombres[i], nombres[i + 1]);

        cantidades[i] = cantidades[i + 1];
        tiempos[i] = tiempos[i + 1];
        recursos[i] = recursos[i + 1];
    }

    (*n)--;

    printf("\nProducto eliminado.\n");
}


void calcularProduccion(int cantidades[], float tiempos[], float recursos[], int n) {
                        

    float tiempoTotal = 0;
    float recursosTotal = 0;

    float tiempoDisponible;
    float recursosDisponibles;

    if (n == 0) {
        printf("\nNo hay productos registrados.\n");
        return;
    }

    for (int i = 0; i < n; i++) {

        tiempoTotal += cantidades[i] * tiempos[i];

        recursosTotal += cantidades[i] * recursos[i];
    }

    printf("\nTiempo total necesario: %.2f minutos\n", tiempoTotal);
    printf("Recursos necesarios: %.2f\n", recursosTotal);

    printf("\nIngrese el tiempo disponible: ");
    scanf("%f", &tiempoDisponible);

    printf("Ingrese los recursos disponibles: ");
    scanf("%f", &recursosDisponibles);

    if (tiempoTotal <= tiempoDisponible && recursosTotal <= recursosDisponibles) {
       

        printf("\nSI SE PUEDE CUMPLIR CON LA DEMANDA.\n");

    } else {

        printf("\nNO SE PUEDE CUMPLIR CON LA DEMANDA.\n");

        if (tiempoTotal > tiempoDisponible) {
            printf("Tiempo insuficiente.\n");
        }

        if (recursosTotal > recursosDisponibles) {
            printf("Recursos insuficientes.\n");
        }
    }
}