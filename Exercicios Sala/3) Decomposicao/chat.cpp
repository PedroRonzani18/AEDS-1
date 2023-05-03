#include <iostream>
#include <vector>

using namespace std;

vector<vector<vector<int>>> carrega_map(int n) {
    vector<vector<vector<int>>> resultados(n+1);

    for (int i = 1; i <= n; i++) {
        resultados[i].push_back({i});
    }

    for (int i = 2; i <= n; i++) {
        resultados[i].reserve(n); // redimensiona o vetor com antecedência

        for (int j = i-1; j >= 1; j--) {
            for (const auto& decomposicao : resultados[i-j]) {
                if (j <= decomposicao[0]) {
                    auto nova_decomposicao = decomposicao;
                    nova_decomposicao.insert(nova_decomposicao.begin(), j);
                    resultados[i].push_back(nova_decomposicao);
                }
            }
        }
    }

    return resultados;
}

void printa_valores(const vector<vector<int>>& decomposicoes) {
    for (const auto& decomposicao : decomposicoes) {
        for (size_t i = 0; i < decomposicao.size()-1; i++) {
            cout << decomposicao[i] << " + ";
        }
        cout << decomposicao.back() << endl;
    }
}

void decompor(int n) {
    auto resultados = carrega_map(n);

    cout << "Decomposicao: \n";
    for (const auto& decomposicoes : resultados) {
        printa_valores(decomposicoes);
    }
}

int main() {
    cout << "Digite um numero inteiro: ";
    int n;
    cin >> n;

    decompor(n);

    return 0;
}
