#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arq.h"
void exibe(struct descritor *desc);
void removePal(struct descritor *desc);
void removePos(struct descritor *desc);
void conta(struct descritor *desc);
void busca(struct descritor *desc);
void contaTotal(struct descritor *desc);
void subStr(struct descritor *desc);
void edita(struct descritor *desc);

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
    while (1)
    {
        printf("Digite 1 para exibir o texto\nDigite 2 para buscar uma palavra do texto\n");
        printf("Digite 3 para contar uma determinada palavra\nDigite 4 para contar o total de palavras\n");
        printf("Digite 5 para remover uma palavra\nDigite 6 para remover uma palavra de uma linha e coluna\n");
        printf("Digite 7 para editar uma palavra\nDigite 9 para mostrar as substrings de uma string\n");
        printf("Digite 0 para sair do programa\n");
        scanf("%d", &escolha);
        switch ((escolha))
        {
        case 1:
            exibe(desc);
            break;
        case 2:
            busca(desc);
            break;
        case 3:
            conta(desc);
            break;
        case 4:
            contaTotal(desc);
            break;
        case 5:
            removePal(desc);
            break;
        case 6:
            removePos(desc);
            break;
        case 7:
            edita(desc);
            break;
        case 9:
            subStr(desc);
            break;
        case 0:
            return 0;
        default:
            break;
        }
    }
}

void exibe(struct descritor *desc)
{
    exibeTexto(desc);
}
void contaTotal(struct descritor *desc)
{
    printf("Total de palavras:%d\n", numTotalPalavra(desc));
}
void conta(struct descritor *desc)
{
    char *palavra = calloc(40, sizeof(char));
    printf("Digite uma palavra para ser contada\n");
    scanf(" %[^\n]s", palavra);
    printf("A palavra %s ocorre %d vezes\n", palavra, numTotalCertaPalavra(desc, palavra));
}
void busca(struct descritor *desc)
{
    char *palavra = calloc(40, sizeof(char));
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
}
void removePal(struct descritor *desc)
{
    char *palavra = calloc(40, sizeof(char));
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
}
void removePos(struct descritor *desc)
{
    int lin, col;
    printf("Digite a linha e a coluna da palavra a ser removida\n");
    scanf("%d %d", &lin, &col);
    if (removePalavraPos(desc, lin, col))
        printf("Palavra removida com sucesso\n");
    else
        printf("Palavra nao encontrada\n");
}
void edita(struct descritor *desc){
    int lin, col;
    char *palavra = calloc(40, sizeof(char));
    printf("Digite a linha e a coluna da palavra a ser editada\n");
    scanf("%d %d", &lin, &col);
    printf("Digite a palavra a ser editada\n");
    scanf(" %[^\n]s", palavra);
    if (edicaoPalavra(desc, lin, col, strtok(palavra, " .-&/")))
        printf("Palavra editada com sucesso\n");
    else
        printf("Palavra nao encontrada\n");
}

void subStr(struct descritor *desc)
{
    
    char *teste;
    int **sub;
    sub = malloc(sizeof(int));
    teste = malloc(sizeof(char) * 100);
    char *str = calloc(40, sizeof(char));
    printf("Digite uma palavra para ser buscada\n");
    scanf(" %[^\n]s", teste);
    int tam = 0;
    sub = subString(desc, teste, &tam);
    str = strtok(teste, " .*-/");
    for (int i = 0; i < tam; i++)
    {
        printf("\nOcorrencias da substring '%s': \n", str);
        if (sub[i][0] != 0)
        {

            for (int j = 0; j < sub[i][0] * 2; j += 2)
            {
                printf("(%d,%d)\n", sub[i][j + 1], sub[i][j + 2]);
            }
        }
        else
            printf("Nao ha ocorrencias\n");

        str = strtok(NULL, " ./-");
    }
}
