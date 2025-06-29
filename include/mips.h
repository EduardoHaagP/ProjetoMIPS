// Eduardo Haag Piassa da Silva 
// Lucas Henrique Motta
#ifndef MIPS_H
#define MIPS_H

// Define a quantidade de registradores e o tamanho da memória
#define NUM_REGISTRADORES 32
#define TAMANHO_MEMORIA 1024

// Estrutura para manter o estado da CPU MIPS
typedef struct {
    int registradores[NUM_REGISTRADORES];
    unsigned int pc; // Program Counter
} EstadoMips;

// --- Declarações das Funções ---

/**
 * @brief Inicializa a CPU MIPS, zerando todos os registradores e o PC.
 * @param estado Ponteiro para a estrutura de estado do MIPS.
 */
void inicializarMips(EstadoMips* estado);

/**
 * @brief Exibe o conteúdo de todos os registradores e do PC.
 * @param estado Ponteiro para a estrutura de estado do MIPS a ser exibida.
 */
void exibirRegistradores(const EstadoMips* estado);

#endif // MIPS_H