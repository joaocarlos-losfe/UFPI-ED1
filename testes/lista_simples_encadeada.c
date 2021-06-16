#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Dado* Dado;
typedef struct ListaE* ListaE;

struct Dado
{
    int valor;
    Dado proximo;
};

struct ListaE 
{
    unsigned int n_elementos;
    Dado topo;
};

Dado novoDado();
Dado deletarDado(Dado data);
void mostrarDado(Dado data);

ListaE novaLista();
ListaE formatarLista(ListaE list);

void acresentarDadoLista(ListaE list, Dado data);
bool listaVazia(ListaE list);
void inserirOrdenadoLista(ListaE list, Dado data);
void inserirPosicaoLista(ListaE list, unsigned index, Dado data);
Dado removerFinalLista(ListaE list);
Dado removerInicioFila(ListaE list);
void imprimirTodaLista(ListaE list);
void inseriFinalLista(ListaE list, Dado data); //
Dado removerPosicaoLista(ListaE list, unsigned index);
Dado buscarRemoverLista(ListaE list, int value);

int main()
{
    int i = 0;

    ListaE lista = novaLista();

    for(i=0; i<10; i++)
    {
        Dado dado = novoDado();
        dado->valor = rand() % 100;
       
        inserirOrdenadoLista(lista, dado);
        printf("%d ", dado->valor);
    }

    printf("\n");

    imprimirTodaLista(lista);

    printf("\n");

    removerFinalLista(lista);

    imprimirTodaLista(lista);

    removerPosicaoLista(lista, 3);

    printf("\n");
    imprimirTodaLista(lista);

    Dado dado = novoDado();
    dado->valor = 500;

    inserirPosicaoLista(lista, 0, dado);

    Dado dado2 = novoDado();
    dado2->valor = 3233;

    Dado dado3 = novoDado();
    dado3->valor = 4232;


    inserirPosicaoLista(lista, 2, dado);

    printf("\n");
    imprimirTodaLista(lista);

    inseriFinalLista(lista, dado3);

    printf("\n");
    imprimirTodaLista(lista);

    return 0;
}

Dado novoDado() 
{
    Dado data = malloc(sizeof(struct Dado));
    data->valor = 0;
    data->proximo = NULL;
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

ListaE novaLista() 
{
    ListaE list = malloc(sizeof(struct ListaE));
    list->n_elementos = 0;
    list->topo = NULL;
    return list;
}
ListaE formatarLista(ListaE list) 
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
void acresentarDadoLista(ListaE list, Dado data) 
{

    Dado current = list->topo;
    Dado previous = NULL;

    while (current != NULL) 
    {
        previous = current;
        current = current->proximo;
    }
    if(list->topo == NULL) 
    {
        list->topo = data;
    } 
    else if(previous == NULL) 
    {
        current->proximo = data;
    } 
    else 
    {
        previous->proximo = data;
    }
    list->n_elementos++;
}
void inserirOrdenadoLista(ListaE list, Dado data) {

    Dado current = list->topo;
    Dado previous = NULL;

    while ((current!=NULL) && (current->valor < data->valor)) 
    {
        previous = current;
        current = current->proximo;
    }

    data->proximo = current;

    if (previous == NULL) 
    {
        list->topo = data;
    } 
    else 
    {
        previous->proximo = data;
    }

    list->n_elementos++;
}
void inserirPosicaoLista(ListaE list, unsigned index, Dado data) 
{

    Dado current = list->topo;
    Dado previous = NULL;

    while ((current!=NULL) && index > 0) 
    {
        previous = current;
        current = current->proximo;
        index--;
    }

    data->proximo = current;

    if (previous == NULL) 
    {
        list->topo = data;
    } 
    else 
    {
        previous->proximo = data;
    }

    list->n_elementos++;
}

bool listaVazia(ListaE list) 
{
    return list->topo == NULL;
}
Dado removerFinalLista(ListaE list) {

    Dado current = list->topo;

    if (current != NULL) 
    {

        Dado previous = NULL;

        while ((current->proximo != NULL)) 
        {
            previous = current;
            current = current->proximo;
        }
        if(previous == NULL) 
        {
            list->topo = NULL;
        } 
        else 
        {
            previous->proximo = NULL;
        }

        list->n_elementos--;
    }
    return current;
}
Dado removerInicioFila(ListaE list) 
{

    Dado current = list->topo;

    if (current != NULL) {
        list->topo = current->proximo;
        list->n_elementos--;
    }
    return current;
}
void imprimirTodaLista(ListaE list) 
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
void inseriFinalLista(ListaE list, Dado data) {

    data->proximo = list->topo;
    list->topo = data;
    list->n_elementos++;
}
Dado removerPosicaoLista(ListaE list, unsigned index) {

    Dado current = list->topo;

    if (current != NULL) 
    {
        Dado previous = NULL;

        while ((current->proximo != NULL) && (index > 0)) 
        {
            previous = current;
            current = current->proximo;
            index--;
        }
        if (previous == NULL) 
        {
            list->topo = current->proximo;
        } else if(current != NULL) 
        {
            previous->proximo = current->proximo;
        }

        list->n_elementos--;
    }

    return current;
}

Dado list_remove_value(ListaE list, int value) 
{

    Dado current = list->topo;

    if (current != NULL) {
        Dado previous = NULL;

        while ((current != NULL) && (current->valor != value)) 
        {
            previous = current;
            current = current->proximo;
        }

        if (previous == NULL) 
        {
            list->topo = current->proximo;
            list->n_elementos--;
        } 
        else if (current != NULL) 
        {
            previous->proximo = current->proximo;
            list->n_elementos--;
        }
    }
    return current;
}
