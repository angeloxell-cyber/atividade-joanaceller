/* Calcula média, maior nota e quantidade de aprovados. */

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
#define ALUNOS 10
double calcularMediaTurma(const double notas[], int n) {
    double soma = 0;
    for (int i = 0; i < n; i++) soma += notas[i];
    return soma / n;
}
double encontrarMaiorNota(const double notas[], int n) {
    double maior = notas[0];
    for (int i = 1; i < n; i++) if (notas[i] > maior) maior = notas[i];
    return maior;
}
int contarAprovados(const double notas[], int n) {
    int aprovados = 0;
    for (int i = 0; i < n; i++) if (notas[i] >= 7.0) aprovados++;
    return aprovados;
}
void exibirResultados(double media, double maior, int aprovados) {
    printf("Media da turma: %.2f\nMaior nota: %.2f\nAprovados: %d\n", media, maior, aprovados);
}
int main(void) {
    double notas[ALUNOS];
    for (int i = 0; i < ALUNOS; i++) {
        printf("Nota do aluno %d: ", i + 1);
        if (scanf("%lf", &notas[i]) != 1) return 1;
    }
    exibirResultados(calcularMediaTurma(notas, ALUNOS),
                     encontrarMaiorNota(notas, ALUNOS),
                     contarAprovados(notas, ALUNOS));
    return 0;
}
