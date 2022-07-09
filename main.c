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
    // exibeTexto(desc);
    //  printf("Numero total da palavra Teste: %d\n",numTotalCertaPalavra(desc, "Teste"));
    /*  int *ocorrencias = buscaPalavra(desc, "Teste");
      if (ocorrencias != NULL)
      {
          for (int i = 0; i < ocorrencias[0] * 2; i += 2)
          {
              printf("(%d,%d)\n", ocorrencias[i + 1], ocorrencias[i + 2]);
          }
      }*/
    // printf("Numero de palavras: %d\n",numTotalPalavra(desc));*/
    // edicaoPalavra(desc, 2, 7, "justin bieber");
    // removePalavraPos(desc,1,1);
    // exibeTexto(desc);
    char *teste;
    char *str;
    int **sub;
    teste = malloc(sizeof(char) * 100);
    strcpy(teste, "teste a b c divinas bunda a b c d e f g h a tese aboboras ");
    int tam=0;
    sub = subString(desc, teste, &tam);
    str = strtok(teste, " .*-/");
    while(str!=NULL){
        printf("%s", str);
        str = strtok(NULL, " .*-/");
    }
/*
    for (int i = 0; i < tam; i++)
    {
        printf("ocorrencias da substring '%s': \n", str);
        if (sub[i] != NULL)
        {

            for (int j = 0; j < sub[i][0] * 2; j += 2)
            {
                printf("(%d,%d)\n", sub[i][j + 1], sub[i][j + 2]);
            }
        }
        else
            printf("nao ha ocorrencias\n")
        
        str = strtok(NULL, " ./-");
    }
*/
    return 0;
}