#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int tamanhoVec (int num){
    return (1+num)*num/2;
}

int* create_vctor(char* arquivo, int* tamanho) {
    FILE* fp;
    fp = fopen(arquivo, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    fscanf(fp, "%i ", tamanho);
    *tamanho = tamanhoVec(*tamanho);

    int* vetor = (int*) malloc(*tamanho+1 * sizeof(int));

    for (int i = 0; i < *tamanho; i++) {
        fscanf(fp, "%d ", &vetor[i]);
    }

    //fclose(fp);

    return vetor;
}

int qunatidade_de_linhar(int num) {
    int cont = 0;
    int soma = 0;

    while(soma < num) {
        soma += cont;
        cont ++;
    }

    return (cont -1);
}

int main(){

    int tamanho;

    char arquivo[200];

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s",arquivo);

    int* vetor = create_vctor(arquivo, &tamanho);

    int num_linhas = qunatidade_de_linhar(tamanho);

    int melhor_linha = 1, melhor_coluna = 1, soma_anteriores_total = vetor[0], soma_com_current = vetor[0];

    int maior_soma = vetor[0];

    int quantidade_ja_lida = 1;

    for(int linha = 2; linha <= num_linhas; linha++) {

        for(int atual = quantidade_ja_lida; atual < quantidade_ja_lida + linha; atual ++) {

            if(soma_anteriores_total + vetor[atual] > maior_soma ) {

                maior_soma = soma_anteriores_total + vetor[atual];
                melhor_coluna = atual - quantidade_ja_lida + 1;
                melhor_linha = linha;
            }
            soma_com_current += vetor[atual];
        }

        quantidade_ja_lida += linha;

        soma_anteriores_total = soma_com_current;
    }

    printf("Resposta: fileira %d, caixa %d.",melhor_linha,melhor_coluna);

    free(vetor);

    return 0;
}
