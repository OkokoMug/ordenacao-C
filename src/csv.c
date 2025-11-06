#include "csv.h"

ManipuladorCSV* AbrirCSV(const char* caminho) {
    FILE* f = fopen(caminho, "r");
    if (!f) return NULL;

    ManipuladorCSV* m = malloc(sizeof(ManipuladorCSV));
    if (!m) {
        fclose(f);
        return NULL;
    }

    m->arquivo = f;
    return m;
}

void FecharCSV(ManipuladorCSV* manipulador) {
    if (!manipulador) return;

    if (manipulador->arquivo)
        fclose(manipulador->arquivo);

    free(manipulador);
}

LinhaCSV LerProximaLinha(ManipuladorCSV* manipulador) {
    LinhaCSV linha = { .nColunas = 0 };
    char buffer[MAX_LINHA];

    if (!fgets(buffer, MAX_LINHA, manipulador->arquivo))
        return linha; // EOF

    char* token = strtok(buffer, ",\n");
    while (token && linha.nColunas < MAX_COLUNAS) {
        linha.colunas[linha.nColunas++] = strdup(token); // aloca memória para cada coluna
        token = strtok(NULL, ",\n");
    }

    return linha;
}

void LiberarLinha(LinhaCSV* linha) {
    if (!linha) return;

    for (size_t i = 0; i < linha->nColunas; i++) {
        free(linha->colunas[i]);
        linha->colunas[i] = NULL;
    }
    linha->nColunas = 0;
}
