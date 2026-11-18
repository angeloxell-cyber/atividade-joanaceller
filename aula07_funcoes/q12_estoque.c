/* Soma o estoque, conta níveis baixos e busca um produto. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
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
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
#define PRODUTOS 8
int calcularTotalEstoque(const int estoque[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) total += estoque[i];
    return total;
}
int contarEstoqueBaixo(const int estoque[], int n) {
    int contador = 0;
    for (int i = 0; i < n; i++) if (estoque[i] < 5) contador++;
    return contador;
}
int buscarProduto(const int estoque[], int codigo) {
    (void)estoque;
    if (codigo < 1 || codigo > PRODUTOS) return -1;
    return codigo - 1;
}
int main(void) {
    int estoque[PRODUTOS];
    for (int i = 0; i < PRODUTOS; i++) {
        printf("Quantidade do produto %d: ", i + 1);
        if (scanf("%d", &estoque[i]) != 1 || estoque[i] < 0) return 1;
    }
    printf("Total em estoque: %d\nProdutos com estoque baixo: %d\n",
           calcularTotalEstoque(estoque, PRODUTOS),
           contarEstoqueBaixo(estoque, PRODUTOS));
    int codigo;
    printf("Codigo do produto a buscar (1 a 8): ");
    if (scanf("%d", &codigo) != 1) return 1;
    int posicao = buscarProduto(estoque, codigo);
    if (posicao == -1) printf("Produto inexistente.\n");
    else printf("Produto %d encontrado na posicao %d; quantidade: %d\n",
                codigo, posicao, estoque[posicao]);
    return 0;
}
