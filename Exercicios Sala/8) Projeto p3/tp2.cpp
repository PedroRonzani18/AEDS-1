/****************

LAED1 - Projeto (Parte II) - Estimativa do formato da pista

Alunos: Pedro Augusto de Portilho Ronzani, Ulisses Andrade Carvallho

Data: 02/06/2023

****************/

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/* ======================================================================================================================================== */

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

TipoLista* matriz_intervalos;
TipoLista* matriz_valores;

TipoLista index_padrao;

int colunas;
float linhas;

// separa numeros por espaço
TipoLista split(const string &str)
{
    TipoLista retorno; FLVazia(&retorno);
    stringstream ss(str);
    TipoItem numero;

    while (ss >> numero.Chave)
        Insere(numero, &retorno);
    
    return retorno;
}

// leitura do arquivo de teste
void leitura_arquivo()
{
    cout << "Digite o nome do arquivo: "; string path; cin >> path;

    string linha;
    fstream arquivo;

    arquivo.open(path, fstream::in);

    getline(arquivo, linha); linhas = stoi(linha);

    matriz_valores = (TipoLista*) malloc(linhas * sizeof(TipoLista));

    for(int i=0; i<linhas; i++) {
        getline(arquivo, linha); colunas = stoi(linha);
        getline(arquivo, linha); matriz_valores[i] = split(linha); // armazena quantidade de linhas        
    }

    arquivo.close();
}

// cria vetores de cores e padrao a ser encontrado
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

// função que simula lista[i]
TipoItem item_index(const TipoLista& lista, const int& index) {
    TipoCelula *Aux = lista.Primeiro->Prox;
    
    for (int i=0; i<index; i++) 
        Aux = Aux->Prox;

    return Aux->Item;
}

// verrifica qual intervalo caracteriza aquele valor, e adiciona um item à matriz de intervalos
void adiciona_item(const TipoItem& auxItem, const int& cont, const int& index, const int& linha) {

    int valor;
    
    for (int j = 0; j < 3; j++) {
        if (auxItem.Chave == vetor_cores[j])
            valor = j+1;
    }

    TipoItem inserido; 
        inserido.Tipo = valor;
        inserido.NumElementos = cont;
        inserido.PontoMedio = index - cont/2;
    Insere(inserido, &matriz_intervalos[linha]);
}

// itera pela matriz de valores e faz a leitura dos valores
void contagem_valores()
{
    matriz_intervalos = (TipoLista*) malloc(linhas * sizeof(TipoLista));
    for(int j=0; j<linhas; j++) {
        FLVazia(&matriz_intervalos[j]);
        
        int cont = 1;

        TipoItem auxItem;
        
        int i;
        for(i = 0; i < colunas-1; i++) {
            Retira(matriz_valores[j].Primeiro, &matriz_valores[j], &auxItem);

            if(auxItem.Chave != matriz_valores[j].Primeiro->Prox->Item.Chave) {
                adiciona_item(auxItem, cont, i, j);

                cont = 1;
            } else {
                cont ++;
            }
        }
        
        Retira(matriz_valores[j].Primeiro, &matriz_valores[j], &auxItem);

        adiciona_item(auxItem, cont, i, j);
    }
}

// verifica se o padrao 1 3 2 3 1 se encontra em algum lugar da matriz de intervalos
int verifica_conter_padrao(const int& i, int& index_central) {

    int k=0;
    for(TipoCelula* auxI = matriz_intervalos[i].Primeiro->Prox; auxI != NULL; auxI = auxI->Prox, k++) {
        
        if(auxI->Item.Tipo == vetor_modelo[0]) {

            bool padrao_encontrado = true;
            TipoCelula* iterador = auxI;

            for(int j=0; j<5; j++, iterador = iterador->Prox) {
                if(iterador == NULL) {
                    index_central = -1;
                    return 0;
                }

                if(vetor_modelo[j] != iterador->Item.Tipo) {
                    padrao_encontrado = false;
                    break;
                }
            }
            if(padrao_encontrado) {
                index_central = item_index(matriz_intervalos[i], k+2).PontoMedio;
                return 1;
            }
        }
    }

    index_central = -1;
    return 0;
}

// verifica em qual tipo de pista essa se encaixa
void verifica_tipagem_pista() {

    float quantidade_linhas_padrao = 0;

    TipoLista lista_indices; FLVazia(&lista_indices);

    for(int i=0; i<linhas; i++) {
        TipoItem index_central;
        quantidade_linhas_padrao += verifica_conter_padrao(i, index_central.Chave);
        
        if(index_central.Chave != -1)
            Insere(index_central, &lista_indices);
    }

    if(quantidade_linhas_padrao / linhas < 0.7 - 1e-6) { // erro de precisão float
        cout << "Resultado: Formato da pista nao estimado.\n";
        return;
    }

    TipoCelula *Aux = lista_indices.Primeiro->Prox;

    while (Aux->Prox != NULL) Aux = Aux->Prox;

    int distancia = Aux->Item.Chave - lista_indices.Primeiro->Prox->Item.Chave;
    float limite = 0.1 * colunas;

    if(distancia < -limite) cout << "Resultado: Curva a direita.\n";
    else if (distancia > limite) cout << "Resultado: Curva a esquerda.\n";
    else  cout << "Resultado: Pista em linha reta.\n";
}

int main()
{
    leitura_arquivo();
    cria_vetores_modelo();
    contagem_valores();
    verifica_tipagem_pista();
}