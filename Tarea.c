//
// Created by maciel on 3/12/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Tarea.h"

Tarea listaTareas[MAX_TAREAS];
int cantidadTareas = 0;

static void pedirTitulo(Tarea *t);
static void pedirDescripcion(Tarea *t);
static void pedirDificultad(Tarea *t);
static void pedirEstado(Tarea *t);
static void pedirFechaVencimiento(Tarea *t);
static void mostrarResumen(Tarea t);

void crearTarea() { //Funcion de CREAR TAREA
    Tarea tarea;
    int confirm;
    system("clear");

    printf("\nEstas creando una tarea:\n");

    pedirTitulo(&tarea);
    pedirDescripcion(&tarea);
    pedirDificultad(&tarea);
    pedirEstado(&tarea);
    pedirFechaVencimiento(&tarea);
    system("clear");
    mostrarResumen(tarea);
    printf("¿Confirmar tarea? SI (1) / NO (2): ");
    scanf("%d", &confirm);

    if (confirm == 1) { // guardo en el array

        listaTareas[cantidadTareas] = tarea;
        cantidadTareas++;
        printf("¡Se guardó la tarea exitosamente!\n\n\n");
        system("clear");
    } else {

        printf("Tarea cancelada. Puedes volver a crearla.\n");
        system("clear");
    }
}

static void pedirTitulo(Tarea *t) {                  //Titulo
    printf("\nDe un titulo a esta tarea: ");
    scanf("%s", t->titulo);
    while (getchar() != '\n');
}

static void pedirDescripcion(Tarea *t) {              //Descripcion//
    printf("\nDe una descripcion a esta tarea: ");
    fgets(t->descripcion, sizeof(t->descripcion), stdin);
    t->descripcion[strcspn(t->descripcion, "\n")] = 0;
}

static void pedirDificultad(Tarea *t) {                //Dificultad//
    do {
        printf("\n1 = § = Facilisimo\n2 = §§ = Facil\n3 = §§§ = Medio\n4 = §§§§ = Complicado\n5 = §§§§§ = Dificilisimo");
        printf("\nSeleccione su dificultad: ");
        scanf("%d", &t->dificultad);

        if (t->dificultad < 1 || t->dificultad > 5) {
            printf("?? ¡Seleccione un número entre 1 y 5!\n");
        }
    } while (t->dificultad < 1 || t->dificultad > 5);
}

static void pedirEstado(Tarea *t) {                   //Estado
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

static void pedirFechaVencimiento(Tarea *t) {
    int confirm = 2; // Inicializado a 2 (NO)
    t->preguntaFecha = 2; // Asumir NO hasta que se confirme

    printf("¿Quiere una fecha de vencimiento?\n SI(1) o NO(2): ");
    if (scanf("%d", &t->preguntaFecha) != 1) {
        t->preguntaFecha = 2; // Si hay error, asumimos NO
    }

    if (t->preguntaFecha == 1) {
        do {
            printf("\n--- Ingreso de Fecha ---\n");

            // 1. Pedir DÍA
            printf("Ingrese dia (1-31): ");
            if (scanf("%d", &t->dia) != 1) { t->dia = 0; }

            // 2. Pedir MES
            printf("Ingrese el numero del mes (1-12): ");
            if (scanf("%d", &t->mes) != 1) { t->mes = 0; }

            // 3. Pedir AÑO
            printf("Ingrese el anio (2025 en adelante): ");
            if (scanf("%d", &t->anio) != 1) { t->anio = 0; }

            // 4. Validacion
            if (t->dia > 31 || t->dia <= 0 ||
                t->mes > 12 || t->mes <= 0 ||
                t->anio < 2025) {

                printf("\n¡ERROR! Una o más fechas son inválidas. Intente de nuevo.\n");
                confirm = 2;
                } else {
                    // 5. Mostrar resumen y pedir confirmación
                    printf("\n...%02d/%02d/%d... ¿Es su fecha final?\n SI(1) NO(2): ", t->dia, t->mes, t->anio);
                    if (scanf("%d", &confirm) != 1) { confirm = 2; }
                }
        } while (confirm != 1);
    }
}

static void mostrarResumen(Tarea t) {                   //RESUMEN
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

void eliminarTarea() {
    system("clear");

    if (cantidadTareas == 0) {
        printf("No hay tareas para eliminar.\n");
        return;
    }

    printf("\n--- Eliminador de tareas ---\n");

    for (int j = 0; j < cantidadTareas; j++) {
        printf("%d. %s\n", j + 1, listaTareas[j].titulo);
    }

    int i;
    printf("Seleccione el número de tarea a eliminar: ");
    scanf("%d", &i);

    // Validación
    while (i < 1 || i > cantidadTareas) {
        printf("Número inválido. Intente nuevamente: ");
        scanf("%d", &i);
    }
    // Ajustar índice
    i--;
    // Desplazar todo hacia arriba

    for (int j = i; j < cantidadTareas - 1; j++) {
        listaTareas[j] = listaTareas[j + 1];
    }

    cantidadTareas--;

    printf("La tarea fue eliminada correctamente.\n");
}

void verTareas() {
    system("clear");
    if (cantidadTareas == 0) {
        printf("No hay tareas para mostrar.\n");
        return;
    }
    printf("\n--- LISTA DE TAREAS ---\n");
    for (int i = 0; i < cantidadTareas; i++) {
        printf("\nTarea Nº%d:\n", i + 1);
        mostrarResumen(listaTareas[i]);
        while (getchar() != '\n');
        system("clear");
    }
}

void editarTarea() {
    system("clear");

    if (cantidadTareas == 0) {
        printf("No hay tareas para editar.\n");
        return;
    }

    printf("\n--- EDITOR DE TAREAS ---\n");

    // Mostrar lista de tareas
    for (int j = 0; j < cantidadTareas; j++) {
        printf("%d. %s\n", j + 1, listaTareas[j].titulo);
    }

    int indice;
    printf("Seleccione el número de tarea a editar: ");
    scanf("%d", &indice);

    // Validación del índice
    while (indice < 1 || indice > cantidadTareas) {
        printf("Número inválido. Intente nuevamente: ");
        scanf("%d", &indice);
    }
    indice--;
    Tarea tareaEditada = listaTareas[indice];
    while (getchar() != '\n');

    pedirTitulo(&tareaEditada);
    pedirDescripcion(&tareaEditada);
    pedirDificultad(&tareaEditada);
    pedirEstado(&tareaEditada);
    pedirFechaVencimiento(&tareaEditada);

    system("clear");
    mostrarResumen(tareaEditada);

    int confirm;
    printf("¿Confirmar edición? SI (1) / NO (2): ");
    scanf("%d", &confirm);

    if (confirm == 1) {
        listaTareas[indice] = tareaEditada;
        printf("\n¡La tarea ha sido editada exitosamente!\n");
    } else {
        printf("\nEdición cancelada. No se realizaron cambios.\n");
    };
}
