#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Dado* Dado;
typedef struct ListDE* ListaDE;

struct Dado
{
    int valor; // ou outra struct separadas de dados. cabe gerenciar nas funções basicas da lista DE
    Dado proximo;
    Dado anterior;
};

struct ListDE 
{
    unsigned total_elementos;

    Dado topo; // cabeça
    Dado inicio; // pés
};

Dado novoDado();
Dado deletarDado(Dado data);
void mostrarDado(Dado data);

ListaDE novaLista();
ListaDE formatarLista(ListaDE list);

void acresentarDadoLista(ListaDE list, Dado data);
bool listaVazia(ListaDE list);
void inserirOrdenadoLista(ListaDE list, Dado data);
void inserirPosicaoLista(ListaDE list, unsigned index, Dado data);
Dado removerTopoLista(ListaDE list);
Dado removerInicioLista(ListaDE list);
void mostrarLista(ListaDE list);
void mostrarAoContrarioLista(ListaDE list);
void inserirDadoLista(ListaDE list, Dado data);
Dado removerPosicaoLista(ListaDE list, unsigned index);
Dado buscarERemoverLista(ListaDE list, int value);

int main()
{
    return 0;
}

Dado novoDado() 
{
    Dado data = malloc(sizeof(struct Dado));
    data->valor = 0;
    data->proximo = NULL;
    data->anterior = NULL;
    return data;
}

Dado deletarDado(Dado data)
{
    free(data);
    data = NULL;
    return data;
}
void mostrarDado(Dado data) 
{
    printf("[ %d ]\n", data->valor);
}

ListaDE novaLista() 
{
    ListaDE list = malloc(sizeof(struct ListDE));
    list->total_elementos = 0;
    list->topo = NULL;
    list->inicio = NULL;
    return list;
}

ListaDE formatarLista(ListaDE list) 
{
    Dado tmp = list->topo;

    while (tmp != NULL) 
    {
        list->topo = tmp->proximo;
        tmp = deletarDado(tmp);
        tmp = list->topo;
    }

    free(list);
    list = NULL;
    return list;
}
void acresentarDadoLista(ListaDE list, Dado data) 
{
    Dado last = list->inicio;

    if(last == NULL) 
    {
        list->topo = list->inicio = data;
    } 
    else 
    {
        data->anterior = last;
        last->proximo = list->inicio = data;
    }

    list->total_elementos++;
}


void inserirOrdenadoLista(ListaDE list, Dado data) 
{

    Dado previous = NULL;
    Dado current = list->topo;

    while ((current != NULL)&& (current->valor < data->valor)) 
    {
        previous = current;
        current = current->proximo;
    }

    list_insert_into(list, previous, current, data);
}

void inserirPosicaoLista(ListaDE list, unsigned index, Dado data) 
{

    Dado previous = NULL;
    Dado current = list->topo;

    while ((current != NULL) && ( index > 0)) 
    {
        previous = current;
        current = current->proximo;
        index--;
    }

    list_insert_into(list, previous, current, data);
}

bool listaVazia(ListaDE list) 
{
    return list->topo == NULL;
}

Dado removerTopoLista(ListaDE list) {

    Dado current = list->inicio;

    if (current != NULL) 
    {

        Dado previous = current->anterior;

        if (previous == NULL) 
        {
            list->topo = list->inicio = NULL;
        } else 
        {
            previous->proximo = NULL;
            list->inicio = previous;
        }

        current->anterior = current->proximo = NULL;
        list->total_elementos--;
    }
    return current;
}
Dado removerInicioLista(ListaDE list) 
{

    Dado current = list->topo;

    if (current != NULL) 
    {
        if(current->proximo != NULL) 
        {
            current->proximo->anterior = NULL;
        } 
        else 
        {
            list->inicio = NULL;
        }

        list->topo = current->proximo;
        current->anterior = current->proximo = NULL;
        list->total_elementos--;
    }

    return current;
}
void mostrarLista(ListaDE list) 
{
    if (listaVazia(list)) 
    {
        printf("empty list\n");
    } 
    else 
    {
        Dado data = list->topo;
        while(data != NULL) 
        {
            mostrarDado(data);
            data = data->proximo;
        }
    }
}
void mostrarAoContrarioLista(ListaDE list) 
{
    if (listaVazia(list)) 
    {
        printf("empty list\n");
    } 
    else 
    {
        Dado data = list->inicio;

        while(data != NULL) 
        {
            mostrarDado(data);
            data = data->anterior;
        }
    }
}

void inserirDadoLista(ListaDE list, Dado data) 
{

    data->proximo = list->topo;
    if(list->topo != NULL) 
    {
        list->topo->anterior = data;
    } 
    else 
    {
        list->inicio = data;
    }

    list->topo = data;
    list->total_elementos++;
}


Dado removerPosicaoLista(ListaDE list, unsigned index) 
{

    Dado current = list->topo;

    Dado previous = NULL;

    while ((current->proximo != NULL) && ( index > 0)) 
    {
        previous = current;
        current = current->proximo;
        index--;
    }

    return (current != NULL) ? list_remove_from(list, previous, current) : NULL;
}

Dado buscarERemoverLista(ListaDE list, int value) 
{

    Dado current = list->topo;
    Dado previous = NULL;

    while ((current != NULL) && (current->valor != value))
    {
        previous = current;
        current = current->proximo;
    }
    
    return (current != NULL) ? list_remove_from(list, previous, current) : NULL;
}