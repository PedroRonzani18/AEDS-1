#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void remove_zeros_a_esquerda(vector<int>& v) 
{
    if(v.size() > 1) 
    {
        int cont=0;

        for(int i=v.size()-1; i >= 0; i--) // contabiliza quantidade de zeros a serem removidos
        {
            if(v[i] == 0) cont++;
            else break;
        }

        while(cont--) 
            v.pop_back();
    }
}

void multiplicar_vetor_por_numero(vector<int>& resultado, const int& num) 
{
    int vai1 = 0;
    for (size_t r = 0; r < resultado.size() || vai1 > 0; r++) // multiplica todos os algarismos pelo numero
    {
        if (r == resultado.size()) 
        {
            resultado.push_back(0); // se chegar ao final, coloca mais um zero para nao precisar de if na hora de somar
        }                        // adicionar 0 mesma coisa que somar so o vai1
                                 // remove necessidade de somar zeros adicionais para casos extremos

        int produto = resultado[r] * num + vai1; // menos um for se multiplicar numero direto ao inves de cada digito
        resultado[r] = produto % 10;
        vai1 = produto / 10;
    }
}

string factorial(const int& n) 
{
    vector<int> resultado; resultado.push_back(1); // numero fica ao contrario porem mais simples de trabalhar
    
    for (int i = 2; i <= n; i++) // multiplica por todos os numeros no fatorial 
    {
        multiplicar_vetor_por_numero(resultado, i);
        remove_zeros_a_esquerda(resultado);
    }

    reverse(resultado.begin(), resultado.end()); // coloca 

    string retorno = "";
    for(int& algarismo : resultado) 
        retorno += to_string(algarismo);
    return retorno;
}

int main() {

    cout << "Digite um numero inteiro: "; int n; cin >> n;

    cout << "Resultado: " << factorial(n) << endl;
    
    return 0;
}