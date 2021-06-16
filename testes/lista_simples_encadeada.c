#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Dado* Dado;
typedef struct ListaSE* ListaSE;

struct Dado
{
    int valor;
    Dado proximo;
};

struct ListaSE 
{
    unsigned int n_elementos;
    Dado topo;
};

Dado novoDado();
Dado deletarDado(Dado data);
void mostrarDado(Dado data);

ListaSE novLista();
ListaSE formatarLista(ListaSE list);

void acresentarDadoLista(ListaSE list, Dado data);
bool listaVazia(ListaSE list);
void inserirOrdenadoLista(ListaSE list, Dado data);
void inserirPosicaoLista(ListaSE list, unsigned index, Dado data);
Dado removerFinalLista(ListaSE list);
Dado removerInicioFila(ListaSE list);
void imprimirTodaLista(ListaSE list);
void inseriFinalLista(ListaSE list, Dado data); //
Dado removerPosicaoLista(ListaSE list, unsigned index);
Dado buscarRemoverLista(ListaSE list, int value);

int main()
{
    int i = 0;

    ListaSE lista = novLista();

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

ListaSE novLista() 
{
    ListaSE list = malloc(sizeof(struct ListaSE));
    list->n_elementos = 0;
    list->topo = NULL;
    return list;
}
ListaSE formatarLista(ListaSE list) 
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
void acresentarDadoLista(ListaSE list, Dado data) 
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
void inserirOrdenadoLista(ListaSE list, Dado data) {

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
void inserirPosicaoLista(ListaSE list, unsigned index, Dado data) 
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

bool listaVazia(ListaSE list) 
{
    return list->topo == NULL;
}
Dado removerFinalLista(ListaSE list) {

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
Dado removerInicioFila(ListaSE list) 
{

    Dado current = list->topo;

    if (current != NULL) {
        list->topo = current->proximo;
        list->n_elementos--;
    }
    return current;
}
void imprimirTodaLista(ListaSE list) 
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
void inseriFinalLista(ListaSE list, Dado data) {

    data->proximo = list->topo;
    list->topo = data;
    list->n_elementos++;
}
Dado removerPosicaoLista(ListaSE list, unsigned index) {

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

Dado list_remove_value(ListaSE list, int value) 
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
