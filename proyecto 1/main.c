#include <stdio.h>
#include <stdlib.h>
#define TOTAL_VOTOS 30

int main() {
    int votos[3] = {0}; // votos[0] = Candidato A, votos[1] = B, votos[2] = C
    int voto, i, opcion;
    float porcentaje[3];
    
    // Carga de votos
    printf("Ingresá los votos (1, 2 o 3) segun el candidato:\n");
    for (i = 0; i < TOTAL_VOTOS; i++) {
        do {
            printf("Voto #%d: ", i + 1);
            scanf("%d", &voto);
            if (voto < 1 || voto > 3) {
                printf("Voto invalido. Ingresá 1, 2 o 3.\n");
            }
        } while (voto < 1 || voto > 3);
        votos[voto - 1]++;
    }

    // Menú
    do {
        printf("\n--- MENU ---\n");
        printf("1. Ver votos por candidato\n");
        printf("2. Ver porcentajes de votos\n");
        printf("3. Ver ganador, perdedor o empate\n");
        printf("4. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Candidato A: %d votos\n", votos[0]);
                printf("Candidato B: %d votos\n", votos[1]);
                printf("Candidato C: %d votos\n", votos[2]);
                break;

            case 2:
                for (i = 0; i < 3; i++)
                    porcentaje[i] = (votos[i] * 100.0) / TOTAL_VOTOS;
                printf("Candidato A: %.2f%%\n", porcentaje[0]);
                printf("Candidato B: %.2f%%\n", porcentaje[1]);
                printf("Candidato C: %.2f%%\n", porcentaje[2]);
                break;

            case 3:
                if (votos[0] == votos[1] && votos[1] == votos[2]) {
                    printf("Empate triple entre todos los candidatos.\n");
                } else if (votos[0] == votos[1] && votos[0] > votos[2]) {
                    printf("Empate entre A y B. Van a desempate.\n");
                } else if (votos[0] == votos[2] && votos[0] > votos[1]) {
                    printf("Empate entre A y C. Van a desempate.\n");
                } else if (votos[1] == votos[2] && votos[1] > votos[0]) {
                    printf("Empate entre B y C. Van a desempate.\n");
                } else {
                    // Determinar ganador y perdedor
                    int ganador = 0, perdedor = 0;
                    for (i = 1; i < 3; i++) {
                        if (votos[i] > votos[ganador]) ganador = i;
                        if (votos[i] < votos[perdedor]) perdedor = i;
                    }
                    char letras[3] = {'A', 'B', 'C'};
                    printf("Ganador: Candidato %c con %d votos.\n", letras[ganador], votos[ganador]);
                    printf("Perdedor: Candidato %c con %d votos.\n", letras[perdedor], votos[perdedor]);
                }
                break;

            case 4:
                printf("Saliendo del programa. Chauuuu.\n");
                break;

            default:
                printf("Opcion invalida. Intentalo de nuevo.\n");
        }
    } while (opcion != 4);

    return 0;
}
