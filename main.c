// Eduardo Haag Piassa da Silva 
// Lucas Henrique Motta
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mips.h"
#include "simulador.h"

#define MAX_INSTRUCOES 256
#define TAMANHO_INSTRUCAO 33 // 32 bits + \0

void exibirMenu() {
    printf("\n--- Mini Simulador MIPS ---\n");
    printf("1. Carregar Programa Binario\n");
    printf("2. Executar Passo a Passo\n");
    printf("3. Executar Programa Completo\n");
    printf("4. Exibir Registradores e PC\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    EstadoMips estado;
    int memoria[TAMANHO_MEMORIA] = {0};
    char* instrucoes[MAX_INSTRUCOES];
    int numInstrucoes = 0;
    int programaCarregado = 0;

    inicializarMips(&estado);

    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do \n

        switch (opcao) {
            case 1: {
                char nomeArquivo[100];
                printf("Digite o nome do arquivo de programa (.txt): ");
                scanf("%s", nomeArquivo);

                FILE* arquivo = fopen(nomeArquivo, "r");
                if (!arquivo) {
                    perror("Erro ao abrir o arquivo");
                    break;
                }

                // Limpar instruções antigas se houver
                for(int i = 0; i < numInstrucoes; i++) {
                    free(instrucoes[i]);
                }
                numInstrucoes = 0;
                inicializarMips(&estado); // Reseta o estado da CPU

                char buffer[TAMANHO_INSTRUCAO];
                while (numInstrucoes < MAX_INSTRUCOES && fgets(buffer, sizeof(buffer), arquivo)) {
                    buffer[strcspn(buffer, "\n")] = 0; // Remove a nova linha
                    if(strlen(buffer) == 32) {
                        instrucoes[numInstrucoes] = (char*) malloc(TAMANHO_INSTRUCAO);
                        strcpy(instrucoes[numInstrucoes], buffer);
                        numInstrucoes++;
                    }
                }
                fclose(arquivo);
                programaCarregado = 1;
                printf("Programa carregado com %d instrucoes.\n", numInstrucoes);
                break;
            }
            case 2: // Execução Passo a Passo
                if (!programaCarregado) {
                    printf("Nenhum programa carregado!\n");
                    break;
                }
                if (estado.pc >= numInstrucoes) {
                     printf("Fim do programa. Para re-executar, carregue o programa novamente (Opcao 1).\n");
                     break;
                }
                cicloDeInstrucao((const char**)instrucoes, &estado, memoria);
                exibirRegistradores(&estado);
                break;
            case 3: // Execução Completa
                 if (!programaCarregado) {
                    printf("Nenhum programa carregado!\n");
                    break;
                }
                 if (estado.pc >= numInstrucoes) {
                     printf("Fim do programa. Para re-executar, carregue o programa novamente (Opcao 1).\n");
                     break;
                }
                while(estado.pc < numInstrucoes) {
                    if (cicloDeInstrucao((const char**)instrucoes, &estado, memoria) == 0) {
                        break; // Syscall de SAIR
                    }
                }
                printf("\n--- Execucao Finalizada ---\n");
                exibirRegistradores(&estado);
                break;
            case 4:
                exibirRegistradores(&estado);
                break;
            case 5:
                printf("Saindo do simulador...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    // Liberar memória alocada
    for(int i = 0; i < numInstrucoes; i++) {
        free(instrucoes[i]);
    }

    return 0;
}