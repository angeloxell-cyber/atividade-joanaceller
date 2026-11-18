/* Cadastra votos dinamicamente e salva em arquivo binário. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - stdlib.h: oferece funções como malloc, realloc, free e qsort.
 * - string.h: oferece funções para trabalhar com textos e copiar dados, como strcmp e memcpy.
 * - scanf: lê um valor digitado pelo usuário. O & indica o endereço da variável onde o valor será guardado.
 * - printf: mostra mensagens e resultados na tela.
 * - for: repete um trecho de código enquanto a condição for verdadeira.
 * - if: executa um trecho somente quando a condição é verdadeira.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
 * - const: indica que o valor apontado não deve ser alterado pela função.
 * - [ ]: acessa uma posição de um vetor. Em C, a primeira posição é a de índice 0.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - struct: reúne várias informações diferentes em um único tipo de dado.
 * - malloc: reserva memória durante a execução do programa.
 * - realloc: aumenta ou diminui um bloco de memória já reservado.
 * - free: libera a memória reservada dinamicamente.
 * - sizeof: informa quantos bytes um tipo ou variável ocupa na memória.
 * - FILE: tipo usado para representar um arquivo aberto.
 * - fopen: abre ou cria um arquivo. Modos comuns: r = leitura, w = escrita do zero, rb = leitura binária, wb = escrita binária e rb+ = leitura e escrita.
 * - fclose: fecha o arquivo e finaliza o acesso a ele.
 * - fread: lê dados de um arquivo, geralmente em formato binário.
 * - fwrite: grava dados em um arquivo, geralmente em formato binário.
 * - fseek: muda a posição de leitura ou escrita dentro do arquivo.
 * - ftell: informa a posição atual dentro do arquivo; pode ser usada para descobrir seu tamanho.
 * - rewind: volta a posição do arquivo para o começo.
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * - ?: operador condicional. Escolhe um resultado se a condição for verdadeira e outro se for falsa.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char titulo[12]; int zona; } Eleitor;
typedef struct { Eleitor eleitor; int numero_voto; } Cedula;

int adicionarVoto(Cedula **votos, size_t *quantidade, Cedula novo) {
    Cedula *temp = realloc(*votos, (*quantidade + 1) * sizeof(Cedula));
    if (!temp) return 0;
    *votos = temp;
    (*votos)[*quantidade] = novo;
    (*quantidade)++;
    return 1;
}
Cedula *recuperarVotos(const char *arquivo, size_t *quantidade) {
    FILE *arq = fopen(arquivo, "rb");
    if (!arq) return NULL;
    if (fseek(arq, 0, SEEK_END) != 0) { fclose(arq); return NULL; }
    long tamanho = ftell(arq);
    if (tamanho < 0 || tamanho % (long)sizeof(Cedula) != 0) { fclose(arq); return NULL; }
    *quantidade = (size_t)tamanho / sizeof(Cedula);
    rewind(arq);
    Cedula *v = *quantidade ? malloc(*quantidade * sizeof(Cedula)) : NULL;
    if (*quantidade && (!v || fread(v, sizeof(Cedula), *quantidade, arq) != *quantidade)) {
        free(v); fclose(arq); return NULL;
    }
    fclose(arq);
    return v;
}
int main(void) {
    Cedula *votos = NULL;
    size_t quantidade = 0;
    int n;
    printf("Quantidade de votos a cadastrar: ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 100000) return 1;
    for (int i = 0; i < n; i++) {
        Cedula c;
        printf("Titulo eleitoral: ");
        if (scanf("%11s", c.eleitor.titulo) != 1) { free(votos); return 1; }
        printf("Zona: ");
        if (scanf("%d", &c.eleitor.zona) != 1) { free(votos); return 1; }
        printf("Numero do voto: ");
        if (scanf("%d", &c.numero_voto) != 1 || !adicionarVoto(&votos, &quantidade, c)) {
            printf("Erro ao adicionar voto.\n"); free(votos); return 1;
        }
    }
    FILE *arq = fopen("urnas.bin", "wb");
    if (!arq) { perror("urnas.bin"); free(votos); return 1; }
    if (quantidade && fwrite(votos, sizeof(Cedula), quantidade, arq) != quantidade) {
        printf("Erro ao salvar votos.\n"); fclose(arq); free(votos); return 1;
    }
    fclose(arq);
    free(votos);

    size_t recuperados = 0;
    Cedula *lista = recuperarVotos("urnas.bin", &recuperados);
    if (recuperados && !lista) { printf("Erro ao recuperar votos.\n"); return 1; }
    printf("\nVotos recuperados: %zu\n", recuperados);
    for (size_t i = 0; i < recuperados; i++)
        printf("Titulo: %s | Zona: %d | Voto: %d\n",
               lista[i].eleitor.titulo, lista[i].eleitor.zona, lista[i].numero_voto);
    free(lista);
    return 0;
}
