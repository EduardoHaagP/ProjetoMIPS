# ProjetoMIPS
Instrucoes para compilar e executar o Mini Simulador MIPS.

Certifique-se de ter o compilador GCC e a ferramenta Make instalados.

1. Para compilar o projeto:
   No terminal, na pasta raiz do projeto, execute o comando:
   make

   Isso irá compilar todos os arquivos fonte e gerar um executável chamado "simulador_mips".

2. Para executar o simulador:
   Ainda no terminal, execute o comando:
   make run
   
   Ou diretamente:
   ./simulador_mips

3. Para limpar (apagar) os arquivos compilados e o executável:
   No terminal, execute o comando:
   make clean

**Como usar o simulador:**
- Ao executar, um menu será exibido.
- Use a opção 1 para carregar um arquivo de texto contendo o programa em formato binário. Cada linha do arquivo deve ter exatamente 32 caracteres '0' ou '1'.
- Use as outras opções para executar o programa carregado (passo a passo ou completo) e verificar o estado dos registradores.