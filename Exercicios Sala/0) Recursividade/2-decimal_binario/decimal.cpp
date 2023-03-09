#include <iostream>

void dec2bin(int n)
{
    if(n == 0 or n == 1) 
    {
        std::cout << n;
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

    dec2bin(n);

    std::cout << std::endl;
}