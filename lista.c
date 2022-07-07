#include "arq.h"

// Funcao de criacao do descritor da lista - Pedro Vargas
struct descritor *cria()
{
    struct descritor *desc = malloc(sizeof(struct descritor));
    if (desc == NULL)
    {
        return -1; // O -1 foi escolhido como padrao de retorno de erro para todas as funcoes
    }
    desc->numlinhas = 0;
    desc->primeiraLinha = NULL;
}

int importaTexto(struct descritor *desc, FILE *fp)
{
    int numLinha = 0;

    desc->primeiraLinha = malloc(sizeof(struct noLinha));

    if (desc->primeiraLinha == NULL)
        return -1;

    char linha[900];

    struct noLinha *aux = malloc(sizeof(struct noLinha));

    while (fgets(linha, 900, fp) != NULL) // While da linha
    {
        numLinha += 1;
        int numCol = 1;
        int quantEspacos = 0;
        int acabou = 0;
        struct noLinha *temp = malloc(sizeof(struct noLinha));
        if (temp == NULL)
        {
            return -1;
        }
        temp->lin = numLinha;
        temp->primeiraPalavra = malloc(sizeof(struct noPalavra));
        struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));

        for (int i = 0; i < strlen(linha); i += 1)
        {
            char *palavra;
            if (linha[i] != " " && acabou == 0)
            {
                palavra += linha[i];
            }
            else if (linha[i] == " ")
            {
                quantEspacos += 1;
                acabou = 1;
            }
            else
            {
                struct noPalavra *temp2 = malloc(sizeof(struct noPalavra));
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
            }
        }
        /*while (palavra)
        {
            struct noPalavra *temp2 = malloc(sizeof(struct noPalavra));
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
            numCol += strlen(palavra) + 1;
            palavra = strtok(NULL, ".!,? ");
        }*/
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
    }
}