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
//Funcao que remove uma determinada palavra do texto - Pedro Vargas
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
                    aux2->proxPal->antPal = NULL;
                }
                if(aux2->proxPal != NULL)
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
//Funcao que remove uma determinada palavra do texto - Pedro Vargas
int removePalavraPos(struct descritor *desc, int lin, int col)
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
            if (aux->lin == lin && aux2->col == col)
            {
                removeu = TRUE;
                if (aux2->antPal != NULL)
                {
                    aux2->antPal->proxPal = aux2->proxPal;
                }
                else
                {
                    aux->primeiraPalavra = aux2->proxPal;
                    aux2->proxPal->antPal = NULL;
                }
                if(aux2->proxPal != NULL)
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


int insercaoPorPos(struct descritor *desc, char *palavra, int linha, int coluna)
{
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra)); 
    
    if (aux != NULL && aux2 != NULL)
    {
        aux = desc->primeiraLinha;
        while (aux->lin != linha) // Verifica se é a linha desejada //
        {
            if (aux->proxLin != NULL) // Se proxima linha existir pula pra ela //
            {
                aux = aux->proxLin;
            }
            else // Se não existir, cria a proxima linha e pula pra ela //
            {
                aux->proxLin = malloc(sizeof(struct noLinha)); 
                struct noLinha *temp = malloc(sizeof(struct noLinha));
                if (temp == NULL)
                {
                    return -1;
                }
                temp = aux->proxLin;
                temp->numPalavras = 0;
                temp->primeiraPalavra = NULL;
                temp->antLin = aux;
                temp->proxLin = NULL;
                temp->lin = aux->lin + 1;
                free(temp);
                aux = aux->proxLin;
            }
        }
        aux2 = aux->primeiraPalavra;
        if (aux2 == NULL) // É uma linha sem palavras //
        {
            aux2 = malloc(sizeof(struct noPalavra)); 
            aux2->col = coluna;
            aux2->antPal = NULL;
            aux2->proxPal = NULL;
            strcpy(aux2->palavra, palavra);
        }
        else
        {   
            if (aux2->col < coluna && aux2->col+strlen(aux2->palavra) > coluna) // Verifica se a coluna da primera palavra está entre coluna desejada //
            {
                return 0;
            }  
            if (aux2->col > coluna) // A palavra inserida sera a primeira palavra
            {
                struct noPalavra *temp2 = malloc(sizeof(struct noPalavra));
                if (temp2 == NULL)
                {
                    return -1;
                }
                temp2->col = coluna;
                strcpy(temp2->palavra, palavra);
                temp2->proxPal = aux2;
                temp2->antPal = NULL;
                aux->primeiraPalavra = temp2;
                aux2->antPal = temp2;
                free(temp2);       
                aux2->col = aux2->col + strlen(palavra);             
                while (aux2 -> proxPal != NULL) // Arruma a coluna das proximas palavras da linha //
                {
                    aux2->col = aux2->col + strlen(palavra);
                    aux2 = aux2->proxPal;
                }
            }
            else
            {
                while (aux2->col < coluna && aux2->proxPal!=NULL) // Verifica se passou da coluna desejada, ou seja, a palavra é a anterio de Aux2 // 
                {
                    aux2 = aux2->proxPal;
                    if (aux2->col < coluna && aux2->col+strlen(aux2->palavra) > coluna) // Verifica se a coluna da primera palavra está entre coluna desejada //
                    {
                        return 0;
                    }      
                }
                if (aux2->proxPal==NULL) // A palavra é a ultima palavra //
                {
                    aux2->proxPal = malloc(sizeof(struct noPalavra)); 
                    struct noPalavra *temp2 = malloc(sizeof(struct noPalavra));
                    if (temp2 == NULL)
                    {
                        return -1;
                    }
                    temp2 = aux2->proxPal;
                    temp2->proxPal = NULL;
                    temp2->col = coluna;
                    temp2->antPal = aux2;
                    strcpy(temp2->palavra, palavra);
                    free(temp2);
                }
                else // A palavra está entre duas palavras //
                {
                    struct noPalavra *temp2 = malloc(sizeof(struct noPalavra));
                    if (temp2 == NULL)
                    {
                        return -1;
                    }
                    temp2->col = coluna;
                    strcpy(temp2->palavra, palavra);
                    temp2->proxPal = aux2;
                    temp2->antPal = aux2->antPal;
                    aux2->antPal->proxPal = temp2;
                    aux2->antPal = temp2;
                    free(temp2);  
                    aux2->col = aux2->col + strlen(palavra);                  
                    while (aux2 -> proxPal != NULL) // Arruma a coluna das proximas palavras da linha //
                    {
                        aux2->col = aux2->col + strlen(palavra);
                        aux2 = aux2->proxPal;
                    }
               }  
            }
        }
    }
    return 0;
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
    temp->antPal = aux;
    free(temp);
    inseriu = TRUE;
    return inseriu;
}

int atualizaArquivo(struct descritor *desc, FILE *fp)
{
    FILE *novoFp = fopen("arqTemp.txt","w");
    if (novoFp == NULL)
        return -1;
    struct noLinha *aux = malloc(sizeof(struct noLinha));
    struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));

    if (aux == NULL || aux2 == NULL)
        return -1;

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
    rename("teste.txt", "OldArquivo.txt");
    rename("arqTemp.txt", "teste.txt");
    return 1;
}
