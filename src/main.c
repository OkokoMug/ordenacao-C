#include <stdio.h>
#include <stdlib.h>
#include "csv.h"

#define MAX_CSVS 10
#define MAX_LINHAS 2500  

void mostrarMenuOrdenacao() {
    printf("\n=== MENU DE ORDENACAO ===\n");
    printf("1 - Ordenar por Data\n");
    printf("2 - Ordenar por Bioma\n");
    printf("3 - Ordenar por Municipio\n");
    printf("0 - Cancelar\n");
    printf("=========================\n");
}

int escolherCampo(const char* prompt) {
    int opcao;
    printf("%s", prompt);
    mostrarMenuOrdenacao();
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: return ORDENAR_DATA;
        case 2: return ORDENAR_BIOMA;
        case 3: return ORDENAR_MUNICIPIO;
        default: return -1;
    }
}

int escolherDirecao(const char* prompt) {
    int dir;
    printf("%s", prompt);
    printf("1 - Ascendente (A-Z ou antigo -> novo)\n");
    printf("-1 - Descendente (Z-A ou novo -> antigo)\n");
    printf("Escolha: ");
    scanf("%d", &dir);
    return (dir == -1) ? -1 : 1;
}

int main() {
    const char* arquivos[MAX_CSVS] = {
        "data/focos_br_rn_ref_2023.csv",
        "data/focos_br_rn_ref_2024.csv"
    };
    int nArquivos = 2;

    LinhaCSV* todasLinhas = malloc(sizeof(LinhaCSV) * MAX_LINHAS);
    if (!todasLinhas) {
        printf("Erro: memoria insuficiente\n");
        return 1;
    }

    int totalLinhas = 0;
    for (int i = 0; i < nArquivos; i++) {
        ManipuladorCSV* csv = AbrirCSV(arquivos[i]);
        if (!csv) {
            printf("Falha ao abrir %s\n", arquivos[i]);
            continue;
        }

        LinhaCSV linha;
        while ((linha = LerProximaLinha(csv)).nColunas > 0) {
            if (totalLinhas >= MAX_LINHAS) break;
            todasLinhas[totalLinhas++] = linha;
        }

        FecharCSV(csv);
    }

    printf("\nTotal de linhas carregadas: %d\n", totalLinhas);

    printf("\n=== CONFIGURAR ORDENACAO ===\n");

    int campoPrincipal = escolherCampo("Campo principal:\n");
    if (campoPrincipal == -1) {
        printf("Cancelado.\n");
        free(todasLinhas);
        return 0;
    }

    int dirPrincipal = escolherDirecao("Direcao do campo principal:\n");

    int campoSecundario = escolherCampo("Campo secundario (ou 0 para nenhum):\n");
    if (campoSecundario == -1) campoSecundario = -1;
    int dirSecundario = 1;
    if (campoSecundario != -1)
        dirSecundario = escolherDirecao("Direcao do campo secundario:\n");

    printf("\nOrdenando dados...\n");

    OrdenarLinhas(todasLinhas, totalLinhas, campoPrincipal, campoSecundario,
                  dirPrincipal, dirSecundario);

    printf("\n=== DADOS ORDENADOS ===\n");
    for (int i = 0; i < totalLinhas; i++) {
        for (size_t j = 0; j < todasLinhas[i].nColunas; j++)
            printf("[%s] ", todasLinhas[i].colunas[j]);
        printf("\n");
    }

    free(todasLinhas);
    return 0;
}
