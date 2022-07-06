#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define FRACASSO 0
#define SUCESSO 1

//======================APLICACAO=====================
struct linha
{
    char palavra[40];
    int lin;
    int col;
    struct linha *prox;
    struct linha *ant;


}

//======================LISTA=====================
struct noLDE
{
    linha dados;
    struct noLDE *prox;
    struct noLDE *ant;
};

struct descLDE
{
    int tamInfo;
    struct noLDE *inicio;
};

struct descLDE *cria(int tamInfo);
int insereNovoPrimeiro(struct descLDE *p, info *novo);
int insereNovoUltimo(struct descLDE *p, info *novo);
int insereNaPoslog(struct descLDE *p, info *novo, unsigned int posLog);
int tamanhoDaLista(struct descLDE *p);
int reinicia(struct descLDE *p);
struct descLDE *destroi(struct descLDE *p);
int buscaNaPoslog(struct descLDE *p, info *reg, unsigned int posLog);
int buscaOultimo(struct descLDE *p, info *reg);
int buscaOprimeiro(struct descLDE *p, info *reg);
int removeDaPoslog(struct descLDE *p, info *reg, unsigned int posLog);
int removeOultimo(struct descLDE *p, info *reg);
int removeOprimeiro(struct descLDE *p, info *reg);
int enderecosFisicos(struct descLDE *p);
