#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

 int opc, dificultad, dia, mes, anio, pregunta, confirm, volver;
 char titulo[20];
 char descripcion[200];
 int seleccionEstado;
 char estado[20];
 
 
 int main()
 {
 	do{
 		  printf ("MENU DE OPCIONES \n");
 		   printf ("(1) Ver mis tareas \n");
 		   printf ("(2) Buscar una tarea \n");
 		   printf ("(3) nada aqui \n");
 		   printf ("(4) Crear una tarea \n");
 		   printf ("(0) salir \n");
 		   printf("\nSeleccione: ");
		    scanf ("%d", &opc);
 		  
 		   
	 switch(opc)
	 {
	 	case 0: printf ("\n Gracias por llamarme para nada\n");
	 	break;
		case 1: printf ("\n ingresaste a al modulo de suma \n \n");
	 	break;
	 	case 2: printf ("\n ingresaste al modulo de resta \n \n");
	 	break;
	 	case 3: printf ("\n dije que aqui no hay nada \n");
	 	break;
	 	
		 case 4: printf ("\nEstas creando una tarea: \n");
	 	printf("De un titulo a esta tarea: ");
	 	scanf("%s", titulo);
	 	 while (getchar() != '\n');
	 	printf("\nDe una descripcion a esta tarea: ");
 	    fgets(descripcion, sizeof(descripcion), stdin);
        descripcion[strcspn(descripcion, "\n")] = 0; 
        do{
	 	printf("\n1 = § = Facilisimo\n2 = §§ = Facil\n3 = §§§ = Medio\n4 = §§§§ = Complicado\n5 = §§§§§ = Dificilimo \nSeleccione su dificultad:");
	 	scanf("%d", &dificultad);
	 	    if (dificultad < 1 || dificultad > 5) {
        printf("¡Seleccione un número entre 1 y 5!\n");
    }
} while (dificultad < 1 || dificultad > 5);

printf("\n¿En qué estado desea dejar la tarea?\n");
printf("1 = Pendiente\n2 = En curso\n3 = Terminada\nSeleccione: ");
scanf("%d", &seleccionEstado);

while (seleccionEstado < 1 || seleccionEstado > 3) {
    printf("?? Opción inválida. Intente nuevamente: ");
    scanf("%d", &seleccionEstado);
}

switch (seleccionEstado) {
    case 1:
        strcpy(estado, "Pendiente");
        break;
    case 2:
        strcpy(estado, "En curso");
        break;
    case 3:
        strcpy(estado, "Terminada");
        break;
}

	 	printf("¿Quiere una fecha de vencimiento?\n SI(1) o NO(2): ");
	 	scanf("%d", &pregunta);
	 	if(pregunta == 1){
	 		do{
	 			
			 
	 		printf("\nIngrese dia aqui: ");
	 		scanf("%d", &dia);
	 		printf("\nIngrese el numero del mes: ");
	 		scanf("%d", &mes);
	 		printf("\nIngrese el anio:  ");
	 		scanf("%d", &anio);
	 		if (dia > 31 || dia <= 0 || mes > 12 || mes <= 0 || anio < 2024) {
        printf("\n?? Fecha inválida. Por favor ingrese una fecha válida.\n");
        continue; // vuelve al inicio del bucle
    }
	 		printf("...%d/%d/%d...¿Es su fecha de vencimiento final?\n SI(1) NO(2): ", dia, mes, anio);
	 		scanf("%d", &confirm);
	 		while (getchar() != '\n');
			 }while (confirm != 1);
			 }else{printf("\n");
		 }printf("\n¿Estos son todos los datos ingresados?\n");
printf("----------------------------------------\n");
printf("Tarea: %s\n", titulo);
printf("Descripcion: %s\n", descripcion);
printf("Dificultad: ");
for (int i = 0; i < dificultad; i++) {
    printf("§");
}
printf("\n");
time_t t = time(NULL);
struct tm tm = *localtime(&t);
printf("Fecha de creación: %02d/%02d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1927);
printf("Estado: %s\n", estado);

if (pregunta == 1) {
    printf("Vencimiento: %02d/%02d/%d\n", dia, mes, anio);
} else {
    printf("Vencimiento: Sin datos incorporados\n");
}
printf("----------------------------------------\n");
printf("¿Confirmar tarea? SI (1) / NO (2): ");
    scanf("%d", &confirm);

    if (confirm == 1) {
        printf("¡Se guardo la tarea exitosamente!\n \n \n");
    } else {
        printf("? Tarea cancelada. Puedes volver a crearla.\n");
    }

	 	break;
	   }
}	   while (opc !=0);
printf ("Adios!");
	return 0;}
