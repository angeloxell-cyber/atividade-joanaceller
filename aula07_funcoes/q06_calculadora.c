/* Faz uma operação escolhida pelo usuário. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - scanf: lê um valor digitado pelo usuário. O & indica o endereço da variável onde o valor será guardado.
 * - printf: mostra mensagens e resultados na tela.
 * - if: executa um trecho somente quando a condição é verdadeira.
 * - else: executa uma alternativa quando a condição do if é falsa.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * - switch: escolhe qual bloco executar conforme o valor de uma variável.
 * - case: representa uma das opções possíveis dentro de um switch.
 * - break: interrompe um laço ou encerra um case do switch.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
double somar(double a, double b) { return a + b; }
double subtrair(double a, double b) { return a - b; }
double multiplicar(double a, double b) { return a * b; }
double dividir(double a, double b) { return a / b; }

int main(void) {
    double a, b;
    int opcao;
    printf("Digite dois numeros: ");
    if (scanf("%lf %lf", &a, &b) != 2) return 1;
    printf("1-Adicao  2-Subtracao  3-Multiplicacao  4-Divisao\nOpcao: ");
    if (scanf("%d", &opcao) != 1) return 1;
    switch (opcao) {
        case 1: printf("Resultado: %.2f\n", somar(a, b)); break;
        case 2: printf("Resultado: %.2f\n", subtrair(a, b)); break;
        case 3: printf("Resultado: %.2f\n", multiplicar(a, b)); break;
        case 4:
            if (b == 0.0) printf("Erro: divisao por zero.\n");
            else printf("Resultado: %.2f\n", dividir(a, b));
            break;
        default: printf("Opcao invalida.\n"); return 1;
    }
    return 0;
}
