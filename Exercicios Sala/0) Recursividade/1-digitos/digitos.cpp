#include <iostream>

int digitos(int n, int cont)
{
    if(n == 0) 
    {
        return 0;
    }

    n /= 10;
    cont++;

    return digitos(n, cont) + 1;
}

int main()
{
    int n;
    std::cout << "Digite um numero inteiro: "; std::cin >> n;

    int cont = 0;
    int result = digitos(n, cont);

    std::cout << "Resultado: " << result << std::endl;
}