/****************

LAED1 - Intercalacao Listas

Alunos: Pedro Augusto de Portilho Ronzani, Ulisses Andrade Carvallho

Data: 13/05/2023

****************/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef int TipoChave;

typedef struct
{
    int Chave;
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

void Imprime(TipoLista Lista)
{
    TipoCelula *Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        printf("%d ", Aux->Item.Chave);
        Aux = Aux->Prox;
    }
    printf("\n");
}

/* ======================================================================================================================================== */

TipoLista *lista_de_lista;
TipoLista lista_resultado;
int numero_listas;

void leitura_arquivo()
{
    printf("Digite o nome do arquivo de entrada: ");
    char *path = (char *)malloc(200 * sizeof(char));
    scanf("%s", path);

    FILE *f = fopen(path, "r");

    fscanf(f, "%d ", &numero_listas);

    lista_de_lista = (TipoLista *)malloc(numero_listas * sizeof(TipoLista));

    for (int cont = 0; cont < numero_listas; cont++)
    {
        int num;

        TipoLista auxLista;
        FLVazia(&auxLista);
        lista_de_lista[cont] = auxLista;

        while (fscanf(f, "%d", &num) != -1)
        {

            TipoItem auxItem;
            auxItem.Chave = num;
            Insere(auxItem, &lista_de_lista[cont]);

            if (fgetc(f) == '\n')
            {   
                break;
            }
        }
    }
    fclose(f);
    free(path);
}

void concatena_listas()
{
    FLVazia(&lista_resultado);

    while (1)
    {
        int flag_matriz_vazia = 1;
        int i_menor = 0;
        int menor = __INT32_MAX__;

        for (int i = 0; i < numero_listas; i++)
        { // encontra o menor item

            if (!Vazia(lista_de_lista[i]))
            {
                flag_matriz_vazia = 0;

                int itemChaveAux = lista_de_lista[i].Primeiro->Prox->Item.Chave;
                if (itemChaveAux < menor)
                {
                    menor = itemChaveAux;
                    i_menor = i;
                }
            }
        }

        if (flag_matriz_vazia)
            break;

        TipoItem item_a_adicionar;
        Retira(lista_de_lista[i_menor].Primeiro, &lista_de_lista[i_menor], &item_a_adicionar);
        Insere(item_a_adicionar, &lista_resultado);
    }
}

void imprime_resultado(TipoLista Lista) {
    
    printf("\nLista final: ");
    TipoCelula *Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        if(Aux->Prox == NULL) {
            printf("%d", Aux->Item.Chave);
            break;
        }
        printf("%d,", Aux->Item.Chave);
        Aux = Aux->Prox;
    }
    printf("\n");
}

int main()
{
    leitura_arquivo();
    concatena_listas();
    imprime_resultado(lista_resultado);
}