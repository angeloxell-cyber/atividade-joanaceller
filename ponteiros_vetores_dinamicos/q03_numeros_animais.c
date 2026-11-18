/* Conta números, cadastra nomes e mostra correspondências. */

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
 * - #define: cria uma constante textual para substituir um nome por um valor no código.
 * - [ ]: acessa uma posição de um vetor. Em C, a primeira posição é a de índice 0.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * - break: interrompe um laço ou encerra um case do switch.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 15
#define MAX_ANIMAIS 100

int primo(int n) {
    if (n < 2) return 0;
    for (int d = 2; d <= n / d; d++) if (n % d == 0) return 0;
    return 1;
}
int main(void) {
    int v[N], distintos[N], freq[N], qtd = 0;
    char animais[MAX_ANIMAIS][50];
    int totalAnimais = 0;

    printf("Informe 15 numeros inteiros:\n");
    for (int i = 0; i < N; i++) if (scanf("%d", &v[i]) != 1) return 1;

    for (int i = 0; i < N; i++) {
        int j;
        for (j = 0; j < qtd; j++) if (distintos[j] == v[i]) { freq[j]++; break; }
        if (j == qtd) { distintos[qtd] = v[i]; freq[qtd] = 1; qtd++; }
    }

    /* Regra adotada: para primo com frequencia impar, cadastrar a soma das ocorrencias (numero * frequencia) de nomes. */
    for (int i = 0; i < qtd; i++) {
        if (primo(distintos[i]) && freq[i] % 2 == 1) {
            long long quantidade = (long long)distintos[i] * freq[i];
            if (quantidade > MAX_ANIMAIS || quantidade < 0) {
                printf("Quantidade de animais excede o limite de %d.\n", MAX_ANIMAIS); return 1;
            }
            for (int k = 0; k < (int)quantidade; k++) {
                printf("Nome do animal %d: ", totalAnimais + 1);
                if (scanf("%49s", animais[totalAnimais++]) != 1) return 1;
            }
        }
    }

    printf("\nCorrespondencias para numeros com frequencia par:\n");
    for (int i = 0; i < qtd; i++) {
        if (freq[i] % 2 == 0) {
            int pos = distintos[i] - 1;
            if (pos >= 0 && pos < totalAnimais) printf("%d: %s\n", distintos[i], animais[pos]);
            else printf("%d: Nao existe correspondencia\n", distintos[i]);
        }
    }
    printf("\nAnimais cadastrados:\n");
    for (int i = 0; i < totalAnimais; i++) printf("%d. %s\n", i + 1, animais[i]);
    return 0;
}
