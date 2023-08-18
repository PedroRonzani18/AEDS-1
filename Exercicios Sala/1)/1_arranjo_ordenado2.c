#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {

    // printf("Digite a quantidade de numeros: ");
    
    int n; scanf("%d",&n);
    int v[n];

    // printf("Digite a sequencia de numeros: ");

    for(int i=0; i<n; i++) scanf("%d",&v[i]);
    // printf("\n");

    for(int i=0; i<n; i++) 
    {

       if(v[i] == v[i+1]) 
       {
            for(int j=i+1; j<n; j++) 
            {
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

