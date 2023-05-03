#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_zeros_a_esquerda(int* v, int* n) 
{
    if(*n > 1) 
    {
        int cont=0;

        for(int i=*n-1; i >= 0; i--) // contabiliza quantidade de zeros a serem removidos
        {
            if(v[i] == 0) cont++;
            else break;
        }

        // while(cont--) 
        //     v.pop_back();
        v = (int*) realloc(v, *n - cont);
        *n -= cont;
    }

}

void multiplicar_vetor_por_numero(int* resultado, int num, int* n) 
{
    int vai1 = 0;
    for (size_t r = 0; r < *n || vai1 > 0; r++) // multiplica todos os algarismos pelo numero
    {
        if (r == *n) 
        {
            *n = *n + 1;
            resultado = (int*) realloc(resultado, *n);
            resultado[*n-1] = 0;
            //resultado.push_back(0); // se chegar ao final, coloca mais um zero para nao precisar de if na hora de somar
        }                        // adicionar 0 mesma coisa que somar so o vai1
                                 // remove necessidade de somar zeros adicionais para casos extremos

        int produto = resultado[r] * num + vai1; // menos um for se multiplicar numero direto ao inves de cada digito
        resultado[r] = produto % 10;
        vai1 = produto / 10;
    }
}

int* factorial(int n, int* size_return) 
{
    int* resultado = (int*) malloc(1 * sizeof(int)); resultado[0] = 1;; // numero fica ao contrario porem mais simples de trabalhar
    
    int size = 1;

    for (int i = 2; i <= size; i++) // multiplica por todos os numeros no fatorial 
    {
        multiplicar_vetor_por_numero(resultado, i, &size);
        remove_zeros_a_esquerda(resultado, &size);
    }

    *size_return = size;
    return resultado;
}

int main() {

    int n;
    printf("Digite um numero inteiro: "); scanf("%d",&n);

    int size;

    printf("Resultado: "); int* fact = factorial(n,&size);
    
    for(int i=size-1; i>=0; i--) {
        printf("%d",fact[i]);
    }
    printf("\n");
    
    return 0;
}