#include <stdio.h>

void swap(int* a, int* b) {

    int aux = *a;
    *a = *b;
    *b = aux;
}

void bubble_sort(int arr[], int n) {
    
    for(int i=1; i<n; i++) {
        for(int j=0; j < n-i; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void bubble_sort_recursive_1(int arr[], int n) {

    if(n == 1) return;

    for(int j=0; j < n-1; j++) {
        if(arr[j] > arr[j+1]) {
            swap(arr[j], arr[j+1]);
        }
    }

    bubble_sort_recursive_1(arr, n-1);
}

void bubble_sort_recursive_2(int arr[], int n, int j) {
    if(n  == 1) return;

    if(j == n-1) // se j chegou ao final do arr, recomeça porem com um subarr sem o ultimo termo do atual subarr
        bubble_sort_recursive_2(arr, n-1, 0); 

    if(arr[j] > arr[j+1]) {
        swap(arr[j], arr[j+1]);
    }

    // fica realizando j++ até sair la em cima
    bubble_sort_recursive_2(arr, n, j+1); 
}

