/* Atualiza depósito ou saque em clientes.bin. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - scanf: lê um valor digitado pelo usuário. O & indica o endereço da variável onde o valor será guardado.
 * - printf: mostra mensagens e resultados na tela.
 * - while: repete um trecho enquanto a condição continuar verdadeira.
 * - if: executa um trecho somente quando a condição é verdadeira.
 * - else: executa uma alternativa quando a condição do if é falsa.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
 * - [ ]: acessa uma posição de um vetor. Em C, a primeira posição é a de índice 0.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - struct: reúne várias informações diferentes em um único tipo de dado.
 * - sizeof: informa quantos bytes um tipo ou variável ocupa na memória.
 * - FILE: tipo usado para representar um arquivo aberto.
 * - fopen: abre ou cria um arquivo. Modos comuns: r = leitura, w = escrita do zero, rb = leitura binária, wb = escrita binária e rb+ = leitura e escrita.
 * - fclose: fecha o arquivo e finaliza o acesso a ele.
 * - fread: lê dados de um arquivo, geralmente em formato binário.
 * - fwrite: grava dados em um arquivo, geralmente em formato binário.
 * - fseek: muda a posição de leitura ou escrita dentro do arquivo.
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * - ?: operador condicional. Escolhe um resultado se a condição for verdadeira e outro se for falsa.
 * - break: interrompe um laço ou encerra um case do switch.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>

typedef struct { int conta_corrente; char nome[50]; float saldo; } Cliente;
int main(void) {
    int conta;
    float valor;
    char tipo;
    printf("Numero da conta: ");
    if (scanf("%d", &conta) != 1) return 1;
    printf("Operacao (D para deposito, S para saque): ");
    if (scanf(" %c", &tipo) != 1) return 1;
    printf("Valor: ");
    if (scanf("%f", &valor) != 1 || valor < 0) return 1;
    if (tipo != 'D' && tipo != 'd' && tipo != 'S' && tipo != 's') {
        printf("Operacao invalida.\n"); return 1;
    }

    FILE *arq = fopen("clientes.bin", "rb+");
    if (!arq) { perror("clientes.bin"); return 1; }
    Cliente c;
    int encontrado = 0;
    while (fread(&c, sizeof(Cliente), 1, arq) == 1) {
        if (c.conta_corrente == conta) {
            if (tipo == 'D' || tipo == 'd') c.saldo += valor;
            else if (c.saldo >= valor) c.saldo -= valor;
            else { printf("Saldo insuficiente.\n"); fclose(arq); return 1; }
            if (fseek(arq, -(long)sizeof(Cliente), SEEK_CUR) != 0 ||
                fwrite(&c, sizeof(Cliente), 1, arq) != 1) {
                printf("Erro ao atualizar registro.\n"); fclose(arq); return 1;
            }
            encontrado = 1;
            printf("Saldo atualizado: R$ %.2f\n", c.saldo);
            break;
        }
    }
    if (!encontrado) printf("Conta nao encontrada.\n");
    fclose(arq);
    return encontrado ? 0 : 1;
}
