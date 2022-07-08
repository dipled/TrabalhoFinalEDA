#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arq.h"
int main(){
    struct descritor *desc = cria();
    if(desc == NULL)
    {
        printf("Erro ao crirar descritor\n");
    }
    FILE *fp;
    fp = fopen("teste.txt","r");
    if(fp == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }
    importaTexto(desc, fp);
    exibeTexto(desc);
    

    return 0;
}
