// Eduardo Haag Piassa da Silva 
// Lucas Henrique Motta
#include "util.h"
#include <string.h>
#include <stdlib.h>

unsigned int binarioParaInteiro(const char* strBinaria) {
    return (unsigned int) strtoul(strBinaria, NULL, 2);
}