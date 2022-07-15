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
void atualizaArq(struct descritor *desc, FILE *fp);
void insercaoPal(struct descritor *desc);
void subStr(struct descritor *desc);
void edita(struct descritor *desc);

int main()
{
    struct descritor *desc = cria();
    if (desc == NULL)
    {
        printf("Erro ao crirar descritor\n");
        return -1;
    }
    FILE *fp;
    fp = fopen("arq.txt", "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return -2;
    }
    importaTexto(desc, fp);
    int escolha = -234;
    while (1)
    {
        if (escolha != -234)
        {
            printf("Digite 1 para continuar ou 0 para parar\n");
            scanf("%d",&escolha);
            if(escolha == 0){
                atualizaArq(desc,fp);
                destroi(desc);
                if(desc!=NULL)
                    free(desc);
                return 0;
            }
        }
            
        fprintf(stderr,"\033[2J\033[H");
        printf("Digite 1 para exibir o texto\nDigite 2 para buscar uma palavra do texto\n");
        printf("Digite 3 para contar uma determinada palavra\nDigite 4 para contar o total de palavras\n");
        printf("Digite 5 para remover uma palavra\nDigite 6 para remover uma palavra de uma linha e coluna\n");
        printf("Digite 7 para editar uma palavra\nDigite 8 para inserir uma palavra\nDigite 9 para pesquisar uma palavra contendo um termo\n");
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
        case 8:
            insercaoPal(desc);
            break;
        case 9:
            subStr(desc);
            break;
        default:
            break;
        }
    }
}

void exibe(struct descritor *desc)
{
    fprintf(stderr,"\033[2J\033[H");
    exibeTexto(desc);
    printf("\n");
}
void contaTotal(struct descritor *desc)
{
    fprintf(stderr,"\033[2J\033[H");
    printf("Total de palavras:%d\n", numTotalPalavra(desc));
}
void conta(struct descritor *desc)
{
    fprintf(stderr,"\033[2J\033[H");
    char *palavra = calloc(40, sizeof(char));
    printf("Digite uma palavra para ser contada\n");
    scanf(" %[^\n]s", palavra);
    printf("A palavra %s ocorre %d vezes\n", palavra, numTotalCertaPalavra(desc, palavra));
    if(palavra != NULL) 
        free(palavra);
}
void busca(struct descritor *desc)
{
    fprintf(stderr,"\033[2J\033[H");
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
    if(palavra != NULL) 
        free(palavra);
        if(ocorrencia != NULL) 
        free(ocorrencia);
}
void removePal(struct descritor *desc)
{
    fprintf(stderr,"\033[2J\033[H");
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
    if(palavra != NULL)
        free(palavra);
}
void removePos(struct descritor *desc)
{
    fprintf(stderr,"\033[2J\033[H");
    int lin, col;
    printf("Digite a linha e a coluna da palavra a ser removida\n");
    scanf("%d %d", &lin, &col);
    if (removePalavraPos(desc, lin, col) == 1)
        printf("Palavra removida com sucesso\n");
    else
        printf("Palavra nao encontrada\n");
}
void edita(struct descritor *desc)
{
    fprintf(stderr,"\033[2J\033[H");
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
    if(palavra != NULL) 
        free(palavra);
}

void subStr(struct descritor *desc)
{
    fprintf(stderr,"\033[2J\033[H");

    char *palavra;
    palavra = calloc(40, sizeof(char));
    printf("Digite um termo para ser buscado\n");
    scanf(" %[^\n]s", palavra);
    char **resultado = subString(desc, palavra);
    if (resultado == NULL)
    {
        printf("Nenhuma palavra com termo encontrada!\n");
        return;
    }
    int i = 0;
    while (resultado[i] != NULL)
    {
        printf("Palavra que contem termo encontrada! %s\n", resultado[i]);
        int *ocorrencia = buscaPalavra(desc, resultado[i]);
        if (ocorrencia != NULL)
        {
            printf("Ocorrencias:\n");
            for (int i = 0; i < ocorrencia[0] * 2; i += 2)
            {
                printf("(%d,%d)", ocorrencia[i + 1], ocorrencia[i + 2]);
            }
            printf("\n");
        }
        i += 1;
    }
    if(palavra != NULL) 
        free(palavra);
    if(resultado != NULL)
        free(resultado);
}
void insercaoPal(struct descritor *desc)
{
    fprintf(stderr,"\033[2J\033[H");
    char *palavra = calloc(40, sizeof(char));
    printf("Digite a palavra a ser inserida\n");
    scanf(" %[^\n]s", palavra);
    if (insercao(desc, palavra))
        printf("Palavra inserida com sucesso\n");
    else
        printf("Erro ao inserir a palavra\n");
    if(palavra!=NULL)
        free(palavra);
}
void atualizaArq(struct descritor *desc, FILE *fp)
{
    if (atualizaArquivo(desc, fp))
        printf("Arquivo salvo com sucesso\n");
    else
        printf("Erro ao salvar o arquivo\n");    
}