#include <iostream>
#include <deque>
#include <string.h>

using namespace std;

deque<int> multiplicador_em_valores(int n) { // Retorna o multiplicador dentro de um deque
    deque<int> retorno;

    while(n > 0) {
        retorno.push_front(n % 10);
        n /= 10;
    }

    return retorno;
}

void adiciona_zeros(deque<int>& d, const size_t& num) {
    for(size_t o=0; o<num; o++, d.push_front(0));
}

void remove_zeros_a_esquerda(deque<int>& d){    
    if(d.size() > 1)
    {
        int cont = 0;

        for(const int& x : d) {
            if(x == 0) cont ++;
            else break;
        }

        for(int i=0; i<cont; i++, d.pop_front());
    }
}

string factorial(const int& n)
{
    deque<int> resultado; resultado.push_back(1);

    for(int c=2; c<=n; c++)
    {
        deque<int> multiplicador = multiplicador_em_valores(c); 
        deque<int> soma_das_microsomas;
                                                   // iteração zero-based para logica mais simples
        for(size_t m=0; m<multiplicador.size(); m++) // itera por toddos os algarismos do multiplicador
        {
            adiciona_zeros(soma_das_microsomas, resultado.size() + multiplicador.size()); // o produto tem no maximo a soma dos tamanhos dos mulipliccandos

            deque<int> microsoma; 
            adiciona_zeros(microsoma, resultado.size() + multiplicador.size()); // TODO:

            int vai1 = 0;

            // Realiza o produto entre todos os algarismos do result e um do multiplicador, e armazena em microsoma
            for(size_t pos=0; pos<resultado.size() || vai1>0; pos++) // cotnador de qual posição relativa ao numero deve avaliar
            {
                // como se iterasse ao contrario

                int produto_entre_algarismos = 
                    multiplicador[multiplicador.size()-1-m] * 
                    (pos < resultado.size() ? resultado[resultado.size()-1-pos] : 0)   
                    + vai1;
            
                // -m por causa dos extras zeros com as potencias de 10 do multiplicador
                microsoma[microsoma.size()-1-pos-m] = produto_entre_algarismos % 10;

                vai1 = produto_entre_algarismos / 10;

                if(pos == resultado.size()-1)// se nao tem mais o que multiplicar, e nao gerou +1, acaba
                {
                    if(vai1 == 0) break;
                    else microsoma[microsoma.size()-1-pos-m-1] += vai1;
                }
            }


            vai1=0;

            for(size_t pos=0; pos<microsoma.size() || vai1 > 0; pos ++)
            {
                int soma_entre_algarismos = 
                    microsoma[microsoma.size()-1-pos] + 
                    soma_das_microsomas[soma_das_microsomas.size()-1-pos] + 
                    vai1;

                soma_das_microsomas[soma_das_microsomas.size()-1-pos] = soma_entre_algarismos % 10;
                vai1 = soma_entre_algarismos / 10;
            
                if(pos == microsoma.size()-1)// se nao tem mais o que multiplicar, e nao gerou +1, acaba
                {
                    if(vai1 == 0) break;
                    else soma_das_microsomas[soma_das_microsomas.size()-1-pos-1] += vai1;
                }
            }

            remove_zeros_a_esquerda(soma_das_microsomas);
        }

        resultado = soma_das_microsomas;
    }

    remove_zeros_a_esquerda(resultado);
    string retorno = "";
    for(const int& algarismo : resultado) {
        retorno += to_string(algarismo);
    }
    return retorno;
}

int main() {
    cout << "Digite um numero inteiro: "; int n; cin >> n;

    cout << "Resultado: " << factorial(n) << endl;

    return 0;
}