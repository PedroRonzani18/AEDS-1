#include <stdio.h>

int quantidade_casas(int* n)
{
    int cont;
    int nc = *n;

    if(nc == 0) return 1;

    for(cont = 0; nc > 0; cont++) nc /= 10;

    return cont;
}

void soma_digitos_util(int v[], int* soma, int n)
{
    if(n == 1) {
        *soma += v[n-1]; 
        return;
    }

    soma_digitos_util(v, soma, n-1); // transita denro do vetor até primeira posiçaõ

    *soma += v[n-1];
}

int soma_digitos(int* n)
{
    int size = quantidade_casas(n);
    int v[size];


    for(int i=0; i<size; i++)
    {
        v[i] = *n%10;

        *n /= 10;
    }

    int soma = 0;

    soma_digitos_util(v, &soma, size);

    return soma;
}

int main()
{
    int n; printf("Digite um numero: "); scanf("%d",&n);    

    printf("%d\n",soma_digitos(&n));
}