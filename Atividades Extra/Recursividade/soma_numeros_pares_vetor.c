#include <stdio.h>

void positivos(int v[], int n, int* soma) {
    if(n == 1) {
        if(n % 2 == 0) 
            soma += v[n-1];
        return;
    }

    positivos(v, n-1, soma);

    if(v[n-1] % 2 == 0) 
        *soma += v[n-1];
}

int soma_positivos(int v[], int n) {
    int soma = 0;

    positivos(v, n, &soma);

    return soma;
}


int main() {
    int v[] = {1,2,3,4,5,6};
    int n = sizeof(v) / sizeof(int);
    printf("%d\n",soma_positivos(v,n));
}