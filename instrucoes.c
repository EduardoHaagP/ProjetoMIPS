// Eduardo Haag Piassa da Silva 
// Lucas Henrique Motta
#include "instrucoes.h"
#include <stdio.h>

// --- Lógica e Aritméticas ---
void executarAdd(unsigned int rd, unsigned int rs, unsigned int rt, EstadoMips* estado) {
    estado->registradores[rd] = estado->registradores[rs] + estado->registradores[rt];
}

void executarAddi(unsigned int rt, unsigned int rs, int imediato, EstadoMips* estado) {
    estado->registradores[rt] = estado->registradores[rs] + imediato;
}

void executarSub(unsigned int rd, unsigned int rs, unsigned int rt, EstadoMips* estado) {
    estado->registradores[rd] = estado->registradores[rs] - estado->registradores[rt];
}

void executarMult(unsigned int rs, unsigned int rt, EstadoMips* estado) {
    // MIPS real usa registradores HI e LO. Simplificando:
    long long resultado = (long long)estado->registradores[rs] * estado->registradores[rt];
    // Armazenando em dois registradores convencionais (ex: R1 e R2) para simular
    estado->registradores[1] = (int)(resultado >> 32); // HI
    estado->registradores[2] = (int)(resultado & 0xFFFFFFFF); // LO
}

void executarAnd(unsigned int rd, unsigned int rs, unsigned int rt, EstadoMips* estado) {
    estado->registradores[rd] = estado->registradores[rs] & estado->registradores[rt];
}

void executarOr(unsigned int rd, unsigned int rs, unsigned int rt, EstadoMips* estado) {
    estado->registradores[rd] = estado->registradores[rs] | estado->registradores[rt];
}

void executarSll(unsigned int rd, unsigned int rt, unsigned int shamt, EstadoMips* estado) {
    estado->registradores[rd] = estado->registradores[rt] << shamt;
}

// --- Load e Store ---
void executarLw(unsigned int rt, int imediato, unsigned int rs, EstadoMips* estado, const int* memoria) {
    // Endereço = R[rs] + imediato. O endereço é em bytes, mas nossa memória é de inteiros.
    // Simplificação: o índice da memória será o endereço calculado / 4.
    unsigned int endereco = (estado->registradores[rs] + imediato) / 4;
    if(endereco < TAMANHO_MEMORIA) {
         estado->registradores[rt] = memoria[endereco];
    } else {
        printf("Erro: Acesso invalido a memoria em LW!\n");
    }
}

void executarSw(unsigned int rt, int imediato, unsigned int rs, EstadoMips* estado, int* memoria) {
    unsigned int endereco = (estado->registradores[rs] + imediato) / 4;
     if(endereco < TAMANHO_MEMORIA) {
        memoria[endereco] = estado->registradores[rt];
    } else {
        printf("Erro: Acesso invalido a memoria em SW!\n");
    }
}

void executarLui(unsigned int rt, int imediato, EstadoMips* estado) {
    estado->registradores[rt] = imediato << 16;
}

// --- Condicionais ---
void executarSlt(unsigned int rd, unsigned int rs, unsigned int rt, EstadoMips* estado) {
    estado->registradores[rd] = (estado->registradores[rs] < estado->registradores[rt]) ? 1 : 0;
}

void executarSlti(unsigned int rt, unsigned int rs, int imediato, EstadoMips* estado) {
    estado->registradores[rt] = (estado->registradores[rs] < imediato) ? 1 : 0;
}

// --- Chamadas de Sistema ---
void executarSyscall(EstadoMips* estado) {
    // O tipo de syscall é determinado pelo valor em $v0 (R2)
    int tipoSyscall = estado->registradores[2];
    switch(tipoSyscall) {
        case 1: // IMPRIMIR_INTEIRO
            printf("IMPRIMIR_INTEIRO: %d\n", estado->registradores[4]); // Argumento em $a0 (R4)
            break;
        case 4: // IMPRIMIR_STRING (não implementado neste escopo)
             printf("IMPRIMIR_STRING: (nao implementado)\n");
            break;
        case 10: // SAIR (EXIT)
            printf("Syscall SAIR executada.\n");
            // A lógica de parada é tratada no ciclo principal
            break;
        default:
            printf("Erro: Syscall com codigo %d nao reconhecido.\n", tipoSyscall);
            break;
    }
}