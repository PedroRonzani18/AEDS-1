/****************

LAED1 - Análise de segmentos com elementos iguais

Alunos(as): Pedro Augusto de Portilho Ronzani, Ulisses Andrade Carvallho

Data: 12/05/2023

****************/

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int *values;
int values_size;
int *values_no_repetition;
int values_no_repetition_size;
int **matriz_final;

vector<int> split(string &str)
{
    vector<int> retorno;
    stringstream ss(str);
    int num;

    while (ss >> num)
    {
        retorno.push_back(num);
    }

    return retorno;
}

void leitura_arquivo()
{
    cout << "Digite o nome do arquivo: ";
    string path;
    cin >> path;

    string linha;
    fstream arquivo;

    arquivo.open(path, fstream::in);

    getline(arquivo, linha);
    getline(arquivo, linha);

    vector<int> numeros = split(linha); // armazena quantidade de linhas

    arquivo.close();

    values_size = numeros.size();
    values = (int *)malloc(values_size * sizeof(int));

    for (int i = 0; i < values_size; i++) 
        values[i] = numeros[i];
}

void remove_repeticao()
{
    values_no_repetition = (int *)malloc(values_size * sizeof(int));

    for (int i = 0; i < values_size; i++)
        values_no_repetition[i] = values[i];

    sort(values_no_repetition, values_no_repetition + values_size);

    int j = 1;

    for (int i = 1; i < values_size; i++) {
        if (values_no_repetition[i] != values_no_repetition[i - 1]) {
            values_no_repetition[j] = values_no_repetition[i];
            j++;
        }
    }

    values_no_repetition_size = j;
    values_no_repetition = (int*) realloc(values_no_repetition, values_no_repetition_size);
}

void contagem_valores()
{
    int quantidade_intervalos = 1;

    for (int i = 1; i < values_size; i++) {
        if (values[i] != values[i - 1])
            quantidade_intervalos++;
    }

    matriz_final = (int **)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++)
        matriz_final[i] = (int *)malloc(quantidade_intervalos * sizeof(int));

    int indice_matrix = 0;
    int cont = 1;
    int valor;

    for (int j = 0; j < values_no_repetition_size; j++) {
        if (values[0] == values_no_repetition[j])
            valor = j+1;
    }

    for (int i = 1; i < values_size; i++) {

        if (values[i] != values[i - 1]) {

            matriz_final[0][indice_matrix] = valor;
            matriz_final[1][indice_matrix] = cont;

            indice_matrix++;

            for (int j = 0; j < values_no_repetition_size; j++) {

                if (values[i] == values_no_repetition[j])
                    valor = j+1;
            }
            cont = 1;

        } else {
            cont++;
        }

    }

    matriz_final[0][indice_matrix] = valor;
    matriz_final[1][indice_matrix] = cont;

    cout << "Matriz:\n";
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < quantidade_intervalos -1; j++)
        {
            cout << matriz_final[i][j] << " ";
        }
        cout << matriz_final[i][quantidade_intervalos-1] << endl;
    }
}

int main()
{
    leitura_arquivo();
    remove_repeticao();
    contagem_valores();
}