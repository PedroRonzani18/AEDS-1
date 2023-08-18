#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/*
Este jogo consiste de uma pilha de caixas de determinado valor em que cada fileira contém uma caixa a mais que a fileira anterior. 
O competidor deve escolher uma caixa e seu prêmio será a soma dos valores da caixa escolhida mais os valores de todas as caixas das fileiras acima dela, 
ou seja, todas as caixas das fileiras acima serão incluídas no cálculo também, sejam positivas ou negativas. 
Se o competidor fizer uma escolha ruim, o valor poderá ser negativo e não haverá prêmio.

Por exemplo, para a seguinte configuração de caixas, a segunda caixa da terceira fileira deverá ser escolhida para obter o maior prêmio, 
cujo valor é igual a 17.

Jogo: https://drive.google.com/file/d/1bWl-0Sjl6OD-fQ2AZEexswpCOCABqb9K/view?usp=sharing

Para este exercício, o programa deverá determinar qual caixa deverá ser escolhida para maximizar o valor do prêmio.

Os valores das caixas serão fornecidos em um arquivo cujo formato segue a seguinte descrição: na primeira linha, 
há um número inteiro N representando o número de fileiras da pilha de caixas. 
As linhas seguintes contêm, cada uma, os valores das caixas de cada fileira separados por espaços. 
A primeira fileira é a mais ao topo e, em cada fileira, a primeira caixa é a mais à esquerda.
*/

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