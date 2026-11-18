/* Compara dois números e retorna o maior. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - scanf: lê um valor digitado pelo usuário. O & indica o endereço da variável onde o valor será guardado.
 * - printf: mostra mensagens e resultados na tela.
 * - if: executa um trecho somente quando a condição é verdadeira.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * - ?: operador condicional. Escolhe um resultado se a condição for verdadeira e outro se for falsa.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
int maiorNumero(int a, int b) { return (a > b) ? a : b; }
int main(void) {
    int a, b;
    printf("Digite dois inteiros: ");
    if (scanf("%d %d", &a, &b) != 2) return 1;
    printf("Maior numero: %d\n", maiorNumero(a, b));
    return 0;
}
