#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arq.h"
int main()
{
    struct descritor *desc = cria();
    if (desc == NULL)
    {
        printf("Erro ao crirar descritor\n");
    }
    FILE *fp;
    fp = fopen("teste.txt", "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }
    importaTexto(desc, fp);
    exibeTexto(desc);
    printf("Numero total da palavra Teste: %d\n",numTotalCertaPalavra(desc, "Teste"));
    int *ocorrencias = buscaPalavra(desc, "teste");
    if(ocorrencias != NULL){
        for(int i = 0; i < ocorrencias[0]*2; i += 2){
            printf("(%d,%d)\n",ocorrencias[i+1],ocorrencias[i+2]);
        }
    }
    printf("Numero de palavras: %d\n",numTotalPalavra(desc));
    

    return 0;
}