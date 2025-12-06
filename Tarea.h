//
// Created by maciel on 3/12/25.
//

#ifndef EPYA_TAREA_H
#define EPYA_TAREA_H
#define MAX_TAREAS 100


typedef struct {                //Estructura pricipal de crear tarea
    char titulo[20];
    char descripcion[200];
    int dificultad;
    int dia, mes, anio;
    int preguntaFecha;
    int estadoSeleccionado;
    char estado[20];
} Tarea;
void crearTarea();
void eliminarTarea();
void verTareas();
void editarTarea();
#endif //EPYA_TAREA_H