#include <stdio.h>
#include <math.h>

int mdc(int a, int b)
{
    if(a == 1 || b == 1) 
        return 1;

    for(int i=2; i<=fmin(a,b); i++)  // enquanto nao encontrar um numero que e divisivel por ambos
        if(a%i == 0 && b%i == 0) 
            return i * mdc(a/i, b/i);

    return 1;
}

int main()
{
    int a,b; printf("Digite dois numeros inteiros: "); scanf("%d %d",&a,&b);

    printf("Resultado: %d\n",mdc(a,b));
}