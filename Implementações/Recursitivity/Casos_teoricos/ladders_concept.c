#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int ladders(int n) {

    if(n == 0) return 1;
    if(n < 0) return 0;

    return ladders(n-1) + ladders(n-2) + ladders(n-3); // só pode dar pulos de tamanho 1, 2 ou 3 pra chegar no final da escada
}

int* ladders_;

int ladders_dinamic(int n) {

    if(n == 0 || n == 1) return ladders_[n] = 1;
    if(n < 0) return 0;

    ladders_[n] = ladders_dinamic(n-1) + ladders_dinamic(n-2) + ladders_dinamic(n-3); 

    return ladders_[n]; // só pode dar pulos de tamanho 1, 2 ou 3 pra chegar no final da escada
}

int main() {

    clock_t start = clock();

    int n; printf("Numero de degraus: "); scanf("%d",&n);

    ladders_ = (int*)malloc(n * sizeof(int));

    printf("%d\n",ladders_dinamic(n));

    clock_t end = clock();

    printf("Tempo: %f\n",(float)(end-start)/CLOCKS_PER_SEC);
}