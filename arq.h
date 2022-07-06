#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define FRACASSO 0
#define SUCESSO 1

struct noPalavra
{
    char palavra[40];
    int col;
    struct noPalavra *prox;
    struct noPalavra *ant;
};

struct noLinha{
    int lin;
    int numPalavras;
    struct noPalavra *primeiraPalavra;
    struct noLinha *prox;
    struct noLinha *ant;
};

struct multiLista{
    int numlinhas;
    struct noLinha *primeiraLinha;
};
