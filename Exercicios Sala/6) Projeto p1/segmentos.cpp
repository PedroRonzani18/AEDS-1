/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Alunos(as): Pedro Augusto de Portilho Ronzani, Ulisses Andrade Carvallho

Data: 23/05/2023

****************/

#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/*===========================================*/

typedef int TipoChave;

typedef struct
{
    int Chave;
    int Tipo;
    int NumElementos;
    int PontoMedio;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct
{
    TipoApontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

void Insere(TipoItem x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

/* ======================================================================================================================================== */

int *vetor_cores;
int *vetor_modelo;

TipoLista lista_intervalos;
TipoLista valores_lidos;

int vetor_cores_size;
int quantidade_valores_lidos;

void imprime_valores(TipoLista Lista)
{
    TipoCelula *Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        printf("%d ", Aux->Item.Tipo);
        Aux = Aux->Prox;
    }
    printf("\n");

    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        printf("%d ", Aux->Item.NumElementos);
        Aux = Aux->Prox;
    }
    printf("\n");

    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        printf("%d ", Aux->Item.PontoMedio);
        Aux = Aux->Prox;
    }
    printf("\n");
}

TipoLista split(const string &str)
{
    TipoLista retorno; FLVazia(&retorno);
    stringstream ss(str);
    TipoItem numero;

    while (ss >> numero.Chave)
        Insere(numero, &retorno);
    
    return retorno;
}

void leitura_arquivo()
{
    cout << "Digite o nome do arquivo: "; string path; cin >> path;

    string linha;
    fstream arquivo;

    arquivo.open(path, fstream::in);

    getline(arquivo, linha); quantidade_valores_lidos = stoi(linha) + 1;
    getline(arquivo, linha); valores_lidos = split(linha); // armazena quantidade de linhas

    arquivo.close();
}

void cria_vetores_modelo()
{    
    vetor_cores = (int *)malloc(3 * sizeof(int));
    vetor_cores[0] = 0;
    vetor_cores[1] = 128;
    vetor_cores[2] = 255;

    vetor_modelo = (int*) malloc(5 * sizeof(int));
    vetor_modelo[0] = 1;
    vetor_modelo[1] = 3;
    vetor_modelo[2] = 2;
    vetor_modelo[3] = 3;
    vetor_modelo[4] = 1;    
}

void contagem_valores()
{
    FLVazia(&lista_intervalos);

    int valor;
    int cont = 0;

    for (int j = 0; j < 3; j++) {
        if(valores_lidos.Primeiro->Item.Chave == vetor_cores[j])
            valor = j+1;
    }

    int initial_index = 0;

    TipoCelula *anterior = valores_lidos.Primeiro;
    TipoCelula *Aux = anterior->Prox;

    for (int i = 1; i < quantidade_valores_lidos; i++, Aux = Aux->Prox, anterior = anterior->Prox) {

        if (Aux->Item.Chave != anterior->Item.Chave) {

            TipoItem inserido; 
                inserido.Tipo = valor;
                inserido.NumElementos = cont;
                inserido.PontoMedio = (i-1 + initial_index)/2;
            Insere(inserido,&lista_intervalos);
            initial_index = i;

            for (int j = 0; j < 3; j++) {
                if (Aux->Item.Chave == vetor_cores[j])
                    valor = j+1;
            }
            cont = 1;
        } else {
            cont++;
        }
    }

    TipoItem inserido; 
        inserido.Tipo = valor;
        inserido.NumElementos = cont;
        inserido.PontoMedio = (quantidade_valores_lidos-1 + initial_index)/2;
    Insere(inserido,&lista_intervalos);
}

void verifica_conter_padrao() {

    for(TipoCelula* auxI = lista_intervalos.Primeiro->Prox; auxI != NULL; auxI = auxI->Prox) {
        
        if(auxI->Item.Tipo == vetor_modelo[0]) {

            bool padrao_encontrado = true;
            TipoCelula* iterador = auxI;

            for(int j=0; j<5; j++, iterador = iterador->Prox) {
                if(iterador == NULL) {
                    cout << "Resultado: Padrao nao encontrado.\n";
                    return;
                }

                if(vetor_modelo[j] != iterador->Item.Tipo) {
                    padrao_encontrado = false;
                    break;
                }
            }
            if(padrao_encontrado) {
                cout << "Resultado: Padrao encontrado.\n";
                return;
            }
        }
    }

    cout << "Resultado: Padrao nao encontrado.\n";
}

int main()
{
    leitura_arquivo();
    cria_vetores_modelo();
    contagem_valores();
    verifica_conter_padrao();
}