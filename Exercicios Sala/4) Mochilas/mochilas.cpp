/****************

LAED1 - Problema da Mochila

Alunos(as): Pedro Augusto de Portilho Ronzani, Ulisses Andrade Carvallho

Data: 30/04/2023

****************/

#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define rf(i,e,s) 	   for(int i=e-1;i>=s;i--)

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

vector<int> capacidades_mochilas;
vector<pair<int, int>> itens; // peso e valor
vector<vector<int>> solucoes; // matriz de 0 e 1
vector<int> soma_valores;
int quant_mochilas;
int num_itens;
int soma_otima_valores = 0;

void leitura_arquivo() {

    cout << "Digite o nome do arquivo: "; string path; cin >> path;

    string linha;
    fstream arquivo;

    arquivo.open(path, fstream::in);

    getline(arquivo, linha); quant_mochilas = stoi(linha); // armazena quantidade de linhas
    getline(arquivo, linha); capacidades_mochilas = split(linha); // armazena capacidades das mochilas
    getline(arquivo, linha); num_itens = stoi(linha); // armazena quantidade de itens

    for(int i=0; i<num_itens; i++) {
        getline(arquivo, linha);
        vector<int> par = split(linha);
        itens.push_back(make_pair(par[0], par[1]));
    }

    for(int i=0; i<num_itens; i++) {
        getline(arquivo, linha); 
        solucoes.push_back(split(linha));
    }

    arquivo.close();
}

// verifica se é inviavel
bool caso_inviavel() {
    soma_valores.resize(quant_mochilas);

    for(int i=0; i<quant_mochilas; i++) {

        int peso=0; 
        for(int j=0; j<num_itens; j++) {

            if(solucoes[j][i]) {

                peso += itens[j].first;
                soma_valores[i] += itens[j].second; 
            }
        }        
        if(peso > capacidades_mochilas[i]) {
            return true;
        }
    }

    return false;
}

vector<int> decimal_to_binary(const int& n) {
    vector<int> ret;

    if(n == 0) {
        ret.push_back(0);
        return ret;
    }

    for(int i=n; i>0; i/=2)
        ret.push_back(i%2);
    

    reverse(ret.begin(), ret.end());
    return ret;
}

void verifica_casos(int index_mochila) {

    for(int k=0; k<quant_mochilas && !itens.empty(); k++) {
        map<int,int> numero_frequencia;

        int maior_valor = 0;
        vector<int> itens_usados;


        for(size_t i=0; i<pow(2,itens.size()); i++) {
            vector<int> linha = decimal_to_binary(i);

            int soma_subconj_atual_valor = 0;
            int soma_subconj_atual_peso = 0;

            for(size_t j=0; j<linha.size(); j++) {
                if(linha[linha.size() -1 - j] == 1) {
                    soma_subconj_atual_valor += itens[itens.size() - 1 - j].second;
                    soma_subconj_atual_peso += itens[itens.size() - 1 - j].first;
                }
            }

            if(soma_subconj_atual_peso <= capacidades_mochilas[index_mochila]) { // se couber na mochila
                if(soma_subconj_atual_valor > maior_valor) { // se esse valor total for o maior até agora, muda                
                    maior_valor = soma_subconj_atual_valor;
                    itens_usados = linha;
                }

                if(!(soma_subconj_atual_valor < maior_valor)) // anota frequencia dos maiores valores
                    numero_frequencia[soma_subconj_atual_peso] += 1;
            }
        }

        soma_otima_valores += maior_valor;

        vector<int> posicoes_a_remover;

        for(size_t i=0; i<itens_usados.size(); i++) { // encontra posições na mochila dos itens usados
            if(itens_usados[itens_usados.size()-1-i] == 1) {
                posicoes_a_remover.push_back(itens_usados.size()-i);        
            }
        }

        for (int i = posicoes_a_remover.size() - 1; i >= 0; i--) {
            itens.erase(itens.begin() + posicoes_a_remover[i] - 1);
        }
    }
}

void confere_resposta_passada() 
{
    int soma_geral_passada = 0;

    for(const int& valor : soma_valores)
        soma_geral_passada += valor;

    if(soma_geral_passada < soma_otima_valores) cout << "Solucao viavel mas nao otima.\n";
    else if(soma_geral_passada == soma_otima_valores) cout << "Solucao otima.\n";
    else cout << "merda: " << soma_geral_passada << " " << soma_otima_valores << "\n";
}

int main() {

    leitura_arquivo();

    if(caso_inviavel())  {
        cout << "Solucao inviavel.\n";
        return 0;
    }

    // vai eonctrar melhor caso para uma mochila, depois com o resto vai para a proxima
    for(int i=0; i<quant_mochilas && !itens.empty(); i++)
        verifica_casos(i);     

    confere_resposta_passada();
}
