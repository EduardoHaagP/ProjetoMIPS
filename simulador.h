#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "mips.h"

/**
 * @brief Traduz uma instrução binária para o formato Assembly (string).
 * @param instrucaoBinaria A instrução em formato numérico.
 * @param instrucaoAssembly Buffer para armazenar a string da instrução traduzida.
 */
void traduzirParaAssembly(unsigned int instrucaoBinaria, char* instrucaoAssembly);

/**
 * @brief Decodifica uma instrução e chama a função de execução correspondente.
 * @param instrucaoBinaria A instrução em formato numérico.
 * @param estado Ponteiro para o estado da CPU.
 * @param memoria Ponteiro para a memória.
 */
void decodificarEExecutar(unsigned int instrucaoBinaria, EstadoMips* estado, int* memoria);


/**
 * @brief Realiza um ciclo completo de instrução: busca, decodifica e executa.
 * @param instrucoes Ponteiro para o vetor de strings com as instruções do programa.
 * @param estado Ponteiro para o estado da CPU.
 * @param memoria Ponteiro para a memória.
 * @return Retorna 1 se o programa deve continuar, 0 se encontrou SAIR (EXIT).
 */
int cicloDeInstrucao(const char** instrucoes, EstadoMips* estado, int* memoria);

#endif // SIMULADOR_H