/* Executar o programa lendo o arquivo: a.out <vestibular.dat  */

#include <stdio.h>
#include <stdlib.h>

#define NOPCOES 3
#define NCURSOS 7
#define FALSE 0
#define TRUE 1

typedef short TipoChave;

typedef struct TipoItem
{
  TipoChave Chave;
  int NotaFinal;
  int Opcao[NOPCOES];
} TipoItem;

typedef struct TipoCelula
{
  TipoItem Item;
  struct TipoCelula *Prox;
} TipoCelula;

typedef struct TipoLista
{
  TipoCelula *Primeiro, *Ultimo;
} TipoLista;

TipoItem Registro;
TipoLista Classificacao[11];
TipoLista Aprovados[NCURSOS];
TipoLista Reprovados;
long Vagas[NCURSOS];
short Passou;
long i, Nota;

void FLVazia(TipoLista *Lista)
{
  Lista->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

short Vazia(TipoLista Lista)
{
  return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{
  Lista->Ultimo->Prox = (TipoCelula *)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = x;
  Lista->Ultimo->Prox = NULL;
}

void Retira(TipoCelula *p, TipoLista *Lista, TipoItem *Item)
{ /*---Obs.: o item a ser retirado e o seguinte ao apontado por  p --- */
  TipoCelula *q;

  if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
  {
    printf("Erro : Lista vazia ou posicao nao existe\n");
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
    printf("%d\n", Aux->Item.Chave);
    Aux = Aux->Prox;
  }
}

void LeRegistro(TipoItem *Registro)
{ /*---os valores lidos devem estar separados por brancos---*/
  long i;
  scanf("%hd%d", &Registro->Chave, &Registro->NotaFinal);
  for (i = 0; i < NOPCOES; i++)
    scanf("%d", &Registro->Opcao[i]);
}

int main(int argc, char *argv[])
{ /*---Programa principal---*/
  for (i = 1; i <= NCURSOS; i++)
    scanf("%ld", &Vagas[i - 1]);
  scanf("%*[^\n]");
  getchar();
  for (i = 0; i <= 10; i++)
    FLVazia(&Classificacao[i]);
  for (i = 1; i <= NCURSOS; i++)
    FLVazia(&Aprovados[i - 1]);
  FLVazia(&Reprovados);
  LeRegistro(&Registro);
  while (Registro.Chave != 0)
  {
    Insere(Registro, &Classificacao[Registro.NotaFinal]);
    LeRegistro(&Registro);
  }
  for (Nota = 10; Nota >= 0; Nota--)
  {
    while (!Vazia(Classificacao[Nota]))
    {
      Retira(Classificacao[Nota].Primeiro,
             &Classificacao[Nota], &Registro);
      i = 1;
      Passou = FALSE;
      while (i <= NOPCOES && !Passou)
      {
        if (Vagas[Registro.Opcao[i - 1] - 1] > 0)
        {
          Insere(Registro, &Aprovados[Registro.Opcao[i - 1] - 1]);
          Vagas[Registro.Opcao[i - 1] - 1]--;
          Passou = TRUE;
        }
        i++;
      }
      if (!Passou)
        Insere(Registro, &Reprovados);
    }
  }
  for (i = 1; i <= NCURSOS; i++)
  {
    printf("Relacao dos aprovados no Curso%ld\n", i);
    Imprime(Aprovados[i - 1]);
  }
  printf("Relacao dos reprovados\n");
  Imprime(Reprovados);
  return 0;
}
