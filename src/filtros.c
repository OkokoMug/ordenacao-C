#include "filtros.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int filtrarPorLetra(const LinhaCSV* linha, int campo, char letra) {
    if (!linha || linha->nColunas < 1) return 0;
    size_t idx = (campo == ORDENAR_BIOMA) ? 8 : 7; // bioma ou municipio
    if (linha->nColunas <= idx) return 0;
    char inicial = linha->colunas[idx][0];
    return toupper((unsigned char)inicial) == toupper((unsigned char)letra);
}

int filtrarPorAno(const LinhaCSV* linha, int ano) {
    if (!linha || linha->nColunas <= 4) return 0;
    int anoLinha;
    if (sscanf(linha->colunas[4], "%d", &anoLinha) != 1) return 0;
    return anoLinha == ano;
}
