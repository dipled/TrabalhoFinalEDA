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
    int numlinhas;
    struct noLinha *primeiraLinha;
};

// Definicao das funcoes

struct descritor * cria();
int importaTexto(struct descritor *desc, FILE *fp);
int exibeTexto(struct descritor *desc, FILE *fp);