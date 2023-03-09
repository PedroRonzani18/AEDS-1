#include <stdio.h>

void dec(int n) {

    if(n == 0) return;

    printf("%d ",n);
    
    dec(n-1);
}

void inc(int n) { // vai ate o final do vetor, depois faz as coisas
    
    // Caso Base
    if(n == 0) return;

    // Movimentação
    inc(n-1);

    // Ação
    printf("%d ",n);
}

int main()
{
    dec(5);
    printf("\n");
    
    inc(5);
    printf("\n");
}

