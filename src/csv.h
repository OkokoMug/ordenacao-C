#ifndef CSV_H
#define CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLUNAS 100
#define MAX_LINHA 1024

typedef struct {
    char* colunas[MAX_COLUNAS];
    size_t nColunas;
} LinhaCSV;

typedef struct {
    FILE* arquivo;
} ManipuladorCSV;


typedef enum {
    ORDENAR_DATA = 1,
    ORDENAR_BIOMA = 2,
    ORDENAR_MUNICIPIO = 3
} TipoOrdenacao;

ManipuladorCSV* AbrirCSV(const char* caminho);
void FecharCSV(ManipuladorCSV* manipulador);

LinhaCSV LerProximaLinha(ManipuladorCSV* manipulador);

void LiberarLinha(LinhaCSV* linha);

void OrdenarLinhas(LinhaCSV* linhas, int total, int campoPrincipal, int campoSecundario,
                   int dirPrincipal, int dirSecundario);

#endif

void ResetarContadores();
long long ObterComparacoes();
long long ObterMovimentacoes();