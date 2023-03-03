#include <iostream>

void dec2bin(int n)
{
    if(n == 0) 
    {
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

    if(n == 0)
    {
        std::cout << 0;
    }
    else
        dec2bin(n);

    std::cout << std::endl;
}