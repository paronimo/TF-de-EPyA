#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {                //Estructura pricipal de crear tarea
    char titulo[20];
    char descripcion[200];
    int dificultad;
    int dia, mes, anio;
    int preguntaFecha;
    int estadoSeleccionado;
    char estado[20];
} Tarea;
                               //Todos los void guardados
void crearTarea();
void pedirTitulo(Tarea *t);
void pedirDescripcion(Tarea *t);
void pedirDificultad(Tarea *t);
void pedirEstado(Tarea *t);
void pedirFechaVencimiento(Tarea *t);
void mostrarResumen(Tarea t);
int main(){
    int opc;
     do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Modulo de suma\n");
        printf("2. Ver mis tareas\n");
        printf("3. Crear tarea\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);
	 switch(opc)
	 {
	case 0: printf ("\n Gracias por llamarme para nada\n");
	break;
	case 1: printf ("\n ingresaste a al modulo de suma \n \n");
	break;
	case 2: printf ("\n ingresaste al modulo de resta \n \n");
	break;
	case 3:
                crearTarea();
                break;
            default:
                printf("  Opción inválida. Intente nuevamente.\n");
        }
    } while (opc != 0);

    printf("Adios!\n");
    return 0;
    }



void crearTarea() {                      //Funcion de CREAR TAREA
    Tarea tarea;
    int confirm;
 system("cls");
    printf("\nEstas creando una tarea:\n");

    pedirTitulo(&tarea);
    pedirDescripcion(&tarea);
    pedirDificultad(&tarea);
    pedirEstado(&tarea);
    pedirFechaVencimiento(&tarea);
    system("cls");
    mostrarResumen(tarea);

    printf("¿Confirmar tarea? SI (1) / NO (2): ");
    scanf("%d", &confirm);

    if (confirm == 1) {
        printf("¡Se guardó la tarea exitosamente!\n\n\n");
        system("cls");
    } else {
        printf("Tarea cancelada. Puedes volver a crearla.\n");
    }
}

void pedirTitulo(Tarea *t) {                  //Titulo
    printf("\nDe un titulo a esta tarea: ");
    scanf("%s", t->titulo);
    while (getchar() != '\n');
}

void pedirDescripcion(Tarea *t) {              //Descripcion//
    printf("\nDe una descripcion a esta tarea: ");
    fgets(t->descripcion, sizeof(t->descripcion), stdin);
    t->descripcion[strcspn(t->descripcion, "\n")] = 0;
}

void pedirDificultad(Tarea *t) {                //Dificultad//
    do {
        printf("\n1 = § = Facilisimo\n2 = §§ = Facil\n3 = §§§ = Medio\n4 = §§§§ = Complicado\n5 = §§§§§ = Dificilisimo");
        printf("\nSeleccione su dificultad: ");
        scanf("%d", &t->dificultad);

        if (t->dificultad < 1 || t->dificultad > 5) {
            printf("?? ¡Seleccione un número entre 1 y 5!\n");
        }
    } while (t->dificultad < 1 || t->dificultad > 5);
}

void pedirEstado(Tarea *t) {                   //Estado
    printf("\n ¿En que estado desea dejar la tarea?\n");
    printf("1 = Pendiente\n2 = En curso\n3 = Terminada\nSeleccione: ");
    scanf("%d", &t->estadoSeleccionado);

    while (t->estadoSeleccionado < 1 || t->estadoSeleccionado > 3) {
        printf(" Opción inválida. Intente nuevamente: ");
        scanf("%d", &t->estadoSeleccionado);
    }

    switch (t->estadoSeleccionado) {
        case 1: strcpy(t->estado, "Pendiente"); break;
        case 2: strcpy(t->estado, "En curso"); break;
        case 3: strcpy(t->estado, "Terminada"); break;
    }
}

void pedirFechaVencimiento(Tarea *t) {           //Fecha de caducidad
    int confirm;
    printf("¿Quiere una fecha de vencimiento?\n SI(1) o NO(2): ");
    scanf("%d", &t->preguntaFecha);

    if (t->preguntaFecha == 1) {
        do {
            printf("\nIngrese dia: ");
            scanf("%d", &t->dia);
            printf("Ingrese el numero del mes: ");
            scanf("%d", &t->mes);
            printf("Ingrese el anio: ");
            scanf("%d", &t->anio);

            if (t->dia > 31 || t->dia <= 0 || t->mes > 12 || t->mes <= 0 || t->anio < 2025) {
                printf("Fecha invalida. Intente de nuevo.\n");
                continue;
            }

            printf("...%02d/%02d/%d... ¿Es su fecha final?\n SI(1) NO(2): ", t->dia, t->mes, t->anio);
            scanf("%d", &confirm);
            while (getchar() != '\n');
        } while (confirm != 1);
    }
}

void mostrarResumen(Tarea t) {                   //RESUMEN
    printf("\n¿Estos son todos los datos ingresados?\n");
    printf("----------------------------------------\n");
    printf("Tarea: %s\n", t.titulo);
    printf("Descripcion: %s\n", t.descripcion);
    printf("Dificultad: ");
    for (int i = 0; i < t.dificultad; i++) {
        printf("§");
    }

    switch (t.dificultad) {
        case 1: printf(" (Facilisimo)\n"); break;
        case 2: printf(" (Facil)\n"); break;
        case 3: printf(" (Medio)\n"); break;
        case 4: printf(" (Complicado)\n"); break;
        case 5: printf(" (Dificilisimo)\n"); break;
    }

    time_t tActual = time(NULL);
    struct tm tm = *localtime(&tActual);
    printf("Fecha de creacion: %02d/%02d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("Estado: %s\n", t.estado);

    if (t.preguntaFecha == 1) {
        printf("Vencimiento: %02d/%02d/%d\n", t.dia, t.mes, t.anio);
    } else {
        printf("Vencimiento: Sin datos incorporados\n");
    }
    printf("----------------------------------------\n");
}
