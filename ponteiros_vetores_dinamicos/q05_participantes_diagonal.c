/* Cadastra participantes, calcula médias e compara com a diagonal. */

/*
 * GUIA RAPIDO: o que alguns comandos deste codigo fazem:
 * - stdio.h: permite usar printf (mostrar mensagens) e scanf (ler o teclado).
 * - stdlib.h: oferece funções como malloc, realloc, free e qsort.
 * - string.h: oferece funções para trabalhar com textos e copiar dados, como strcmp e memcpy.
 * - math.h: oferece funções matemáticas, como sqrt (raiz quadrada).
 * - scanf: lê um valor digitado pelo usuário. O & indica o endereço da variável onde o valor será guardado.
 * - printf: mostra mensagens e resultados na tela.
 * - for: repete um trecho de código enquanto a condição for verdadeira.
 * - while: repete um trecho enquanto a condição continuar verdadeira.
 * - if: executa um trecho somente quando a condição é verdadeira.
 * - return: encerra a função e, quando necessário, devolve um resultado.
 * - void: indica que a função não devolve um valor.
 * - const: indica que o valor apontado não deve ser alterado pela função.
 * - #define: cria uma constante textual para substituir um nome por um valor no código.
 * - [ ]: acessa uma posição de um vetor. Em C, a primeira posição é a de índice 0.
 * - &: operador que obtém o endereço de uma variável; scanf usa esse endereço para guardar o dado.
 * - *: em declarações, pode indicar um ponteiro (variável que guarda um endereço de memória).
 * - struct: reúne várias informações diferentes em um único tipo de dado.
 * - sizeof: informa quantos bytes um tipo ou variável ocupa na memória.
 * - qsort: organiza os elementos de um vetor usando uma função de comparação.
 * - strcmp: compara dois textos; retorna 0 quando são iguais.
 * - sqrt: calcula a raiz quadrada de um número.
 * - %: operador que calcula o resto de uma divisão; é útil para verificar se um número é par.
 * - ?: operador condicional. Escolhe um resultado se a condição for verdadeira e outro se for falsa.
 * - break: interrompe um laço ou encerra um case do switch.
 * Os comentarios explicam o codigo; nao alteram sua execucao.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define P 4
#define MAX_VALORES 100

typedef struct {
    char nome[60];
    int idade;
    unsigned long long id;
    double valores[MAX_VALORES];
    int quantidade;
    double mediaPonderada;
} Participante;

unsigned long long fatorial(int n) {
    unsigned long long r = 1;
    for (int i = 2; i <= n; i++) {
        if (r > ULLONG_MAX / (unsigned)i) return 0;
        r *= (unsigned)i;
    }
    return r;
}
int idUsado(Participante p[], int ate, unsigned long long id) {
    for (int i = 0; i < ate; i++) if (p[i].id == id) return 1;
    return 0;
}
int compararNome(const void *a, const void *b) {
    return strcmp(((const Participante *)a)->nome, ((const Participante *)b)->nome);
}
double mediaPonderada(const double v[], int n) {
    double soma = 0, pesos = 0;
    for (int i = 0; i < n; i++) { soma += v[i] * (i + 1); pesos += i + 1; }
    return pesos ? soma / pesos : 0;
}
int main(void) {
    Participante p[P] = {0};
    double lados[2];
    int qtdLados = 0;

    for (int i = 0; i < P; i++) {
        printf("Nome e idade do participante %d: ", i + 1);
        if (scanf("%59s %d", p[i].nome, &p[i].idade) != 2 || p[i].idade < 1 || p[i].idade > 20) {
            printf("Dados invalidos (idade permitida: 1 a 20).\n"); return 1;
        }
        unsigned long long base = fatorial(p[i].idade);
        unsigned long long id = base ? base / 2 : 0;
        int tentativa = 0;
        while (id == 0 || idUsado(p, i, id)) {
            tentativa++;
            int metade = p[i].idade / 2;
            unsigned long long f = fatorial(metade);
            int expoente = tentativa;
            id = f;
            for (int k = 1; k < expoente && id; k++) {
                if (f != 0 && id > ULLONG_MAX / f) { id = 0; break; }
                id *= f;
            }
            if (id == 0 && tentativa > 1) {
                printf("Nao foi possivel gerar ID exclusivo sem exceder o limite numerico.\n"); return 1;
            }
        }
        p[i].id = id;
        printf("ID calculado: %llu\n", p[i].id);

        printf("Quantidade de valores (1 a %d): ", MAX_VALORES);
        if (scanf("%d", &p[i].quantidade) != 1 ||
            p[i].quantidade < 1 || p[i].quantidade > MAX_VALORES) return 1;
        for (int j = 0; j < p[i].quantidade; j++) {
            printf("Valor %d: ", j + 1);
            if (scanf("%lf", &p[i].valores[j]) != 1) return 1;
            if (p[i].valores[j] >= 0 && qtdLados < 2) lados[qtdLados++] = p[i].valores[j];
        }
        p[i].mediaPonderada = mediaPonderada(p[i].valores, p[i].quantidade);
    }

    qsort(p, P, sizeof(Participante), compararNome);
    printf("\nParticipantes em ordem alfabetica:\n");
    for (int i = 0; i < P; i++)
        printf("%s | ID: %llu | Media ponderada: %.2f\n", p[i].nome, p[i].id, p[i].mediaPonderada);

    if (qtdLados < 2) {
        printf("Nao foi possivel calcular a diagonal: faltam dois valores nao negativos.\n");
        return 0;
    }
    double diagonal = sqrt(lados[0] * lados[0] + lados[1] * lados[1]);
    printf("Diagonal: %.2f\n", diagonal);
    for (int i = 0; i < P; i++) {
        const char *classe = p[i].mediaPonderada > diagonal ? "Acima da diagonal" :
                             p[i].mediaPonderada < diagonal ? "Abaixo da diagonal" : "Sobre a diagonal";
        printf("%s: %s\n", p[i].nome, classe);
    }
    return 0;
}
