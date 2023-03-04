#include <stdio.h>

int first(int arr[], int n, int k) {
    // Caso base
    if(n == 0) return -1;

    /// Movimenta ate o primeiro elemento
    int ans = first(arr, n-1, k);

    // Se ainda nao havia encontrado, e agora encontrou, retorna o indice
    if(ans == -1 && arr[n] == k) return n;

    // Aqui das duas uma: ans=-1 mas ainda nao achou || ans != -1 mas arr[n] != k -> primeira ocorrencia ja encontrada
    return ans;
}

int last(int arr[], int n, int k) {
    // Se chegou antes do primeiro elemento, quer dizer que nao encontou
    if(n == 0) return -1;

    // Como é reverso, faz a coisa antes de se mover pra pegar o termo mais a "direita"
    if(arr[n-1] == k) return n-1;

    // Se move pra tras
    return last(arr, n-1, k);
}

int main()
{
    int v[] = {1,5,3,6,5,6,5};
    int n = sizeof(v) / sizeof(int);

    printf("%d\n",last(v,n,1));
}