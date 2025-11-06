#include "csv.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static long long comparacoes = 0;
static long long copias = 0;

static int strcmp_case_insensitive(const char* a, const char* b) {
    for (; *a && *b; a++, b++) {
        char ca = tolower((unsigned char)*a);
        char cb = tolower((unsigned char)*b);
        if (ca != cb) return (ca - cb);
    }
    return (unsigned char)*a - (unsigned char)*b;
}

static int compararCampos(const LinhaCSV* a, const LinhaCSV* b, int campo, int direcao) {
    if ((int)a->nColunas <= campo || (int)b->nColunas <= campo) return 0;

    int cmp = strcmp_case_insensitive(a->colunas[campo], b->colunas[campo]);
    comparacoes++;
    return cmp * direcao;
}

static int compararMulti(const LinhaCSV* a, const LinhaCSV* b, int campoPrincipal, int campoSecundario,
                         int dirPrincipal, int dirSecundario) {
    int cmp = compararCampos(a, b, campoPrincipal, dirPrincipal);
    if (cmp != 0) return cmp;
    if (campoSecundario >= 0)
        return compararCampos(a, b, campoSecundario, dirSecundario);
    return 0;
}

static void merge(LinhaCSV* arr, LinhaCSV* aux, int inicio, int meio, int fim,
                  int campoPrincipal, int campoSecundario,
                  int dirPrincipal, int dirSecundario) {
    int i = inicio, j = meio + 1, k = inicio;

    while (i <= meio && j <= fim) {
        if (compararMulti(&arr[i], &arr[j], campoPrincipal, campoSecundario, dirPrincipal, dirSecundario) <= 0)
            aux[k++] = arr[i++];
        else
            aux[k++] = arr[j++];
        copias++;
    }

    while (i <= meio) {
        aux[k++] = arr[i++];
        copias++;
    }
    while (j <= fim) {
        aux[k++] = arr[j++];
        copias++;
    }

    for (i = inicio; i <= fim; i++) {
        arr[i] = aux[i];
        copias++;
    }
}

static void mergesort(LinhaCSV* arr, LinhaCSV* aux, int inicio, int fim,
                      int campoPrincipal, int campoSecundario,
                      int dirPrincipal, int dirSecundario) {
    if (inicio >= fim) return;
    int meio = (inicio + fim) / 2;

    mergesort(arr, aux, inicio, meio, campoPrincipal, campoSecundario, dirPrincipal, dirSecundario);
    mergesort(arr, aux, meio + 1, fim, campoPrincipal, campoSecundario, dirPrincipal, dirSecundario);

    merge(arr, aux, inicio, meio, fim, campoPrincipal, campoSecundario, dirPrincipal, dirSecundario);
}

void OrdenarLinhas(LinhaCSV* linhas, int total, int campoPrincipal, int campoSecundario,
                   int dirPrincipal, int dirSecundario) {
    comparacoes = 0;
    copias = 0;

    clock_t inicio = clock();

    LinhaCSV* aux = malloc(sizeof(LinhaCSV) * total);
    if (!aux) {
        printf("Erro: memoria insuficiente para ordenacao\n");
        return;
    }

    mergesort(linhas, aux, 0, total - 1, campoPrincipal, campoSecundario, dirPrincipal, dirSecundario);
    free(aux);

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n--- Estatisticas da Ordenacao ---\n");
    printf("Comparacoes: %lld\n", comparacoes);
    printf("Copias: %lld\n", copias);
    printf("Tempo total: %.4f segundos\n", tempo);
    printf("---------------------------------\n\n");
}
