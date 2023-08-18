#include <iostream>
#include <vector>
#include <map>

/*
Faça um programa para gerar a decomposição de um número inteiro positivo na soma de todos os possı́veis fatores 
*/

using namespace std;

map<int,vector<vector<int>>> map_resultados; // para cada chave (numero) armazena vectors com numeros cujas somas são as chaves

bool confere_ordem_decrescente(const vector<int>& v) // confere se essa representacao e valida
{
    for(size_t i=0; i<v.size()-1; i++) {
        if(v[i] < v[i+1]) return false; 
    }

    return true;
}

void carrega(const int& base) {

    for(int current = 2; current <= base; current++) { // preencho map de 2 até n com suas representacoes

        for(int i=current-1; i>0; i--) { // itera por todos os números anteriores ao número atual
            
            for(const vector<int>& representacoes : map_resultados[current - i]){ // itera por todas as representacoes do numero

                vector<int> vec_resto = representacoes; 
                vec_resto.insert(vec_resto.begin(), {i}); // escreve numero + representacao do resto

                if(confere_ordem_decrescente(vec_resto))
                    map_resultados[current].push_back(vec_resto); // adiciona representacao ao map 
            }
        }
    }
}

void printa_valores(const int& n) 
{
    for(const vector<int>& vi : map_resultados[n]) {
        for(size_t i=0; i<vi.size()-1; i++) {
            cout << vi[i] << " + ";
        }
        cout << vi.back() << endl;
    }
}

void decompor(const int& n) {

    for(int i=1; i<=n; i++) map_resultados[i].push_back({i}); // preenche map com valores padrao
    
    carrega(n);
    printa_valores(n);
}

int main() {
    cout << "Digite um numero inteiro: "; int n; cin >> n;
    cout << "Decomposicao: \n";
    decompor(n);

    return 0;
}