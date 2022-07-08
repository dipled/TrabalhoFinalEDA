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
    int escolha = -1;
    char *palavra = calloc(40, sizeof(char));
    while (1)
    {
        printf("Digite 1 para exibir o texto\nDigite 2 para buscar uma palavra do texto\n");
        printf("Digite 3 para contar uma determinada palavra\nDigite 4 para contar o total de palavras\n");
        printf("Digite 5 para remover uma palavra\n");
        printf("Digite 0 para sair do programa\n");
        scanf("%d", &escolha);
        switch ((escolha))
        {
        case 1:
            exibeTexto(desc);
            break;
        case 2:
            printf("Digite uma palavra para ser buscada\n");
            scanf(" %[^\n]s", palavra);
            int *ocorrencia = buscaPalavra(desc, palavra);
            if (ocorrencia != NULL)
            {
                if (ocorrencia[0] == 0)
                    printf("Palavra nao encontrada\n");
                else
                {
                    printf("Ocorrencias:\n");
                    for (int i = 0; i < ocorrencia[0] * 2; i += 2)
                    {
                        printf("(%d,%d)", ocorrencia[i + 1], ocorrencia[i + 2]);
                    }
                }
                printf("\n");
            }
            break;
        case 3:
            printf("Digite uma palavra para ser contada\n");
            scanf(" %[^\n]s", palavra);
            printf("A palavra %s ocorre %d vezes\n", palavra, numTotalCertaPalavra(desc, palavra));
            break;
        case 4:
            printf("Total de palavras:%d\n", numTotalPalavra(desc));
            break;
        case 5:
            printf("Digite a palavra a ser removida\n");
            scanf(" %[^\n]s", palavra);
            if (removePalavra(desc, palavra))
            {
                printf("Palavra removida com sucesso\n");
            }
            else
            {
                printf("Erro ao remover a palavra\n");
            }
            break;
        case 0:
            return 0;
        default:
            break;
        }
        memset(palavra, 0, 40 * sizeof(char));
    }
}