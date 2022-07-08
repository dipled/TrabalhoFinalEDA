#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define TRUE 1
#define FALSE 0

// Definicao dos structs -Pedro Vargas

struct noPalavra
{
    char palavra[40];
    int col;
    struct noPalavra *proxPal;
    struct noPalavra *antPal;
};

struct noLinha
{
    int lin;
    int numPalavras;
    struct noPalavra *primeiraPalavra;
    struct noLinha *proxLin;
    struct noLinha *antLin;
};

struct descritor
{
    int numLinhas;
    struct noLinha *primeiraLinha;
};

// Definicao das funcoes

struct descritor *cria();
int importaTexto(struct descritor *desc, FILE *fp);
int exibeTexto(struct descritor *desc);
int numTotalCertaPalavra(struct descritor *desc, char *palavra);
int *buscaPalavra(struct descritor *desc, char *palavra);
int numTotalPalavra(struct descritor *desc);
int removePalavra(struct descritor *desc, char *palavra);
int removePalavraPos(struct descritor *desc, int lin, int col);
