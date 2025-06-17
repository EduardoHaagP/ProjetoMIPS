#include <stdio.h>
#include "simulador.h"
#include "instrucoes.h"
#include "util.h"

// Função para decodificar e executar
void decodificarEExecutar(unsigned int instrucaoBinaria, EstadoMips* estado, int* memoria) {
    // Extrai os campos da instrução usando máscaras e deslocamentos
    unsigned int opcode = (instrucaoBinaria >> 26) & 0x3F;
    unsigned int rs = (instrucaoBinaria >> 21) & 0x1F;
    unsigned int rt = (instrucaoBinaria >> 16) & 0x1F;
    unsigned int rd = (instrucaoBinaria >> 11) & 0x1F;
    unsigned int shamt = (instrucaoBinaria >> 6) & 0x1F;
    unsigned int funct = instrucaoBinaria & 0x3F;
    int imediato = (int)(short)(instrucaoBinaria & 0xFFFF); // Com extensão de sinal

    // Decodifica baseado no OPCODE
    switch(opcode) {
        case 0x00: // Tipo R
            switch(funct) {
                case 0x20: executarAdd(rd, rs, rt, estado); break;   // ADD
                case 0x22: executarSub(rd, rs, rt, estado); break;   // SUB
                case 0x18: executarMult(rs, rt, estado); break;     // MULT 
                case 0x24: executarAnd(rd, rs, rt, estado); break;   // AND 
                case 0x25: executarOr(rd, rs, rt, estado); break;    // OR 
                case 0x00: executarSll(rd, rt, shamt, estado); break; // SLL 
                case 0x2A: executarSlt(rd, rs, rt, estado); break;   // SLT
                case 0x0C: executarSyscall(estado); break;           // SYSCALL
                default: printf("Erro: Funct 0x%X nao reconhecido para Tipo R.\n", funct); break;
            }
            break;
        case 0x08: executarAddi(rt, rs, imediato, estado); break;     // ADDI
        case 0x23: executarLw(rt, imediato, rs, estado, memoria); break; // LW
        case 0x2B: executarSw(rt, imediato, rs, estado, memoria); break; // SW
        case 0x0F: executarLui(rt, imediato, estado); break;          // LUI 
        case 0x0A: executarSlti(rt, rs, imediato, estado); break;     // SLTI
        default: printf("Erro: Opcode 0x%X nao reconhecido.\n", opcode); break;
    }
}

// Função para traduzir para Assembly (simplificada)
void traduzirParaAssembly(unsigned int instrucaoBinaria, char* instrucaoAssembly) {
    unsigned int opcode = (instrucaoBinaria >> 26) & 0x3F;
    unsigned int rs = (instrucaoBinaria >> 21) & 0x1F;
    unsigned int rt = (instrucaoBinaria >> 16) & 0x1F;
    unsigned int rd = (instrucaoBinaria >> 11) & 0x1F;
    unsigned int shamt = (instrucaoBinaria >> 6) & 0x1F;
    unsigned int funct = instrucaoBinaria & 0x3F;
    int imediato = (int)(short)(instrucaoBinaria & 0xFFFF);

    if (opcode == 0x00) { // Tipo R
        switch (funct) {
            case 0x20: sprintf(instrucaoAssembly, "add R%u, R%u, R%u", rd, rs, rt); break;
            case 0x22: sprintf(instrucaoAssembly, "sub R%u, R%u, R%u", rd, rs, rt); break;
            case 0x18: sprintf(instrucaoAssembly, "mult R%u, R%u", rs, rt); break; 
            case 0x24: sprintf(instrucaoAssembly, "and R%u, R%u, R%u", rd, rs, rt); break; 
            case 0x25: sprintf(instrucaoAssembly, "or R%u, R%u, R%u", rd, rs, rt); break;  
            case 0x00: sprintf(instrucaoAssembly, "sll R%u, R%u, %u", rd, rt, shamt); break; 
            case 0x2A: sprintf(instrucaoAssembly, "slt R%u, R%u, R%u", rd, rs, rt); break;
            case 0x0C: sprintf(instrucaoAssembly, "syscall"); break;
            default: sprintf(instrucaoAssembly, "Tipo R desconhecido (funct: 0x%X)", funct); break;
        }
    } else { // Tipo I e J
        switch (opcode) {
            case 0x08: sprintf(instrucaoAssembly, "addi R%u, R%u, %d", rt, rs, imediato); break;
            case 0x23: sprintf(instrucaoAssembly, "lw R%u, %d(R%u)", rt, imediato, rs); break;
            case 0x2B: sprintf(instrucaoAssembly, "sw R%u, %d(R%u)", rt, imediato, rs); break;
            case 0x0F: sprintf(instrucaoAssembly, "lui R%u, %d", rt, imediato); break; 
            case 0x0A: sprintf(instrucaoAssembly, "slti R%u, R%u, %d", rt, rs, imediato); break;
            default: sprintf(instrucaoAssembly, "Tipo I/J desconhecido (opcode: 0x%X)", opcode); break;
        }
    }
}

int cicloDeInstrucao(const char** instrucoes, EstadoMips* estado, int* memoria) {
    // 1. Buscar a instrução na memória de instruções
    const char* instrucaoStringBinaria = instrucoes[estado->pc];
    unsigned int instrucaoBinaria = binarioParaInteiro(instrucaoStringBinaria);
    
    char instrucaoAssembly[100];
    traduzirParaAssembly(instrucaoBinaria, instrucaoAssembly);
    
    printf("Executando [PC=%u]: %s -> %s\n", estado->pc, instrucaoStringBinaria, instrucaoAssembly);

    // 2. Incrementar PC antes de executar
    estado->pc++;

    // 3. Decodificar e Executar
    decodificarEExecutar(instrucaoBinaria, estado, memoria);

    // Checa se a instrução foi um syscall de SAIR
    unsigned int opcode = (instrucaoBinaria >> 26) & 0x3F;
    unsigned int funct = instrucaoBinaria & 0x3F;
    if(opcode == 0x00 && funct == 0x0C && estado->registradores[2] == 10) {
        return 0; // Sinaliza o fim
    }
    
    return 1; // Continua a execução
}