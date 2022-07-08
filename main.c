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
    printf("Numero total da palavra Teste: %d\n",numTotalCertaPalavra(desc, "Teste"));

    int *ocorrencias1 = buscaPalavra(desc, "teste");
    if(ocorrencias1 != NULL){
        for(int i = 0; i < ocorrencias1[0]*2; i += 2){
            printf("(%d,%d)\n",ocorrencias1[i+1],ocorrencias1[i+2]);
        }
    }

    int *ocorrencias = numSubPalavra(desc, "tes");
    if(ocorrencias != NULL){
        printf("Numero de ocorrencia da subString: %d\n", ocorrencias[0]);
        for(int i = 0; i < ocorrencias[0]*2; i += 2){
            printf("(%d,%d)\n",ocorrencias[i+1],ocorrencias[i+2]);
        }
    }
    printf("Numero de palavras: %d\n",numTotalPalavra(desc));

    insercao(desc, "alo", 16, 3);
    exibeTexto(desc);

    return 0;
}
