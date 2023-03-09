#include <iostream>
#include <climits>

using namespace std;

int mult(int base, int exp)
{
    if(exp == 0) return 1;

    return base * mult(base, exp-1);
}

int main()
{/*
    int b, e;
    std::cout << "Digite a base e o expoente inteiros: "; std::cin >> b >> e;

    std::cout << "Resultado: " << mult(b,e) << std::endl;

*/

    unsigned long long x = ULLONG_MAX;
    cout << x << endl;
    unsigned int y = (unsigned int) x;
    cout << y << endl;

}