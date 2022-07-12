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
                if (palavra[0] != '\n' && palavra[0] != '\0') // nao contar linhas vazias como palavra - Gustavo F. Pereira
                    numPalavras += 1;
                memset(palavra, 0, 40 * sizeof(char)); // Reset da palavra lida
                                                       // caractere da proxima palavra - Pedro Vargas
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
    return 0;
}
// Funcao que exibe o texto a partir da lista - Gustavo Felipe
int exibeTexto(struct descritor *desc)
{
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra)); // mudei os mallocs pra fora do while pra nao usar malloc varias vezes sem necessidade Gustavo F. P.

    if (aux != NULL && aux2 != NULL)
    {

        aux = desc->primeiraLinha;
        while (aux != NULL)
        {
            int col = 1;
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

            printf("\n");
            aux = aux->proxLin;
        }
    }
    return 0;
}

// Funcao que exibe do número total de ocorrências de uma palavra - Gustavo Konescki Fuhr
int numTotalCertaPalavra(struct descritor *desc, char *palavra) // Modifiquei palavra para um ponteiro para manter o encapsulamento - Pedro V
{
    // Mudei a declaracao dos ponteiros para fora do while porque eles iriam ficar mallocando desnecessariamente - Pedro V
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));
    int totPalavra = 0;
    if (aux == NULL || aux2 == NULL)
        return -1;
    aux = desc->primeiraLinha;

    while (aux != NULL)
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
        aux = aux->proxLin;
    }
    return totPalavra; // Mudei o printf() que tinha aqui para apenas retornar a quantidade de ocorrencias de uma palavra
                       // já que o input e o output de informacoes nao ocorre nessa camada do programa, mas sim na main - Pedro V
}

// Funcao que retorna a posicao das palavras no texto - Pedro Vargas
// Essa funcao retorna um ponteiro pra int como array, que tem sempre um numero impar de elementos
// O primeiro elemento representa a quantidade de ocorrencias de uma determinada palavra
// Depois do primeiro elemento, ha sempre uma sequencia de pares de numeros
// O primeiro do par representa a linha e o segundo a coluna da ocorrencia da palavra
int *buscaPalavra(struct descritor *desc, char *palavra)
{
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));
    int *ocorrencias = malloc(sizeof(int));
    int ocSize = 3;
    int total = 0;
    if (aux == NULL || aux2 == NULL)
        return NULL;
    aux = desc->primeiraLinha;

    while (aux != NULL)
    {
        aux2 = aux->primeiraPalavra;
        while (aux2->palavra != NULL)
        {
            if (strcmp(palavra, aux2->palavra) == 0)
            {
                total += 1;
                ocorrencias = realloc(ocorrencias, (ocSize) * sizeof(int));
                ocorrencias[ocSize - 2] = aux->lin;
                ocorrencias[ocSize - 1] = aux2->col;
                ocSize += 2;
            }
            aux2 = aux2->proxPal;
        }
        aux = aux->proxLin;
    }
    ocorrencias[0] = total;
    return ocorrencias;
}

// funcao que retorna o numero total de palavras. Gustavo Felipe
int numTotalPalavra(struct descritor *desc)
{
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    int totPalavra = 0;
    if (aux == NULL)
        return -1;
    aux = desc->primeiraLinha;
    while (aux != NULL)
    {
        totPalavra += aux->numPalavras;
        aux = aux->proxLin;
    }
    return totPalavra;
}
// Funcao que remove uma determinada palavra do texto - Pedro Vargas
int removePalavra(struct descritor *desc, char *palavra)
{
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));
    int removeu = FALSE;

    if (aux == NULL || aux2 == NULL)
        return -1;
    aux = desc->primeiraLinha;

    while (aux != NULL)
    {
        aux2 = aux->primeiraPalavra;
        while (aux2->palavra != NULL)
        {
            if (strcmp(palavra, aux2->palavra) == 0)
            {
                removeu = TRUE;
                if (aux2->antPal != NULL)
                {
                    aux2->antPal->proxPal = aux2->proxPal;
                }
                else
                {
                    aux->primeiraPalavra = aux2->proxPal;
                }
                if (aux2->proxPal != NULL)
                {
                    aux2->proxPal->antPal = aux2->antPal;
                }
                free(aux2);
                aux->numPalavras -= 1;
            }
            aux2 = aux2->proxPal;
        }
        aux = aux->proxLin;
    }
    return removeu;
}
// Funcao que remove uma determinada palavra do texto - Pedro Vargas
int removePalavraPos(struct descritor *desc, int lin, int col)
{
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));
    int removeu = FALSE;

    if (aux == NULL || aux2 == NULL)
        return -2;
    aux = desc->primeiraLinha;

    while (aux != NULL)
    {
        if (aux->lin == lin)
            break;
        aux = aux->proxLin;
    }
    if (aux == NULL)
        return 0;
    aux2 = aux->primeiraPalavra;
    while (aux2 != NULL)
    {
        if (aux2->col == col)
        {
            removeu = TRUE;
            if (aux2->antPal != NULL)
            {
                aux2->antPal->proxPal = aux2->proxPal;
            }
            else
            {
                aux->primeiraPalavra = aux2->proxPal;
            }
            if (aux2->proxPal != NULL)
            {
                aux2->proxPal->antPal = aux2->antPal;
            }
            free(aux2);
            aux->numPalavras -= 1;
        }
        aux2 = aux2->proxPal;
    }
    return removeu;
}
// funcao que dada uma string, retorna as ocorrencias das substrings. Gustavo Felipe e Pedro Vargas
char **subString(struct descritor *desc, char *pal)
{

    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));
    char **retorno = malloc(sizeof(char *));
    char **repetidas = malloc(sizeof(char *));
    int quant = 1;
    int quantRepetidas = 1;
    int repetida = FALSE;
    int ehSub = FALSE;
    if (aux == NULL || aux2 == NULL || retorno == NULL)
        return NULL;
    aux = desc->primeiraLinha;
    while (aux != NULL)
    {
        aux2 = aux->primeiraPalavra;
        while (aux2->palavra != NULL)
        {
            // Esse for verifica se a palavra eh substring da outra - Pedro Vargas
            for (int i = 0; aux2->palavra[i] != '\0'; i += 1)
            {
                ehSub = FALSE;
                for (int j = 0; pal[j] != '\0'; j++)
                {
                    if (aux2->palavra[i + j] != pal[j])
                    {
                        ehSub = FALSE;
                        break;
                    }
                    ehSub = TRUE;
                }
                if (ehSub)
                {
                    // Este for verifica se a palavra que foi encontrada nao eh repetida
                    for (int x = 0; x < quantRepetidas - 1; x += 1)
                    {
                        if (strcmp(aux2->palavra, repetidas[x]) == 0)
                        {
                            repetida = TRUE;
                            break;
                        }
                    }
                    if (!repetida)
                    {
                        quant += 1;
                        retorno = realloc(retorno, quant * sizeof(char *));
                        retorno[quant - 2] = malloc(sizeof(aux2->palavra));
                        strcpy(retorno[quant - 2], aux2->palavra);
                    }
                    quantRepetidas += 1;
                    repetidas = realloc(repetidas, quantRepetidas * sizeof(char *));
                    repetidas[quantRepetidas - 2] = calloc(1, sizeof(aux2->palavra));
                    strcpy(repetidas[quantRepetidas - 2], aux2->palavra);
                    repetida = FALSE;
                    break;
                }
            }
            aux2 = aux2->proxPal;
        }
        aux = aux->proxLin;
    }
    if (quant == 1)
        return NULL;
    retorno = realloc(retorno, (quant) * sizeof(char *));
    retorno[quant - 1] = NULL; // Mantem a ultima string do vetor de strings igual a NULL para percorrer ele na main - Pedro Vargas
    return retorno;
}

// funcao que dada uma posicao de uma palavra existente e uma nova palavra, troca a antiga pela nova. Gustavo Felipe
int edicaoPalavra(struct descritor *desc, int lin, int col, char *pal)
{
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));
    int espaco = 0;
    int editou = FALSE;
    if (aux == NULL || aux2 == NULL)
        return -1;
    aux = desc->primeiraLinha;

    while (aux != NULL)
    {
        if (aux->lin == lin)
            break;
        aux = aux->proxLin;
    }
    if (aux == NULL)
        return 0;
    aux2 = aux->primeiraPalavra;
    while (aux2->palavra != NULL)
    {
        if (aux2->col == col)
        {
            editou = TRUE;
            espaco = strlen(pal) - strlen(aux2->palavra);
            strcpy(aux2->palavra, pal);
            if (aux2->proxPal != NULL)
            {
                while (aux2->proxPal != NULL)
                {
                    aux2->proxPal->col = aux2->proxPal->col + espaco;
                    aux2 = aux2->proxPal;
                }
            }
        }
        aux2 = aux2->proxPal;
    }
    aux = aux->proxLin;

    return editou;
}

int insercao(struct descritor *desc, char *palavra)
{
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));
    int inseriu = FALSE;

    if (aux == NULL || aux2 == NULL)
        return -1;

    aux = desc->primeiraLinha;
    while (aux->proxLin != NULL)
    {
        aux = aux->proxLin;
    }

    aux2 = aux->primeiraPalavra;

    while (aux2->proxPal != NULL)
    {
        aux2 = aux2->proxPal;
    }
    struct noPalavra *temp = malloc(sizeof(struct noPalavra));
    temp->col = aux2->col + strlen(aux2->palavra) + 1;
    strcpy(temp->palavra, palavra);
    aux2->proxPal = temp;
    temp->proxPal = NULL;
    temp->antPal = aux2;
    inseriu = TRUE;
    return inseriu;
}
// Funcao que salva o arquivo por Gustavo Kon
int atualizaArquivo(struct descritor *desc, FILE *fp)
{
    FILE *novoFp = fopen("arqTemp.txt", "w");
    if (novoFp == NULL)
        return 0;
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));

    if (aux == NULL || aux2 == NULL)
        return 0;

    aux = desc->primeiraLinha;
    while (aux != NULL)
    {
        int col = 1;
        aux2 = aux->primeiraPalavra;
        while (aux2->palavra != NULL)
        {
            while (col < aux2->col)
            {
                fprintf(novoFp, " ");
                col += 1;
            }
            fprintf(novoFp, "%s", aux2->palavra);
            col += strlen(aux2->palavra);
            aux2 = aux2->proxPal;
        }
        fprintf(novoFp, "\n");
        aux = aux->proxLin;
    }
    fclose(novoFp);
    fclose(fp);
    remove("OldArquivo.txt");
    rename("arq.txt", "OldArquivo.txt");
    rename("arqTemp.txt", "arq.txt");
    return 1;
}
// Funcao que destroi lista - Pedro Vargas
int destroi(struct descritor *desc)
{
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));
    if ((aux == NULL) | (aux2 == NULL))
        return -1;
    aux = desc->primeiraLinha;
    while (aux->proxLin != NULL)
    {
        aux2 = aux->primeiraPalavra;
        if (aux2 != NULL)
        {
            while (aux2->proxPal != NULL)
            {
                aux2 = aux2->proxPal;
                free(aux2->antPal);
            }
            free(aux2);
        }
        aux = aux->proxLin;
        free(aux->antLin);
    }
    if (aux != NULL)
    {
        aux2 = aux->primeiraPalavra;
        if (aux2 != NULL)
        {
            while (aux2->proxPal != NULL)
            {
                aux2 = aux2->proxPal;
                free(aux2->antPal);
            }
            free(aux2);
        }
        free(aux);
    }
    return 0;
}