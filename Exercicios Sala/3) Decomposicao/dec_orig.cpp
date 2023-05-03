#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

map<int,vector<string>> map_resultados;

bool confere_ordem_decrescente(const string& str)
{
    stringstream ss; ss << str;
    int found;  

    vector<int> v;

    while (!ss.eof()) {
 
        string temp;
        ss >> temp;
 
        if (stringstream(temp) >> found){
            v.push_back(found);
        }
    }

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

        if(!map_resultados[resto].empty()) {

            for(size_t i=0; i<map_resultados[resto].size(); i++) {
                if(confere_ordem_decrescente(to_string(current) + " + " + map_resultados[resto][i]))
                    map_resultados[semi_focus].push_back(to_string(current) + " + " + map_resultados[resto][i]);
            }
        }
        current --;
    }

    current = semi_focus;
    carrega_map(current + 1, base_num, current + 1); 
}

void printa_valores(const int& n) 
{
    for(string str : map_resultados[n]) {
        cout << str << endl;
    }
}

void decompor(const int& n) {

    for(int i=1; i<=n; i++) {
        map_resultados[i].push_back(to_string(i));
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