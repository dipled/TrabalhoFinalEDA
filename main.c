#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arq.h"
int main(){
    struct descritor *desc = cria();
    FILE *fp;
    fp = fopen("teste.txt","r");
    if(fp == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }
    importaTexto(desc, fp);
    exibeTexto(desc);
    printf("Numero de vezes que a palavra 'teste' aparece: %d\n", numTotalCertaPalavra(desc,"teste"));
    printf("Numero de palavrsa: %d\n",numTotalPalavra(desc));

    return 0;
}
