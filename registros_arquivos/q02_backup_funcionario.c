/* Copia um funcionário para backup binário. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - stdlib.h: oferece funções como malloc, realloc, free e qsort.
 * - string.h: oferece funções para trabalhar com textos e copiar dados, como strcmp e memcpy.
 * - scanf: lê um valor digitado pelo usuário. O & indica o endereço da variável onde o valor será guardado.
 * - printf: mostra mensagens e resultados na tela.
 * - if: executa um trecho somente quando a condição é verdadeira.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
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
 * - fwrite: grava dados em um arquivo, geralmente em formato binário.
 * - memcpy: copia uma quantidade de bytes de uma região da memória para outra.
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int id; char cargo[30]; float salario; } Funcionario;
int main(void) {
    Funcionario *original = malloc(sizeof(Funcionario));
    Funcionario *backup = malloc(sizeof(Funcionario));
    if (!original || !backup) {
        printf("Falha na alocacao de memoria.\n");
        free(original); free(backup); return 1;
    }
    printf("ID: ");
    if (scanf("%d", &original->id) != 1) return 1;
    printf("Cargo (sem espacos): ");
    if (scanf("%29s", original->cargo) != 1) return 1;
    printf("Salario: ");
    if (scanf("%f", &original->salario) != 1) return 1;

    memcpy(backup, original, sizeof(Funcionario));
    FILE *arq = fopen("backup_rh.bin", "wb");
    if (!arq) { perror("backup_rh.bin"); free(original); free(backup); return 1; }
    if (fwrite(backup, sizeof(Funcionario), 1, arq) != 1) {
        printf("Erro ao gravar backup.\n"); fclose(arq); free(original); free(backup); return 1;
    }
    fclose(arq);
    printf("Backup salvo em backup_rh.bin.\n");
    free(original); free(backup);
    return 0;
}
