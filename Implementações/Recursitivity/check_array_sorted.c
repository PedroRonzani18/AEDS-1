#include <stdio.h>

// vai pro primeiro elemento e compara TODOS os casos => LENTO
int is_sorted(int arr[], int n) {

    if(n == 1) return (arr[n-1] <= arr[n]);

    return (1 && is_sorted(arr, n-1));
}

int is_sorted_2(int arr[], int ini, int fim)
{
    if(ini == fim-1) return 1;

    if(arr[ini] > arr[ini+1]) return 0;

    return is_sorted_2(arr, ini+1, fim);
}

int main()
{
    int v[] = {1,9,3,7,4,7,9,5,3};
    int v2[] = {1,2,3,4,-5,6};
    int n = sizeof(v2)/sizeof(int);

    printf("%d\n",is_sorted_2(v2,0,n-1));
}