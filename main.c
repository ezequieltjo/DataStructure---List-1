#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define QUANT_BUCKETS 100103

typedef struct Item{
    int key;
    char* palavra;
}Item;

typedef struct Dicionario{
    struct Item* item;
    struct Dicionario* proximo;
}Dicionario;

int comparar(char* entrada1, char* entrada2){
    int tm1 = strlen(entrada1);
    int tm2 = strlen(entrada2);

    if(tm1 != tm2){
        return 0;
    }

    int erro = 1;
    for(int cont = 0; cont < tm1; cont++){
        if(entrada1[cont] != entrada2[cont]){
            erro = 0;
            return erro;
        }
    }
    return erro;
}

int main(){

    Dicionario* buckets[QUANT_BUCKETS];
    for(int cont = 0; cont < QUANT_BUCKETS; cont++){
       buckets[cont] = NULL;
    }

    //while(scanf("%s", &palavra) != EOF){
    FILE* arq;

    if(arq = fopen("dicionario.txt", "r")){

    }else{
        printf("Erro ao abrir o arquivo de dicionario\n");
        return 0;
    }

    for(int cc = 0; cc<307855; cc++){
        char* palavra = (char*) malloc(38);
        //scanf("%s", palavra);
        fscanf(arq, "%s",palavra);
        //getchar();
        //printf("%s\n", palavra);

        unsigned long long int key = 0;
        int multiplicador = 0;
        for(int contador = 0; contador < strlen(palavra); contador++){
        	//key = key + palavra[contador]*54*(contador)*(contador+contador)*(contador)*(contador+contador+contador)*(contador)*(contador+contador+contador+contador);
        	key = key + palavra[contador]*54*54*(contador)*(contador+contador)*(contador+contador+contador+contador);
            //key = key + palavra[contador]*multiplicador;
            //multiplicador = 54+multiplicador;
        }
        int bucket = key%QUANT_BUCKETS;

        if(bucket < 0){
            bucket = bucket*-1;
        }

        if(buckets[bucket] == NULL){
            Item* item = (Item*) malloc(sizeof(Item));
            item->key = key;
            //item->palavra = (char*) malloc(strlen(palavra));
            item->palavra = palavra;
            buckets[bucket] = (Dicionario*) malloc(sizeof(Dicionario));
            buckets[bucket]->proximo = NULL;
            buckets[bucket]->item = item;
            //printf("Entrou %s\n", palavra);
        }else{
            //printf("Entrou %s", palavra);
            Item* item = (Item*) malloc(sizeof(Item));
            item->key = key;
            //item->palavra = (char*) malloc(strlen(palavra));
            item->palavra = palavra;
            Dicionario* auxiliar = buckets[bucket];
            Dicionario* dic = (Dicionario*) malloc(sizeof(Dicionario));
            dic->item = item;
            dic->proximo = auxiliar;
            buckets[bucket] = dic;
        }
    }

    fclose(arq);
    printf("Terminou de ler o arquivo de dicionario\n");

    FILE* histograma;

    if(histograma = fopen("bucket-colisoes.txt", "w")){

    }else{
    	histograma = fopen("bucket-colisoes.txt", "a");
    	fclose(histograma);
    	histograma = fopen("bucket-colisoes.txt", "w");
        //printf("Erro ao abrir o arquivo de bucket-colisoes\n");
        //return 0;
    }

    int maximoColisoes = 0;
    int vezesApareceu = 0;
    int vazios=0;
    int colisoesTotais=0;
    for(int cont = 0; cont < QUANT_BUCKETS; cont++){
        int colisoes = 0;
        Dicionario* dAux = NULL;

        if(buckets[cont] != NULL){
            dAux = buckets[cont];
        }

        while(dAux != NULL){
            colisoes++;
            //printf("Bucket: %i, Palavra: %s\n", cont, dAux->item->palavra);
            dAux = dAux->proximo;
        }

        fprintf(histograma, "%i\n", colisoes);

        colisoesTotais = colisoesTotais + colisoes;

        if(colisoes==0){
            vazios++;
        }

        if(colisoes > maximoColisoes){
            maximoColisoes = colisoes;
            vezesApareceu = 0;
        }
        else if(colisoes == maximoColisoes){
            vezesApareceu++;
        }
    }

    fprintf(histograma, "\nTotal de colisoes: %i\n", colisoesTotais);
    fprintf(histograma, "\nMaximo de colisoes em mesmo bucket: %i\n", maximoColisoes);

    printf("VAZIOS: %d\n", vazios);
    printf("COLISOES TOTAIS: %d\n", colisoesTotais);

    fclose(histograma);

    char pl[38];

    FILE* palavrasNaoEncontradas;

    int palavrasN = 0;
    int totalPalavras = 0;

    clock_t inicio = clock();

    palavrasNaoEncontradas = fopen("palavrasIncorretas.txt", "a");
    fclose(palavrasNaoEncontradas);

    if(!(palavrasNaoEncontradas = fopen("palavrasIncorretas.txt", "wr"))){
        printf("Erro ao abrir arquivo palavrasIncorretas\n");
        return 0;
    }

    while(scanf("%s", pl) != EOF){
        //printf("Entrou\n");
        //flush_in();
        unsigned long long int pkey = 0;
        int multiplicador = 0;
        for(int contador = 0; contador < strlen(pl); contador++){
            pkey = pkey + pl[contador]*54*54*(contador)*(contador+contador)*(contador+contador+contador+contador);
            //pkey = pkey + pl[contador]*multiplicador;
            //multiplicador = 54+multiplicador;
        }

        int buck = pkey%QUANT_BUCKETS;

        if(buck < 0){
            buck = buck*-1;
        }

        Dicionario* aux = buckets[buck];
        int encontrou = 0;

        while(aux != NULL){
            //printf("%s %s\n", aux->item->palavra, pl);
            if(comparar(aux->item->palavra,pl)){
                encontrou = 1;
                break;
            }
            aux = aux->proximo;
        }

        if(encontrou){
            //printf(": existe\n");

        }else{
            ///printf(": não existe\n");
            palavrasN++;
            fprintf(palavrasNaoEncontradas, "%s\n", pl);
        }
        totalPalavras++;

    }

    fclose(palavrasNaoEncontradas);

    FILE* saida;

    saida = fopen("saida.txt", "a");
    fclose(saida);

    if(!(saida = fopen("saida.txt", "w"))){
        printf("Erro ao abrir arquivo\n");
        return 0;
    }

    clock_t fim = clock();

    double tempo = (double) (fim-inicio)*1000/CLOCKS_PER_SEC;

    palavrasNaoEncontradas = fopen("palavrasIncorretas.txt", "r");

    fprintf(saida, "Número total de palavras no texto: %i\n", totalPalavras);
    fprintf(saida, "Tempo total de verificação: %lfms\n", tempo);
    fprintf(saida, "Número de palavras que falharam no spell check: %i\n", palavrasN);
    fprintf(saida, "Lista de palavras que falharam no spell check: %i\n", palavrasN);
    fprintf(saida, "Num. Ocorrencia - Palavra\n-----------------------------------------\n");

    for(int cont = 0; cont < palavrasN; cont++){
        char palavra[38];
        int repeticaoPalavra = 0;
        fscanf(palavrasNaoEncontradas, "%s", palavra);
        FILE* reserva;
        if(!(reserva = fopen("palavrasIncorretas.txt", "r"))){
            printf("Erro ao abrir arquivo\n");
            return 0;
        }
        for(int contar = 0; contar < palavrasN; contar++){
            char palavraArquivo[38];
            fscanf(reserva, "%s", palavraArquivo);
            if(comparar(palavra, palavraArquivo)){
                repeticaoPalavra++;
            }
        }
        fclose(reserva);
        fprintf(saida, "%i-%s\n", repeticaoPalavra, palavra);
    }

    fclose(palavrasNaoEncontradas);
    fclose(saida);

    printf("\nMaximo colisoes: %i\nVezes que repetiu: %i\n", maximoColisoes, vezesApareceu);

    return 0;
}
