#include "arq.h"

// Funcao de criacao do descritor da lista - Pedro Vargas
struct descritor *cria()
{
    struct descritor *desc = malloc(sizeof(struct descritor));
    if (desc == NULL)
    {
        return NULL;
    }
    desc->numLinhas = 0;
    desc->primeiraLinha = NULL;
    return desc;
}
// Funcao de importacao do texto para a lista - Pedro Vargas
int importaTexto(struct descritor *desc, FILE *fp)
{
    int numLinha = 0;

    desc->primeiraLinha = malloc(sizeof(struct noLinha));

    if (desc->primeiraLinha == NULL)
        return -1;

    char linha[900];

    struct noLinha *aux = malloc(sizeof(struct noLinha));

    while (fgets(linha, 900, fp) != NULL) // Esse while le ate o final do arquivo
    {
        int numPalavras = 0;
        numLinha += 1;
        int numCol = 1;
        int acabouPal = FALSE;
        int acabouLin = FALSE;
        int quantEspacos = 0;
        struct noLinha *temp = malloc(sizeof(struct noLinha));
        if (temp == NULL)
        {
            return -1;
        }
        temp->lin = numLinha;
        temp->primeiraPalavra = malloc(sizeof(struct noPalavra));
        struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));

        char *palavra = calloc(40, sizeof(char));
        int i2 = 0;                                    // Esse i2 sera usado para servir de indice da palavra
                                                       // Representando cada caractere
        for (int i = 0; i < strlen(linha) + 1; i += 1) // Esse for le ate o final da linha
        {
            if (linha[i] == '\n' || linha[i] == '\0')
            {
                acabouLin = TRUE;
            }
            if (linha[i] == ' ') // A logica por tras desse bloco else if eh basicamente contar quantos espacos
            {                    // tem apos a atual palavra e settar a flag que a palavra acabou
                quantEspacos += 1;
                acabouPal = TRUE;
            }
            if (!acabouLin && !acabouPal)
            {

                palavra[i2] = linha[i];
                i2 += 1;
            }
            if (acabouLin || (acabouPal && linha[i] != ' ')) // Condicao indicando que a palavra ja acabou e os espacos tambem, ou que a linha acabou
            {                                                // ou seja, a proxima palavra comecou
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
                acabouPal = FALSE;
                i2 = 0;
                memset(palavra,0,40*sizeof(char)); // Reset da palavra lida
                                                     // caractere da proxima palavra - Pedro Vargas
                numPalavras += 1;
                if (acabouLin)
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
// Funcao que exibe o texto a partir da lista - Gustavo Felipe
int exibeTexto(struct descritor *desc)
{
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    if (aux != NULL)
    {

        aux = desc->primeiraLinha;
        while (aux != NULL)
        {
            int col = 1;
            struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));
            if (aux2 != NULL)
            {
                aux2 = aux->primeiraPalavra;
                while (aux2->palavra != NULL)
                {
                    while (col < aux2->col)
                    {
                        printf(" ");
                        col += 1;
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