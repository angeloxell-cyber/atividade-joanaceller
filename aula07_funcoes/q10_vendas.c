/* Calcula total, média e dias acima da média. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - scanf: lê um valor digitado pelo usuário. O & indica o endereço da variável onde o valor será guardado.
 * - printf: mostra mensagens e resultados na tela.
 * - for: repete um trecho de código enquanto a condição for verdadeira.
 * - if: executa um trecho somente quando a condição é verdadeira.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
 * - const: indica que o valor apontado não deve ser alterado pela função.
 * - #define: cria uma constante textual para substituir um nome por um valor no código.
 * - [ ]: acessa uma posição de um vetor. Em C, a primeira posição é a de índice 0.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
#define DIAS 5
double calcularTotal(const double vendas[], int n) {
    double total = 0;
    for (int i = 0; i < n; i++) total += vendas[i];
    return total;
}
double calcularMedia(double total, int dias) { return total / dias; }
int contarVendasAcimaDaMedia(const double vendas[], int n, double media) {
    int contador = 0;
    for (int i = 0; i < n; i++) if (vendas[i] > media) contador++;
    return contador;
}
int main(void) {
    double vendas[DIAS];
    for (int i = 0; i < DIAS; i++) {
        printf("Venda do dia %d: ", i + 1);
        if (scanf("%lf", &vendas[i]) != 1) return 1;
    }
    double total = calcularTotal(vendas, DIAS);
    double media = calcularMedia(total, DIAS);
    printf("Total: %.2f\nMedia diaria: %.2f\nDias acima da media: %d\n",
           total, media, contarVendasAcimaDaMedia(vendas, DIAS, media));
    return 0;
}
