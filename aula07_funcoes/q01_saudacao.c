/* Cria uma função e chama três vezes. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - printf: mostra mensagens e resultados na tela.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
void mostrarSaudacao(void) {
    printf("Bem-vindo ao mundo das funcoes em C!\n");
}
int main(void) {
    mostrarSaudacao();
    mostrarSaudacao();
    mostrarSaudacao();
    return 0;
}
