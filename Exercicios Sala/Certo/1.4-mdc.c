#include <stdio.h>
#include <math.h>

int mdc(int a, int b)
{
    if(a == 1 || b == 1) {
        return 1;
    }

    int continuar = 1;

    for(int i=2; i<fmax(a,b) && continuar == 1; i++) {
        if(a%i == 0 && b%i == 0) {
            continuar = 0;
            return i * mdc(a/i, b/i);
        }
    }

    return 1;
}

int main()
{
    int a,b; printf("Digite dois numeros inteiros: "); scanf("%d %d",&a,&b);

    printf("Resultado: %d\n",mdc(a,b));
}