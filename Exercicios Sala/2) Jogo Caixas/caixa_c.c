#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int* split(char* str, int n) {

    int* retorno = (int*)malloc(n * sizeof(int));    
    char * sub = strtok(str, " ");

    for(int i = 0; sub != NULL; i++) {
        retorno[i] = atoi(sub);
        sub = strtok(NULL, " ");
    }

    return retorno;
}


int main() {

    printf("Digite o nome do arquivo de entrada: "); 
    char* path = (char*)malloc(200 * sizeof(char*)); scanf("%s",path);

    FILE* f = fopen(path, "r");

    size_t buffsize = 200;
    char* buffer;
    int fileira=1, caixa=1, maior, numero_linhas;

    getline(&buffer, &buffsize, f); numero_linhas = atoi(buffer);
    getline(&buffer, &buffsize, f); maior = atoi(buffer);

    int soma_anterior = maior;
    
    for(int i=2; i<=numero_linhas; i++) {

        getline(&buffer, &buffsize, f);
        
        int* numeros_atuais = split(buffer, i);

        for(size_t j=0; j < i; j++) {

            if(soma_anterior + numeros_atuais[j] > maior) {

                maior = soma_anterior + numeros_atuais[j];
                caixa = j+1;
                fileira = i;
            }
        }

        for(int j=0; j<i; j++) 
            soma_anterior += numeros_atuais[j];
        

        free(numeros_atuais);
    }

    fclose(f);

    printf("Resposta: fileira %d, caixa %d.\n",fileira,caixa);

    free(path);
}