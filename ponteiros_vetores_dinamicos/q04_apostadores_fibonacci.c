/* Calcula somas de Fibonacci e escolhe os premiados. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - string.h: oferece funções para trabalhar com textos e copiar dados, como strcmp e memcpy.
 * - scanf: lê um valor digitado pelo usuário. O & indica o endereço da variável onde o valor será guardado.
 * - printf: mostra mensagens e resultados na tela.
 * - for: repete um trecho de código enquanto a condição for verdadeira.
 * - if: executa um trecho somente quando a condição é verdadeira.
 * - else: executa uma alternativa quando a condição do if é falsa.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
 * - #define: cria uma constante textual para substituir um nome por um valor no código.
 * - [ ]: acessa uma posição de um vetor. Em C, a primeira posição é a de índice 0.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - struct: reúne várias informações diferentes em um único tipo de dado.
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * - ?: operador condicional. Escolhe um resultado se a condição for verdadeira e outro se for falsa.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
#include <string.h>

#define N 5
typedef unsigned long long ULL;

typedef struct { char nome[60]; int termos; ULL resultado; int premiado; } Apostador;

ULL somaFibonacci(int n) {
    ULL a = 0, b = 1, soma = 0;
    for (int i = 0; i < n; i++) {
        soma += a;
        ULL proximo = a + b;
        a = b; b = proximo;
    }
    return soma;
}
int ehPrimo(ULL n) {
    if (n < 2) return 0;
    for (ULL d = 2; d <= n / d; d++) if (n % d == 0) return 0;
    return 1;
}
int melhorIndice(Apostador a[], int criterio) {
    int melhor = -1;
    for (int i = 0; i < N; i++) {
        if (a[i].premiado) continue;
        int atende = criterio == 1 ? ehPrimo(a[i].resultado) :
                     criterio == 2 ? a[i].resultado % 2 == 0 : 1;
        if (atende && (melhor == -1 || a[i].resultado > a[melhor].resultado)) melhor = i;
    }
    return melhor;
}
int main(void) {
    Apostador a[N] = {0};
    ULL soma = 0;
    for (int i = 0; i < N; i++) {
        printf("Nome do apostador %d: ", i + 1);
        if (scanf("%59s", a[i].nome) != 1) return 1;
        printf("Quantidade de termos Fibonacci (1 a 90): ");
        if (scanf("%d", &a[i].termos) != 1 || a[i].termos < 1 || a[i].termos > 90) {
            printf("Quantidade invalida.\n"); return 1;
        }
        a[i].resultado = somaFibonacci(a[i].termos);
        soma += a[i].resultado;
    }
    int primeiro = melhorIndice(a, 1);
    if (primeiro != -1) a[primeiro].premiado = 1;
    int segundo = melhorIndice(a, 2);
    if (segundo != -1) a[segundo].premiado = 1;
    double media = (double)soma / N;
    int terceiro = -1;
    for (int i = 0; i < N; i++)
        if (!a[i].premiado && (double)a[i].resultado > media &&
            (terceiro == -1 || a[i].resultado > a[terceiro].resultado)) terceiro = i;

    printf("\nPremiacao:\n");
    if (primeiro != -1) printf("1o lugar: %s\n", a[primeiro].nome);
    else printf("1o lugar: sem vencedor\n");
    if (segundo != -1) printf("2o lugar: %s\n", a[segundo].nome);
    else printf("2o lugar: sem vencedor\n");
    if (terceiro != -1) printf("3o lugar: %s\n", a[terceiro].nome);
    else printf("3o lugar: sem vencedor\n");
    return 0;
}
