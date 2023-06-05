#include <stdio.h>
#include <stdlib.h>

int* v;
int numero_itens;

int main() {
    printf("Digite o nome do arquivo de entrada: ");
    char *path = (char *)malloc(200 * sizeof(char));
    scanf("%s", path);

    FILE *f = fopen(path, "r");

    numero_itens; fscanf(f, "%d",&numero_itens);

    v = (int*) malloc(numero_itens * sizeof(int));

    for(int i=0; i < numero_itens; i++)
    {
        fscanf(f, "%d", &v[i]);
    }
    
    for(int i=0; i<numero_itens; i++)
        printf("%d ",v[i]);
    printf("\n");
}