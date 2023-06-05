#include <stdio.h>
#include <stdlib.h>

#define MAXTAM 70
#define CANCELACARATER '#'
#define CANCELALINHA '\\'
#define CANCELAPALAVRA '$'
#define SALTALINHA '*'
#define MARCAEOF '~'
typedef char TipoChave;

typedef struct
{
    TipoChave Chave;

} TipoItem;

typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct
{
    TipoApontador Fundo, Topo;
    int Tamanho;
} TipoPilha;

void FPVazia(TipoPilha *Pilha)
{
    Pilha->Topo = (TipoApontador)malloc(sizeof(TipoCelula));
    Pilha->Fundo = Pilha->Topo;
    Pilha->Topo->Prox = NULL;
    Pilha->Tamanho = 0;
}

int Vazia(TipoPilha Pilha)
{
    return (Pilha.Topo == Pilha.Fundo);
}

void Empilha(TipoItem x, TipoPilha *Pilha)
{
    TipoApontador Aux;
    Aux = (TipoApontador)malloc(sizeof(TipoCelula));
    Pilha->Topo->Item = x;
    Aux->Prox = Pilha->Topo;
    Pilha->Topo = Aux;
    Pilha->Tamanho++;
}

void Desempilha(TipoPilha* Pilha, TipoItem* Item)
{
    TipoApontador q;
    if (Vazia(*Pilha))
    {
        printf("Erro : lista vazia\n");
        return;
    }
    q = Pilha->Topo;
    Pilha->Topo = q->Prox;
    *Item = q->Prox->Item;
    free(q);
    Pilha->Tamanho--;
}

void Imprime(TipoPilha *Pilha)
{
    TipoPilha Pilhaux;
    TipoItem x;
    FPVazia(&Pilhaux);
    while (!Vazia(*Pilha))
    {
        Desempilha(Pilha, &x);
        Empilha(x, &Pilhaux);
    }
    while (!Vazia(Pilhaux))
    {
        Desempilha(&Pilhaux, &x);
        putchar(x.Chave);
    }
    putchar('\n');
}

int Tamanho(TipoPilha Pilha)
{
    return (Pilha.Tamanho);
}

/*===================================================================*/

void removePalavras(TipoPilha* Pilha) {
    TipoItem letra;
    int palavra_encontrada = 0;

    while(!palavra_encontrada) {
        Desempilha(Pilha, &letra);
        if(letra.Chave != ' ') 
            palavra_encontrada = 1;
    }

    int espaco_encontrado = 0;

    while(!espaco_encontrado) {
        Desempilha(Pilha, &letra);
        if(letra.Chave == ' ') 
            espaco_encontrado = 1;    
    }
}

void et(TipoPilha* Pilha) {

    TipoItem x; x.Chave = getchar();
    if (x.Chave == '\n')
        x.Chave = ' ';

    while(x.Chave != MARCAEOF) {
        switch (x.Chave) {

            case CANCELACARATER:
                if (!Vazia(*Pilha)) Desempilha(Pilha, &x);
                break;

            case CANCELALINHA: FPVazia(Pilha);break;

            case CANCELAPALAVRA: removePalavras(Pilha); break;

            case SALTALINHA: Imprime(Pilha); break;

            default:
                if (Tamanho(*Pilha) == MAXTAM)
                    Imprime(Pilha);
                Empilha(x, Pilha);
                break;
        }
        x.Chave = getchar();
        if (x.Chave == '\n')
            x.Chave = ' ';
    }     
}

int main()
{
    TipoPilha Pilha; FPVazia(&Pilha);

    et(&Pilha);

    if (!Vazia(Pilha)) Imprime(&Pilha);
}