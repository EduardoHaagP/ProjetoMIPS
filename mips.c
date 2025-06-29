// Eduardo Haag Piassa da Silva 
// Lucas Henrique Motta
#include "mips.h"
#include <stdio.h>

void inicializarMips(EstadoMips* estado) {
    for (int i = 0; i < NUM_REGISTRADORES; i++) {
        estado->registradores[i] = 0;
    }
    estado->pc = 0;
}

void exibirRegistradores(const EstadoMips* estado) {
    printf("\n--- Estado dos Registradores ---\n");
    printf("PC: %u\n", estado->pc);
    for (int i = 0; i < NUM_REGISTRADORES; i++) {
        printf("R%d: %d (0x%X)\t", i, estado->registradores[i], estado->registradores[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
    printf("--------------------------------\n");
}