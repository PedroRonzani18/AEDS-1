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

int Vazia(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e o seguinte ao apontado por p --- */
    TipoApontador q;

    if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
    {
        printf("Erro Lista vazia ou posicao nao existe\n");
        return;
    }
    q = p->Prox;
    *Item = q->Item;
    p->Prox = q->Prox;
    if (p->Prox == NULL)
        Lista->Ultimo = p;
    free(q);
}

/* ======================================================================================================================================== */
  
int *vetor_cores;
int *vetor_modelo;

TipoLista lista_intervalos;
TipoLista lista_valores;

int vetor_cores_size;
int quantidade_valores_lidos;

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

    getline(arquivo, linha); quantidade_valores_lidos = stoi(linha);
    getline(arquivo, linha); lista_valores = split(linha); // armazena quantidade de linhas

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

void adiciona_item(TipoItem auxItem, int cont, int index) {

    int valor;
    
    for (int j = 0; j < 3; j++) {
        if (auxItem.Chave == vetor_cores[j])
            valor = j+1;
    }

    TipoItem inserido; 
        inserido.Tipo = valor;
        inserido.NumElementos = cont;
        inserido.PontoMedio = index - cont/2;
    Insere(inserido, &lista_intervalos);
}

void contagem_valores()
{
    FLVazia(&lista_intervalos);
    
    int cont = 1;

    TipoItem auxItem;
    
    int i;
    for(i = 0; i < quantidade_valores_lidos-1; i++) {
        Retira(lista_valores.Primeiro, &lista_valores, &auxItem);
        
        if(auxItem.Chave != lista_valores.Primeiro->Prox->Item.Chave) {
            adiciona_item(auxItem, cont, i);

            cont = 1;
        } else {
            cont ++;
        }
    }
    
    Retira(lista_valores.Primeiro, &lista_valores, &auxItem);

    adiciona_item(auxItem, cont, i);
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