#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_TAREAS 100
#define ARCHIVO    "tareas.dat"

typedef enum { Pendiente, En_Proceso, Finalizada, Cancelada } Estado;
typedef enum { Nivel1 = 1, Nivel2, Nivel3, Nivel4, Nivel5 } Dificultad;

typedef struct {
    char  titulo[100];
    char  descripcion[270];
    char  creada[25];
    char  vencimiento[25];
    Estado estado;
    Dificultad dificultad;
} Tarea;

static Tarea tareas[MAX_TAREAS];
static int   numTareas = 0;

static void fechaActual(char *buf, int tam) {
    time_t t = time(NULL);
    strftime(buf, tam, "%d/%m/%Y %H:%M:%S", localtime(&t));
}

static const char *estadoStr(Estado e) {
    const char *s[] = { "Pendiente", "En proceso", "Finalizada", "Cancelada" };
    return (e >= Pendiente && e <= Cancelada) ? s[e] : "N/D";
}

static const char *stars(Dificultad d) {
    static const char *s[] = {
        "", "★☆☆☆☆", "★★☆☆☆", "★★★☆☆", "★★★★☆", "★★★★★"
    };
    return (d >= Nivel1 && d <= Nivel5) ? s[d] : "N/D";
}

static Estado estadoDesdeLetra(char c) {
    switch (c) {
        case 'P': case 'p': return Pendiente;
        case 'E': case 'e': return En_Proceso;
        case 'F': case 'f': return Finalizada;
        case 'C': case 'c': return Cancelada;
        default: return Pendiente;
    }
}

static void cargarTareas(void) {
    FILE *f = fopen(ARCHIVO, "rb");
    if (!f) return;
    fread(&numTareas, sizeof numTareas, 1, f);
    fread(tareas, sizeof(Tarea), numTareas, f);
    fclose(f);
}

static void guardarTareas(void) {
    FILE *f = fopen(ARCHIVO, "wb");
    if (!f) { perror("guardar"); return; }
    fwrite(&numTareas, sizeof numTareas, 1, f);
    fwrite(tareas, sizeof(Tarea), numTareas, f);
    fclose(f);
}

static int esBisiesto(int anio) {
    return (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
}

static int diasEnMes(int mes, int anio) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return esBisiesto(anio) ? 29 : 28;
        default:
            return 0;
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
    printf("Estado: %s\n", t.estadoStr);

    if (t.preguntaFecha == 1) {
        printf("Vencimiento: %02d/%02d/%d\n", t.dia, t.mes, t.anio);
    } else {
        printf("Vencimiento: Sin datos incorporados\n");
    }
    printf("----------------------------------------\n");
}
static void leerFechaValida(int *d, int *m, int *a) {
    do {
        printf("  Día: "); scanf("%d", d);
        printf("  Mes: "); scanf("%d", m);
        printf("  Año: "); scanf("%d", a);
        if (*a < 2025) {
            printf("El año debe ser 2025 o mayor.\n");
            continue;
        }
        int maxDias = diasEnMes(*m, *a);
        if (*m < 1 || *m > 12 || *d < 1 || *d > maxDias) {
            printf("Fecha inválida, intenta de nuevo.\n");
            continue;
        }
        break;
    } while(1);
}

static void agregarTarea(void) {
    if (numTareas == MAX_TAREAS) { puts("Límite alcanzado"); return; }

    Tarea t;
    getchar();
    system("cls");
    printf("Título: ");  fgets(t.titulo, sizeof t.titulo, stdin);
    printf("Descripción: ");  fgets(t.descripcion, sizeof t.descripcion, stdin);

    printf("Fecha de vencimiento:\n");
    int d, m, a;
    leerFechaValida(&d, &m, &a);
    snprintf(t.vencimiento, sizeof t.vencimiento, "%02d/%02d/%04d", d, m, a);

    printf("Dificultad (1 a 5 estrellas): ");
    int dif = 1;  scanf("%d", &dif);
    t.dificultad = (dif < 1 || dif > 5) ? Nivel1 : (Dificultad)dif;

    char letraEstado;
    printf("Estado (P=Pendiente, E=En proceso, F=Finalizada, C=Cancelada): ");
    scanf(" %c", &letraEstado);
    t.estado = estadoDesdeLetra(letraEstado);

    mostrarResumen();
    int confirm;
    printf("¿Confirmar tarea? SI (1) / NO (2): ");
    scanf("%d", &confirm);

    if (confirm == 1) {
        printf("¡Se guardó la tarea exitosamente!\n\n\n");
        system("cls");
    } else {
        printf("Tarea cancelada. Puedes volver a crearla.\n");
    }
}

    fechaActual(t.creada, sizeof t.creada);
    tareas[numTareas++] = t;
    guardarTareas();
}

static void verTareas(void) {
    if (numTareas == 0) {
        printf("No hay tareas para mostrar.\n");
        return;
    }
    for (int i = 0; i < numTareas; i++) {
        Tarea *t = &tareas[i];
        system("cls");
        printf("\nTarea #%d\n", i+1);
        printf("Título .....: %s", t->titulo);
        printf("Descripción : %s", t->descripcion);
        printf("Creada .....: %s\n", t->creada);
        printf("Vence ......: %s\n", t->vencimiento);
        printf("Estado .....: %s\n", estadoStr(t->estado));
        printf("Dificultad .: %s\n", stars(t->dificultad));
        if (i < numTareas - 1) {
            printf("\nPresiona ENTER para ver la siguiente tarea...");
            getchar(); getchar(); // getchar() dos veces para consumir \n previo y pausa
        }
    }
}

static void editarTarea(void) {
    system("cls");
    int i; printf("Nº a editar: "); scanf("%d", &i); --i;
    if (i < 0 || i >= numTareas) return;
    getchar();

    printf("Nuevo título (enter = igual): ");
    char buf[100]; fgets(buf, sizeof buf, stdin);
    if (buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = 0;
        strcpy(tareas[i].titulo, buf);
    }

    printf("Nueva descripción (enter = igual): ");
    char desc[270]; fgets(desc, sizeof desc, stdin);
    if (desc[0] != '\n') {
        desc[strcspn(desc, "\n")] = 0;
        strcpy(tareas[i].descripcion, desc);
    }

    printf("Nueva fecha de vencimiento (0 para mantener):\n");
    int d, m, a;
    do {
        printf("  Día: "); scanf("%d", &d);
        printf("  Mes: "); scanf("%d", &m);
        printf("  Año: "); scanf("%d", &a);
        if (d == 0 && m == 0 && a == 0) break;
        if (a < 2025) {
            printf("El año debe ser 2025 o mayor.\n");
            continue;
        }
        int maxDias = diasEnMes(m, a);
        if (m < 1 || m > 12 || d < 1 || d > maxDias) {
            printf("Fecha inválida, intenta de nuevo.\n");
            continue;
        }
        snprintf(tareas[i].vencimiento, sizeof tareas[i].vencimiento, "%02d/%02d/%04d", d, m, a);
        break;
    } while(1);

    printf("Nuevo estado (P, E, F, C - enter para mantener): ");
    char est = getchar();
    if (est != '\n') {
        tareas[i].estado = estadoDesdeLetra(est);
    }

    guardarTareas();
}

static void eliminarTarea(void) {
    system("cls");
    int i; printf("Nº a eliminar: "); scanf("%d", &i); --i;
    if (i < 0 || i >= numTareas) return;
    for (int j = i; j < numTareas - 1; ++j) tareas[j] = tareas[j + 1];
    --numTareas;
    guardarTareas();
}

static void menu(void) {
    system("cls");
    int op;
    do {
        puts("\n===== GESTOR DE TAREAS =====");
        puts("1. Crear nueva tarea");
        puts("2. Ver todas las tareas");
        puts("3. Editar tarea");
        puts("4. Eliminar tarea");
        puts("0. Salir");
        printf("Opción: ");
        scanf("%d", &op);
        switch (op) {
            case 1: agregarTarea();  break;
            case 2: verTareas();     break;
            case 3: editarTarea();   break;
            case 4: eliminarTarea(); break;
            case 0: break;
            default: puts("Opción inválida.");
        }
    } while (op != 0);
}

int main(void) {
    setlocale(LC_ALL, "es_ES.UTF-8");
    cargarTareas();
    menu();
    return 0;
}
