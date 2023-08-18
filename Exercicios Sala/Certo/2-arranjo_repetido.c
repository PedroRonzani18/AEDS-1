#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
Dado um arranjo de números inteiros ordenados de forma ascendente, remova os números repetidos in situ 
(no próprio arranjo, sem usar outro arranjo auxiliar) de forma que cada elemento apareça uma única vez. 
A ordem relativa dos elementos tem que ser mantida.

O resultado deverá ser mantido na primeira parte do arranjo de números, ou seja, se existirem K elementos 
após a remoção dos números repetidos, então as K primeiras posições do arranjo devem conter o resultado final. 
Os números após a posição K serão ignorados.

A entrada do programa é um número inteiro N e, em seguida, uma sequência de N números inteiros. 
A saída será a quantidade de elementos finais e a sequência final de números.
*/

int main() {

    printf("Digite a quantidade de numeros: ");
    
    int n; scanf("%d",&n);
    int v[n];

    printf("Digite a sequencia de numeros: ");

    for(int i=0; i<n; i++) scanf("%d",&v[i]);
    printf("\n");

    for(int i=0; i<n; i++) {
       if(v[i] == v[i+1]) {
            for(int j=i+1; j<n; j++) {
                v[j] = v[j+1]; 
            }
            n --;
            i--;
        }
    }

    printf("Resultado: existe(m) %d numero(s) na sequencia final\n",n);
    printf("Sequencia final: ");

    for(int i=0; i<n-1; i++) {
        printf("%d ",v[i]);
    }
    printf("%d\n",v[n-1]);
}

