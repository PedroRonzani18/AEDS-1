#include <stdio.h>
#include <time.h>

// Metodo tradicional O(n)
int pot(int b, int e) {
    if(e == 0) return 1;
    
    return b * pot(b, e-1);
}

// Divide pela metade O(log(n))
int fast_pot(int b, int e) {
    if(e == 0) return 1;

    int sub_problem = fast_pot(b, e/2);

    if(e%2 != 0) return b * sub_problem;
    return sub_problem * sub_problem;
}

int main()
{
    printf("%d\n",fast_pot(2,8));
}