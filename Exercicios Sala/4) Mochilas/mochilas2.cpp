/****************

LAED1 - Problema da Mochila

Alunos(as): Pedro Augusto de Portilho Ronzani, Ulisses Andrade Carvallho

Data: 02/05/2023

****************/


#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <iostream>
#include <fstream>
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

// zulisses top funcoes
pair<int, int> sumComb(vector<int> binario, vector<pair<int, int>> itens_local) //retorna peso + valor
{
    int sum_peso = 0, sum_valor = 0;

    for(size_t i = 0; i < binario.size(); i++){
    
        if(binario[i])
        {
            sum_peso += itens_local[i].first;
            sum_valor += itens_local[i].second;
        }
    }
    return make_pair(sum_peso, sum_valor);
}

vector<int> decToBi(int num)
{
    vector<int> aux;
    while(num > 1)
    {
        aux.push_back(num%2);
        num /= 2;
    }
    aux.push_back(num);

    return aux;
}


void remove(const vector<int>& binario, vector<pair<int, int>>& itens_local)
{
    rf(i, binario.size(), 0) {
        if(binario[i]){
            itens_local.erase(itens_local.begin() + i);
        }
    }
}

int melhor_caso_geral(const vector<pair<int, int>> &itens_local, const size_t &index_mochila)
{    
    if(itens_local.empty()) return 0; // se nao tiverem mais itens para comparar, retorna
    if(index_mochila == capacidades_mochilas.size()) return 0; // se  nao tiverem mais mochilas, retorna

    int maior_soma_local = 0;

    for(int i = 0; i < pow(2, itens_local.size()); i++) { 

        vector<pair<int, int>> itens_aux = itens_local; // vector de itens antes de ser alterado

        vector<int> combinacao = decToBi(i);

        pair<int,int> somaComb = sumComb(combinacao, itens_aux);

        if(somaComb.first <= capacidades_mochilas[index_mochila]) {
            remove(combinacao, itens_aux); // remove os itens ja usados
            
            int soma_recursividade = melhor_caso_geral(itens_aux, index_mochila + 1); // chamo função recursiva
        
            soma_recursividade += somaComb.second; // soma local adiciona o item dessa iteracao

            if(soma_recursividade > maior_soma_local) {
                maior_soma_local = soma_recursividade;
            }
        }
    }

    return maior_soma_local;
}

void confere_resultado(int result)
{
    int soma_geral_passada = 0;

    for(const int& valor : soma_valores)
        soma_geral_passada += valor;

    if(soma_geral_passada < result) cout << "Solucao viavel mas nao otima.\n";
    else if(soma_geral_passada == result) cout << "Solucao otima.\n";
}

int main() {

    leitura_arquivo();

    if(caso_inviavel())  {
        cout << "Solucao inviavel.\n";
        return 0;
    }

    int result = melhor_caso_geral(itens, 0);

    confere_resultado(result);
        
}