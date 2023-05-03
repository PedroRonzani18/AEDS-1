#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<int,vector<vector<int>>> map_resultados;

bool confere_ordem_decrescente(const vector<int>& v)
{
    for(size_t i=0; i<v.size()-1; i++) {
        if(v[i] < v[i+1]) return false; 
    }

    return true;
}

void carrega_map(int current, const int& base_num, int semi_focus = 1) 
{
    if(current > base_num || semi_focus > base_num) 
        return;

    if(current == 1) {
        carrega_map(current + 1, base_num, current + 1);
        return;
    }

    current--; 

    while(current > 0) 
    {
        int resto = semi_focus - current;

        for(size_t i=0; i<map_resultados[resto].size(); i++) {

            vector<int> vec_resto = map_resultados[resto][i]; vec_resto.insert(vec_resto.begin(), {current});

            if(confere_ordem_decrescente(vec_resto))
                map_resultados[semi_focus].push_back(vec_resto);
        }

        current --;
    }

    carrega_map(semi_focus + 1, base_num, semi_focus + 1); 
}

void printa_valores(const int& n) 
{
    for(vector<int> vi : map_resultados[n]) {
        for(size_t i=0; i<vi.size()-1; i++) {
            cout << vi[i] << " + ";
        }
        cout << vi.back() << endl;
    }
}

void decompor(const int& n) {

    for(int i=1; i<=n; i++) {
        map_resultados[i].push_back({i});
    }

    carrega_map(1, n);

    printa_valores(n);
}

int main() {
    cout << "Digite um numero inteiro: "; int n; cin >> n;

    cout << "Decomposicao: \n";
    decompor(n);

    return 0;
}