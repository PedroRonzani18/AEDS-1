#include <iostream>

void dec2bin(int n)
{
    if(n/2 == 0) 
    {
        std::cout << n%2;
        return;
    }
    dec2bin(n/2);

    std::cout << n % 2;
}

int main()
{
    int n;
    std::cout << "Digite um numero inteiro: "; std::cin >> n;

    std::cout << "Resultado: ";

    for(int i=0; i<=n; i++) 
    dec2bin(i), std::cout << std::endl;

    std::cout << std::endl;
}