/* Resolve as Torres de Hanói usando recursividade. */

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

void torresDeHanoi(int n, char origem, char auxiliar, char destino) {
    if (n == 1) {
        printf("Mover disco 1 de %c para %c\n", origem, destino);
        return;
    }
    torresDeHanoi(n - 1, origem, destino, auxiliar);
    printf("Mover disco %d de %c para %c\n", n, origem, destino);
    torresDeHanoi(n - 1, auxiliar, origem, destino);
}

int main(void) {
    int n;
    printf("Quantidade de discos: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Informe uma quantidade inteira maior que zero.\n");
        return 1;
    }
    torresDeHanoi(n, 'A', 'B', 'C');
    return 0;
}
