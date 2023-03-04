#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <limits.h>

void all_subarrays(int arr[], int n)
{
    for(int i=1; i<=n; i++)// tamanho do subarray
    {
        for(int j=0; j< n; j++) // posicao inicial do subarray
        {
            for(int k=j; k-j < i; k++) // atual posição do ultimo termo do subarray do momento a ser printado
            {
                printf("%d,",arr[k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void all_subarrays_new(int arr[], int n)
{
    for(int i=0; i<n; i++)// tamanho do subarray || posição inicial do subarray
    {
        for(int j=i; j<n; j++) // posicao final do subarray
        {
            for(int k=i; k<=j; k++) // atual posição do ultimo termo do subarray do momento a ser printado || i <= k <= j
            {
                printf("%d,",arr[k]);
            }
            printf("\n");
        }
    }
}

// Brute Force O(n³)
int max_subarray_sum_n3(int arr[], int n)
{
    int max_sum = -1;

    for(int i=1; i<=n; i++) {// tamanho do subarray
        for(int j=0; j<=n-i; j++) {// posicao inicial do subarray
            int sum = 0;

            for(int k=j; k-j < i; k++) {
                sum += arr[k];
            }

            max_sum = fmax(sum, max_sum);
        }
    }

    return max_sum;
}

// Sum of Prefix O(n²)
int max_subarray_sum_n2(int arr[], int n)
{
    int* somas_ate_indices = (int*) malloc(n * sizeof(int));
    somas_ate_indices[0] = arr[0];

    int max_sum = -1;

    for(int i=0; i<n; i++) {
        somas_ate_indices[i] = somas_ate_indices[i-1] + arr[i];
    }

    for(int i=0; i<n; i++) {// posição inicial do subarray
        for(int j=i; j<n; j++) {// posicao final do subarray                                                                        // 1  2 3  4
            int sub_sum = i > 0 ? somas_ate_indices[j] - somas_ate_indices[i-1] : somas_ate_indices[j]; // 1 [3 6 10]
                                                                                                        // soma de subarr = soma 10 - soma 1 
            max_sum = fmax(max_sum, sub_sum);
        }
    }

    return max_sum;
}

// Kadane's Algorithm O(n)
int max_subarray_sum_n1(int arr[], int n) {
    int ans = INT_MIN, soma_ant = INT_MIN;

    for(int i=0; i<n; i++) {
        if(soma_ant < 0)
            soma_ant = arr[i]; // começa nova soma
        
        else
            soma_ant += arr[i]; // realiza nova soma
        ans = max(soma_ant, ans); // compara qual soma é maior
    }

    return ans;
}

int main()
{
    int arr[] = {-1-1-1-1-1};
    int n = sizeof(arr)/sizeof(int);
    // all_subarrays_new(arr,n);

    printf("%d\n",max_subarray_sum_n1(arr, n));
}