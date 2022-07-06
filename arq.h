#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define FRACASSO 0
#define SUCESSO 1

struct linha
{
    char palavra[40];
    int lin;
    int col;
    struct linha *prox;
    struct linha *ant;


};
