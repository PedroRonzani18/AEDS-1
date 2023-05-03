#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<int,vector<vector<int>>> map_resultados;

void carrega(const int& base) {
    for(int current = 1; current <= base; current++) {
        map_resultados[current].push_back({current});
        for(int i=1; i<current; i++) {
            int resto = current - i;
            for(const vector<int>& representacoes : map_resultados[resto]){
                vector<int> vec_resto = representacoes; 
                vec_resto.insert(vec_resto.begin(), {i}); // escreve numero + representacao do resto
                map_resultados[current].insert(map_resultados[current].begin(), vec_resto); // adiciona representacao ao map 
            }
        }
    }
}



void printa_valores(const int& n) {
    for(const vector<int>& vi : map_resultados[n]) {
        for(size_t i=0; i<vi.size()-1; i++) {
            cout << vi[i] << " + ";
        }
        cout << vi.back() << endl;
    }
}

void decompor(const int& n) {
    carrega(n);
    printa_valores(n);
}

int main() {
    cout << "Digite um numero inteiro: "; int n; cin >> n;
    cout << "Decomposicao: \n";
    decompor(n);

    return 0;
}
