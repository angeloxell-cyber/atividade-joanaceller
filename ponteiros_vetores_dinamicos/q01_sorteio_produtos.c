/* Conta ocorrências, cadastra produtos e ordena os resultados. */

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
 * - #define: cria uma constante textual para substituir um nome por um valor no código.
 * - [ ]: acessa uma posição de um vetor. Em C, a primeira posição é a de índice 0.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - struct: reúne várias informações diferentes em um único tipo de dado.
 * - sizeof: informa quantos bytes um tipo ou variável ocupa na memória.
 * - qsort: organiza os elementos de um vetor usando uma função de comparação.
 * - strcmp: compara dois textos; retorna 0 quando são iguais.
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * - break: interrompe um laço ou encerra um case do switch.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 12
#define MAX_PRODUTOS 100

typedef struct { char nome[50]; float preco; } Produto;

int compararIntDecrescente(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (y > x) - (y < x);
}
int compararProduto(const void *a, const void *b) {
    return strcmp(((const Produto *)a)->nome, ((const Produto *)b)->nome);
}
int main(void) {
    int v[N], distintos[N], freq[N], qtdDistintos = 0;
    int pares[N], qtdPares = 0;
    Produto produtos[MAX_PRODUTOS];
    int qtdProdutos = 0;

    printf("Informe 12 numeros inteiros positivos:\n");
    for (int i = 0; i < N; i++) {
        if (scanf("%d", &v[i]) != 1 || v[i] <= 0) {
            printf("Entrada invalida: use inteiros positivos.\n"); return 1;
        }
    }

    for (int i = 0; i < N; i++) {
        int encontrado = 0;
        for (int j = 0; j < qtdDistintos; j++)
            if (distintos[j] == v[i]) { freq[j]++; encontrado = 1; break; }
        if (!encontrado) { distintos[qtdDistintos] = v[i]; freq[qtdDistintos] = 1; qtdDistintos++; }
    }

    for (int i = 0; i < qtdDistintos; i++) {
        if (freq[i] % 2 == 0) pares[qtdPares++] = distintos[i];
        else {
            for (int k = 1; k <= distintos[i]; k++) {
                if (qtdProdutos >= MAX_PRODUTOS) {
                    printf("Limite de produtos cadastrados atingido.\n"); return 1;
                }
                printf("Produto %d/%d (nome sem espacos): ", k, distintos[i]);
                if (scanf("%49s", produtos[qtdProdutos].nome) != 1) return 1;
                printf("Preco unitario: ");
                if (scanf("%f", &produtos[qtdProdutos].preco) != 1) return 1;
                qtdProdutos++;
            }
        }
    }
    qsort(pares, qtdPares, sizeof(int), compararIntDecrescente);
    qsort(produtos, qtdProdutos, sizeof(Produto), compararProduto);

    printf("\nNumeros informados: ");
    for (int i = 0; i < N; i++) printf("%d ", v[i]);
    printf("\nOcorrencias:\n");
    for (int i = 0; i < qtdDistintos; i++)
        printf("%d aparece %d vez(es)\n", distintos[i], freq[i]);
    printf("\nProdutos cadastrados (ordem alfabetica):\n");
    for (int i = 0; i < qtdProdutos; i++)
        printf("%s - R$ %.2f\n", produtos[i].nome, produtos[i].preco);
    printf("\nNumeros com ocorrencia par (decrescente): ");
    for (int i = 0; i < qtdPares; i++) printf("%d ", pares[i]);
    printf("\n");
    return 0;
}
