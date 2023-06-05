#include <stdio.h>

void MaxMin3 (int A[], int *Max, int *Min, int n) {

    int i, FimDoAnel;
    if ((n % 2) > 0) { //se n é ímpar, duplica último elemento
        A[n] = A[n-1]; FimDoAnel = n;
    }
    else FimDoAnel = n - 1;

    if (A[0] > A[1]) *Max = A[0], *Min = A[1];
    else             *Max = A[1], *Min = A[0];

    for(i=3; i<= FimDoAnel; i += 2) {

        if (A[i-1] > A[i]) {
            if (A[i-1] > *Max) *Max = A[i-1];
            if (A[i] < *Min)   *Min = A[i];
        }
        else {
            if (A[i-1] < *Min) *Min = A[i-1];
            if (A[i] > *Max)   *Max = A[i];
        }
    }
}

int main() {

    int v[6] = {1,2,3,4,5,6};

    int max, min; MaxMin3(v, &max, &min, 6);

    printf("%d %d\n",max,min);
}