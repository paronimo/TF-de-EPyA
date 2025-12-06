#include <stdio.h>
#include "Tarea.h"
//Todos los void guardado
int main(){
    int opc;
     do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Crear tarea\n");
        printf("2. Ver mis tareas\n");
     	printf("3. Eliminar tarea\n");
     	printf("4. Editar Tarea\n");
        printf("5. Buscar tarea(En progreso)\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);
	 switch(opc)
	 {
	 	case 0: printf ("\n Adios!\n");break;

	 	case 4: editarTarea(); break;

	 	case 3: eliminarTarea(); break;

	 	case 2: verTareas(); break;

	 	case 1: crearTarea(); break;
            default:
                printf("  Opción inválida. Intente nuevamente.\n");
        }
    } while (opc != 0);

    printf("Adios!\n");
    return 0;
    }
