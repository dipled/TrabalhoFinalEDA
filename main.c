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
    printf("\nE) Total palavra especifica\n");
    printf("Numero total da palavra Teste: %d\n",numTotalCertaPalavra(desc, "Teste"));
    int *ocorrencias = buscaPalavra(desc, "Teste");
      if (ocorrencias != NULL)
      {
          for (int i = 0; i < ocorrencias[0] * 2; i += 2)
          {
              printf("(%d,%d)\n", ocorrencias[i + 1], ocorrencias[i + 2]);
          }
      }
    printf("\n--------");
    printf("\nF) Numero total\n");
    printf("Numero de palavras: %d\n",numTotalPalavra(desc));
    printf("\n--------");
    printf("\nG) Edicao\n");
    edicaoPalavra(desc, 2, 7, "justin bieber");
    exibeTexto(desc);

    printf("\n--------");
    printf("\nD) Remove posicao\n");
    removePalavraPos(desc,1,1);
    exibeTexto(desc);

    printf("\n--------");
    printf("\nI) Substrings\n");

    char *teste;
    char *str;
    int **sub;
    teste = malloc(sizeof(char) * 100);
    strcpy(teste, "teste a c divinas ");
    int tam = 0;
    sub = subString(desc, teste, &tam);
    str = strtok(teste, " .*-/");

    for (int i = 0; i < tam; i++)
    {
        printf("\nOcorrencias da substring '%s': \n", str);
        if (sub[i] != NULL)
        {

            for (int j = 0; j < sub[i][0] * 2; j += 2)
            {
                printf("(%d,%d)\n", sub[i][j + 1], sub[i][j + 2]);
            }
        }
        else
            printf("nao ha ocorrencias\n");

        str = strtok(NULL, " ./-");
    }

    return 0;
}