# ordenacao-C

ordenacao-C é um projeto em linguagem C desenvolvido para leitura, análise e ordenação de arquivos CSV contendo registros de queimadas no Brasil.  
O programa utiliza o algoritmo Merge Sort, com foco em eficiência, modularidade e clareza didática.

## Instalação

Clone o repositório em sua máquina local:

```bash
git clone https://github.com/OkokoMug/ordenacao-C.git
cd ordenacao-C
```
Compile o projeto usando o Makefile incluído:

```bash
make
```

Após a compilação, execute o programa:

```bash
./ordenacao
```

Durante a execução, o sistema permite:

-  Escolher o campo principal e secundário para ordenação (data, bioma ou município);

-  Definir a direção da ordenação (ascendente ou descendente);

-  Exibir estatísticas de desempenho (tempo, comparações e movimentações);

-  Visualizar os dados ordenados diretamente no terminal.

