#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define TRUE 1
#define FALSE 0

//DEFINICAO DOS DADOS

struct noPalavra
{
    char palavra[40];
    int col;
    struct noPalavra *proxPal;
    struct noPalavra *antPal;
};

struct noLinha{
    int lin;
    int numPalavras;
    struct noPalavra *primeiraPalavra;
    struct noLinha *proxLin;
    struct noLinha *antLin;
};

struct desc{
    int numlinhas;
    struct noLinha *primeiraLinha;
};

//DEFINICAO DAS FUNCOES

struct desc *cria(int numlinhas){}