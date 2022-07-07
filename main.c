#include "arq.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Funcao de criacao do descritor da lista - Pedro Vargas
struct descritor *cria()
{
    struct descritor *desc = calloc(1, sizeof(struct descritor));
    if (desc == NULL)
    {
        return NULL; // O -1 foi escolhido como padrao de retorno de erro para todas as funcoes
    }
    desc->numLinhas = 0;
    desc->primeiraLinha = NULL;
}
// Funcao de importacao do texto para a lista - Pedro Vargas
int importaTexto(struct descritor *desc, FILE *fp)
{
    int numLinha = 0;

    desc->primeiraLinha = calloc(1, sizeof(struct noLinha));

    if (desc->primeiraLinha == NULL)
        return -1;

    char linha[900];

    struct noLinha *aux = calloc(1, sizeof(struct noLinha));

    while (fgets(linha, 900, fp) != NULL) // Esse while le ate o final do arquivo
    {
        int numPalavras = 0;
        numLinha += 1;
        int numCol = 1;
        int acabou = 0;
        int quantEspacos = 0;
        struct noLinha *temp = calloc(1, sizeof(struct noLinha));
        if (temp == NULL)
        {
            return -1;
        }
        temp->lin = numLinha;
        temp->primeiraPalavra = calloc(1, sizeof(struct noPalavra));
        struct noPalavra *aux2 = calloc(1, sizeof(struct noPalavra));

        char *palavra = calloc(40, sizeof(char));
        int i2 = 0;                                    // Esse i2 sera usado para servir de indice da palavra
                                                       // Representando cada caractere
        for (int i = 0; i < strlen(linha) + 1; i += 1) // Esse for le ate o final da linha
        {
            if (linha[i] != ' ' && acabou == 0 && linha[i] != '\n' && linha[i] != '\0')
            {

                palavra[i2] = linha[i];
                i2 += 1;
            }
            else if (linha[i] == ' ') // A logica por tras desse bloco else if eh basicamente contar quantos espacos
            {                         // tem apos a atual palavra e settar a flag que a palavra acabou
                quantEspacos += 1;
                acabou = 1;
            }
            else // Condicao indicando que a palavra ja acabou e os espacos tambem
            {    // ou seja, a proxima palavra comecou
                struct noPalavra *temp2 = calloc(1, sizeof(struct noPalavra));
                if (temp2 == NULL)
                {
                    return -1;
                }
                strcpy(temp2->palavra, palavra);
                temp2->col = numCol;
                if (numCol == 1)
                {
                    temp2->antPal = NULL;
                    temp->primeiraPalavra = temp2;
                }
                else
                {
                    temp2->antPal = aux2;
                }
                aux2->proxPal = temp2;
                temp2->proxPal = NULL;
                aux2 = temp2;
                numCol += strlen(palavra) + quantEspacos;
                quantEspacos = 0;
                acabou = 0;
                i2 = 0;
                palavra = calloc(40, sizeof(char)); // Reset da palavra lida
                                                     // caractere da proxima palavra - Pedro Vargas
                numPalavras += 1;
                if (linha[i] == '\n' || linha[i] == '\0')
                {
                    break;
                }
                i -= 1; // Temos que diminuir o indice em uma unidade, pois lemos ate o primeiro
            }
        }
        if (numLinha == 1)
        {
            temp->antLin = NULL;
            desc->primeiraLinha = temp;
        }
        else
        {
            temp->antLin = aux;
        }
        aux->proxLin = temp;
        temp->proxLin = NULL;
        aux = temp;
        temp->numPalavras = numPalavras;
    }
    desc->numLinhas = numLinha;
}
//Funcao que exibe o texto a partir da lista - Gustavo Felipe
int exibeTexto(struct descritor *desc)
{
    struct noLinha *aux = calloc(1, sizeof(struct noLinha));
    if (aux != NULL)
    {
        aux = desc->primeiraLinha;
        while (aux != NULL)
        {
            int col = 1;
            struct noPalavra *aux2 = calloc(1, sizeof(struct noPalavra));
            if (aux2 != NULL)
            {
                aux2 = aux->primeiraPalavra;
                while (aux2->palavra != NULL)
                {
                    while (col < aux2->col)
                    {
                        printf(" ");
                        col+=1;
                    }
                    printf("%s", aux2->palavra);
                    col += strlen(aux2->palavra);
                    aux2 = aux2->proxPal;
                }
            }
            printf("\n");

            aux = aux->proxLin;
        }
    }
}

//Funcao que exibe do número total de ocorrências de uma palavra - Gustavo Konescki Fuhr
int numTotalCertaPalavra(struct descritor *desc, char palavra[50])
{
    struct noLinha *aux = calloc(1, sizeof(struct noLinha));
    int totPalavra = 0;
    if (aux != NULL)
    {
        aux = desc->primeiraLinha;
        while (aux != NULL)
        {
            struct noPalavra *aux2 = calloc(1, sizeof(struct noPalavra));
            if (aux2 != NULL)
            {
                aux2 = aux->primeiraPalavra;
                while (aux2->palavra != NULL)
                {
                    if (strcmp(palavra, aux2->palavra) == 0)
                    {
                        totPalavra++;
                    }
                    aux2 = aux2->proxPal;
                }
            }
            aux = aux->proxLin;
        }
    }
    printf("Numero total da palavra %s: %d", palavra, totPalavra);
}

int main(){
    setlocale(LC_ALL, "Portuguese");
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
    numTotalCertaPalavra(desc, "oVo");
    return 0;
}