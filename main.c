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
    int *ocorrencias = buscaPalavra(desc, "Teste");
    if(ocorrencias != NULL){
        for(int i = 0; i < sizeof(ocorrencias)/(sizeof (int))*2; i += 2){
            printf("(%d, %d)\n", ocorrencias[i], ocorrencias[i+1]);
        }
    }
    return 0;
}