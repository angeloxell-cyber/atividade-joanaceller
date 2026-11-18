/* Separa positivos pares e negativos ímpares e ordena. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - stdlib.h: oferece funções como malloc, realloc, free e qsort.
 * - scanf: lê um valor digitado pelo usuário. O & indica o endereço da variável onde o valor será guardado.
 * - printf: mostra mensagens e resultados na tela.
 * - for: repete um trecho de código enquanto a condição for verdadeira.
 * - if: executa um trecho somente quando a condição é verdadeira.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
 * - const: indica que o valor apontado não deve ser alterado pela função.
 * - [ ]: acessa uma posição de um vetor. Em C, a primeira posição é a de índice 0.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - sizeof: informa quantos bytes um tipo ou variável ocupa na memória.
 * - qsort: organiza os elementos de um vetor usando uma função de comparação.
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
#include <stdlib.h>

int compararCrescente(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}
int main(void) {
    int positivosPares[10], negativosImpares[10], qtdP = 0, qtdN = 0, n;
    printf("Informe 10 inteiros:\n");
    for (int i = 0; i < 10; i++) {
        if (scanf("%d", &n) != 1) return 1;
        if (n > 0 && n % 2 == 0) positivosPares[qtdP++] = n;
        if (n < 0 && n % 2 != 0) negativosImpares[qtdN++] = n;
    }
    qsort(positivosPares, qtdP, sizeof(int), compararCrescente);
    qsort(negativosImpares, qtdN, sizeof(int), compararCrescente);
    printf("Positivos e pares: ");
    for (int i = 0; i < qtdP; i++) printf("%d ", positivosPares[i]);
    printf("\nNegativos e impares: ");
    for (int i = 0; i < qtdN; i++) printf("%d ", negativosImpares[i]);
    printf("\n");
    return 0;
}
