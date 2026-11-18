/* Converte Celsius para Fahrenheit por função. */

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
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
float celsiusParaFahrenheit(float c) { return (9.0f * c) / 5.0f + 32.0f; }
int main(void) {
    float c;
    printf("Temperatura em Celsius: ");
    if (scanf("%f", &c) != 1) return 1;
    printf("Fahrenheit: %.2f\n", celsiusParaFahrenheit(c));
    return 0;
}
