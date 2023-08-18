#include <iostream>

int digitos(int n)
{
    if(n == 0) return 1;

    if(n >= 10)
        return digitos(n/10) + 1;
    else
        return digitos(n/10);
}

int main()
{
    int n; std::cout << "Digite um numero inteiro: "; std::cin >> n;

    int result = digitos(n);

    std::cout << "Resultado: " << result << std::endl;
}