# Define o compilador e as flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99

# Lista de todos os arquivos objeto (.o) necessários
OBJETOS = main.o mips.o simulador.o instrucoes.o util.o

# Nome do executável final
EXECUTAVEL = simulador_mips

# Regra principal: compila tudo
all: $(EXECUTAVEL)

# Regra para linkar os objetos e criar o executável
$(EXECUTAVEL): $(OBJETOS)
	@echo "Linkando e gerando o executavel..."
	$(CC) $(CFLAGS) -o $(EXECUTAVEL) $(OBJETOS)

# Regra genérica para compilar arquivos .c em .o
%.o: %.c
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	@echo "Limpando arquivos compilados..."
	rm -f *.o $(EXECUTAVEL)

# Regra para executar o programa
run: $(EXECUTAVEL)
	./$(EXECUTAVEL)

.PHONY: all clean run