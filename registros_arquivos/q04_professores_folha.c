/* Copia professores e grava/lê os dados em arquivo binário. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - stdlib.h: oferece funções como malloc, realloc, free e qsort.
 * - string.h: oferece funções para trabalhar com textos e copiar dados, como strcmp e memcpy.
 * - scanf: lê um valor digitado pelo usuário. O & indica o endereço da variável onde o valor será guardado.
 * - printf: mostra mensagens e resultados na tela.
 * - for: repete um trecho de código enquanto a condição for verdadeira.
 * - if: executa um trecho somente quando a condição é verdadeira.
 * - else: executa uma alternativa quando a condição do if é falsa.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
 * - const: indica que o valor apontado não deve ser alterado pela função.
 * - [ ]: acessa uma posição de um vetor. Em C, a primeira posição é a de índice 0.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - struct: reúne várias informações diferentes em um único tipo de dado.
 * - malloc: reserva memória durante a execução do programa.
 * - free: libera a memória reservada dinamicamente.
 * - sizeof: informa quantos bytes um tipo ou variável ocupa na memória.
 * - FILE: tipo usado para representar um arquivo aberto.
 * - fopen: abre ou cria um arquivo. Modos comuns: r = leitura, w = escrita do zero, rb = leitura binária, wb = escrita binária e rb+ = leitura e escrita.
 * - fclose: fecha o arquivo e finaliza o acesso a ele.
 * - fread: lê dados de um arquivo, geralmente em formato binário.
 * - fwrite: grava dados em um arquivo, geralmente em formato binário.
 * - fseek: muda a posição de leitura ou escrita dentro do arquivo.
 * - ftell: informa a posição atual dentro do arquivo; pode ser usada para descobrir seu tamanho.
 * - rewind: volta a posição do arquivo para o começo.
 * - memcpy: copia uma quantidade de bytes de uma região da memória para outra.
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int registro; int horas_aula; } Professor;

Professor *lerProfessores(const char *nomeArquivo, int *quantidade) {
    FILE *arq = fopen(nomeArquivo, "rb");
    if (!arq) return NULL;
    if (fseek(arq, 0, SEEK_END) != 0) { fclose(arq); return NULL; }
    long bytes = ftell(arq);
    if (bytes < 0 || bytes % (long)sizeof(Professor) != 0) { fclose(arq); return NULL; }
    *quantidade = (int)(bytes / sizeof(Professor));
    rewind(arq);
    Professor *lista = malloc((size_t)*quantidade * sizeof(Professor));
    if (*quantidade > 0 && !lista) { fclose(arq); return NULL; }
    if (*quantidade > 0 && fread(lista, sizeof(Professor), (size_t)*quantidade, arq) != (size_t)*quantidade) {
        free(lista); fclose(arq); return NULL;
    }
    fclose(arq);
    return lista;
}
int main(void) {
    int n;
    printf("Quantidade de professores: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 10000) return 1;
    Professor *lista = malloc((size_t)n * sizeof(Professor));
    unsigned char *buffer = malloc((size_t)n * sizeof(Professor));
    if (!lista || !buffer) { free(lista); free(buffer); return 1; }

    for (int i = 0; i < n; i++) {
        printf("Registro e horas-aula do professor %d: ", i + 1);
        if (scanf("%d %d", &lista[i].registro, &lista[i].horas_aula) != 2) {
            free(lista); free(buffer); return 1;
        }
    }
    memcpy(buffer, lista, (size_t)n * sizeof(Professor));
    FILE *arq = fopen("folha.dat", "wb");
    if (!arq) { perror("folha.dat"); free(lista); free(buffer); return 1; }
    if (fwrite(buffer, (size_t)n * sizeof(Professor), 1, arq) != 1) {
        printf("Erro ao gravar arquivo.\n"); fclose(arq); free(lista); free(buffer); return 1;
    }
    fclose(arq);

    int lidos = 0;
    Professor *recuperados = lerProfessores("folha.dat", &lidos);
    if (!recuperados && lidos != 0) printf("Erro ao ler arquivo.\n");
    else {
        printf("\nRegistros recuperados:\n");
        for (int i = 0; i < lidos; i++)
            printf("Registro: %d | Horas-aula: %d\n", recuperados[i].registro, recuperados[i].horas_aula);
    }
    free(recuperados); free(lista); free(buffer);
    return 0;
}
