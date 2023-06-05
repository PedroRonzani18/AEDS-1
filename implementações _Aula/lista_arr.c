#include <stdio.h>
#include <malloc.h>

#define MAXSIZE 1000

typedef int Key;

typedef struct
{
    Key key;
} Node;

typedef struct
{
    Node values[MAXSIZE];
    int front_index, back_index;
} ListaArr;

void clear(ListaArr* list) {

    list->front_index = 0;
    list->back_index = 1;
}

ListaArr create_list()
{
    ListaArr retorno;
    clear(&retorno);
    return retorno;
}

Node create_node(Key value) {

    Node retorno;
    retorno.key = value;
    return retorno;
}

int empty(ListaArr list) {

    return (list.front_index == list.back_index-1);
}

void push_back(Node x, ListaArr* list) {

    if(list->back_index > MAXSIZE) {
        printf("List is Full.\n");
        return;
    }

    list->values[list->back_index - 1] = x;
    list->back_index ++;
}

void remove_index(int index, ListaArr* list, Node* item/* = (Node*) malloc(sizeof(Node))*/) {

    //printf("Index: %d | Back: %d\n",index,list->back_index);

    if(empty(*list) || index > list->back_index-2)
    {
        printf("Incorrect Position.\n");
        return;
    }

    *item = list->values[index];
    list->back_index --;

    for(int i=index+1; i<list->back_index; i++) {
        list->values[i-1] = list->values[i];
    }
}

void print_list(ListaArr list) {

    for(int i=list.front_index; i<list.back_index-1; i++) {
        printf("%d ",list.values[i].key);
    }
    printf("\n");
}

int main() {

    ListaArr list = create_list();

    for(int i=1; i<=10; i++) {
        Node aux; aux.key = i;
        push_back(aux, &list);
    }

    print_list(list);

    Node retorno;

    remove_index(10, &list, &retorno);

    print_list(list);
}