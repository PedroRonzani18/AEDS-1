#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<int> split(string& str)
{
    vector<int> retorno;
    stringstream ss(str);
    int num;

    while (ss >> num) {
        retorno.push_back(num);
    }

    return retorno;
}

int main() {

    cout << "Digite o nome do arquivo de entrada: "; string path; cin >> path;

    string linha;
    fstream arquivo;

    arquivo.open(path,fstream::in);

    int fileira=1, caixa=1, maior, numero_linhas;

    if(arquivo.is_open())
    {
        getline(arquivo,linha); 
        numero_linhas = stoi(linha);

        getline(arquivo,linha); 
        maior = stoi(linha);

        int soma_anterior = maior;

        for(int i=2; i<=numero_linhas; i++) {

            getline(arquivo,linha); // leio numeros
            vector<int> numeros_atuais = split(linha); // armazeno numeros atuais

            for(size_t j=0; j < numeros_atuais.size(); j++) {

                if(soma_anterior + numeros_atuais[j] > maior) {

                    maior = soma_anterior + numeros_atuais[j];
                    caixa = j+1;
                    fileira = i;
                }
            }

            for(int& num : numeros_atuais) {
                soma_anterior += num;
            }
        }
    }

    cout << "Resposta: fileira " << fileira << ", caixa " << caixa << ".\n";

    return 0;
}