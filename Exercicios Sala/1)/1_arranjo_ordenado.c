#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main() {
    
    printf("Digite a quantidade de numeros: "); 
    int n; scanf("%d",&n);

    int enc = 0;

    printf("Digite a sequencia de numeros: ");

    int* v;

    int find = 0;
    if(n > 0) {
        v = (int*)malloc(n * sizeof(int));

        for(int i=0; i<n; i++) {
            scanf("%d",&v[i]);
        }

        for(int i=0; i<n-1; i++) {

            if(v[i] == v[i+1] && v[i] > INT_MIN) {

                enc ++;
                for(int j=i; j<n-1; j++) {
                    v[j] = v[j+1];
                }
                v[n-enc] = INT_MIN;

                if(i > 0) i--;
            }        
        }

        for(int i=0; i<n; i++) {

            if(v[i] == INT_MIN) 
                break;
            find ++;

        }
    }

    printf("\nResultado: existe(m) %d numero(s) na sequencia final\n",find);

    printf("Sequencia final: ");

    if(n > 0) {
        v = realloc(v, find);

        for(int i=0; i<find-1; i++) {
            printf("%d ",v[i]);
        }
        printf("%d",v[find-1]);
    }
    printf("\n");
}
