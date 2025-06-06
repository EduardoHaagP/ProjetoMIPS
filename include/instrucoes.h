#ifndef INSTRUCOES_H
#define INSTRUCOES_H

#include "mips.h"

// --- Lógica e Aritméticas ---
void executarAdd(unsigned int rd, unsigned int rs, unsigned int rt, EstadoMips* estado);
void executarAddi(unsigned int rt, unsigned int rs, int imediato, EstadoMips* estado);
void executarSub(unsigned int rd, unsigned int rs, unsigned int rt, EstadoMips* estado);
void executarMult(unsigned int rs, unsigned int rt, EstadoMips* estado); // MIPS armazena em HI/LO, vamos simplificar para rd
void executarAnd(unsigned int rd, unsigned int rs, unsigned int rt, EstadoMips* estado);
void executarOr(unsigned int rd, unsigned int rs, unsigned int rt, EstadoMips* estado);
void executarSll(unsigned int rd, unsigned int rt, unsigned int shamt, EstadoMips* estado);

// --- Load e Store ---
void executarLw(unsigned int rt, int imediato, unsigned int rs, EstadoMips* estado, const int* memoria);
void executarSw(unsigned int rt, int imediato, unsigned int rs, EstadoMips* estado, int* memoria);
void executarLui(unsigned int rt, int imediato, EstadoMips* estado);

// --- Condicionais ---
void executarSlt(unsigned int rd, unsigned int rs, unsigned int rt, EstadoMips* estado);
void executarSlti(unsigned int rt, unsigned int rs, int imediato, EstadoMips* estado);

// --- Chamadas de Sistema ---
void executarSyscall(EstadoMips* estado);

#endif // INSTRUCOES_H