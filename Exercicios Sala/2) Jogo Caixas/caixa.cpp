#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> split(std::string str)
{
    std::vector<std::string> retorno;
    std::stringstream ss(str);
    std::string word;

    while (ss >> word) {
        retorno.push_back(word);
    }

    return retorno;
}

int main() {

    printf("Digite o nome do arquivo de entrada: "); std::string path; std::cin >> path;

    std::string linha;
    std::fstream arquivo;
    std::vector<std::string> valores;

    arquivo.open(path,std::fstream::in);

    int fileira, caixa, maior, numeros_linhas;

    if(arquivo.is_open())
    {
        getline(arquivo,linha); // quuantidade de linhas

        numeros_linhas = std::stoi(linha);

        getline(arquivo,linha); // primeira caixa

        maior = stoi(linha); caixa = 1; fileira = 1;

        std::vector<int> numeros_anteriores; numeros_anteriores.push_back(maior);
        std::vector<int> numeros_atuais;
        int soma_anterior = 0;

        for(int i=2; i<=numeros_linhas; i++) {

            getline(arquivo,linha); // leio numeros

            std::vector<std::string> numeros_srings = split(linha); // armazeno numeros atuais

            for(std::string str : numeros_srings) {
                numeros_atuais.push_back(std::stoi(str));
            }

            for(int num : numeros_anteriores) {
                soma_anterior += num;
            }

            for(size_t j=0; j < numeros_atuais.size(); j++) {

                if(soma_anterior + numeros_atuais[j] > maior) {

                    maior = soma_anterior + numeros_atuais[j];
                    caixa = j+1;
                    fileira = i;
                }
            }

            numeros_anteriores.resize(0);

            for(int num : numeros_atuais) {
                numeros_anteriores.push_back(num);
            }

            numeros_atuais.resize(0);

        }
    
    }

    printf("Resposta: fileira %d, caixa %d.\n",fileira,caixa);

    return 0;
}