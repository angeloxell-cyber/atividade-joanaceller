/* Grava três produtos em texto e depois lê o arquivo. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - scanf: lê um valor digitado pelo usuário. O & indica o endereço da variável onde o valor será guardado.
 * - printf: mostra mensagens e resultados na tela.
 * - for: repete um trecho de código enquanto a condição for verdadeira.
 * - while: repete um trecho enquanto a condição continuar verdadeira.
 * - if: executa um trecho somente quando a condição é verdadeira.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
 * - [ ]: acessa uma posição de um vetor. Em C, a primeira posição é a de índice 0.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - struct: reúne várias informações diferentes em um único tipo de dado.
 * - FILE: tipo usado para representar um arquivo aberto.
 * - fopen: abre ou cria um arquivo. Modos comuns: r = leitura, w = escrita do zero, rb = leitura binária, wb = escrita binária e rb+ = leitura e escrita.
 * - fclose: fecha o arquivo e finaliza o acesso a ele.
 * - fprintf: grava texto formatado em um arquivo.
 * - fscanf: lê dados formatados de um arquivo.
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>

typedef struct { int codigo; char nome[50]; float preco; } Produto;
int main(void) {
    Produto produtos[3];
    for (int i = 0; i < 3; i++) {
        printf("Produto %d - codigo: ", i + 1);
        if (scanf("%d", &produtos[i].codigo) != 1) return 1;
        printf("Nome (sem espacos): ");
        if (scanf("%49s", produtos[i].nome) != 1) return 1;
        printf("Preco: ");
        if (scanf("%f", &produtos[i].preco) != 1) return 1;
    }
    FILE *arq = fopen("estoque.txt", "w");
    if (!arq) { perror("estoque.txt"); return 1; }
    for (int i = 0; i < 3; i++)
        fprintf(arq, "%d %s %.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
    fclose(arq);

    arq = fopen("estoque.txt", "r");
    if (!arq) { perror("estoque.txt"); return 1; }
    printf("\n%-10s %-20s %s\n", "Codigo", "Nome", "Preco");
    Produto p;
    while (fscanf(arq, "%d %49s %f", &p.codigo, p.nome, &p.preco) == 3)
        printf("%-10d %-20s R$ %.2f\n", p.codigo, p.nome, p.preco);
    fclose(arq);
    return 0;
}
