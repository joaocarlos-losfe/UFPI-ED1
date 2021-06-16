#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Dado* Dado;
typedef struct Lista* Lista;

struct Dado
{
    int value;
    Dado proximo;
    Dado anterior;
};

Dado data_create();
Dado data_delete(Dado dado);
void data_print(Dado dado);

struct Lista 
{
    unsigned size;
    Dado inicio;
    Dado fim;
};


Lista criarLista();
Lista formatarLista(Lista lista);

void inserirnofinal(Lista lista, Dado dado);
bool listaVazia(Lista lista);
void inserirOrdenado(Lista lista, Dado dado);
void inseriPosicaoLista(Lista lista, unsigned index, Dado dado);
Dado removerFinal(Lista lista);
Dado removerInicio(Lista lista);
void mostrarLista(Lista lista);
void mostrarListaAoContrario(Lista lista);
void inserirNoInicio(Lista lista, Dado dado);
Dado removerPosicao(Lista lista, unsigned index);
Dado buscarERemover(Lista lista, int value);

int main()
{
    return 0;
}

Dado data_create() 
{
    Dado dado = malloc(sizeof(struct Dado));
    dado->value = 0;
    dado->proximo = NULL;
    dado->anterior = NULL;
    return dado;
}

Dado data_delete(Dado dado) 
{
    free(dado);
    dado = NULL;
    return dado;
}

void data_print(Dado dado) 
{
    printf("[ %d ]\n", dado->value);
}

Lista criarLista() 
{
    Lista lista = malloc(sizeof(struct Lista));
    lista->size = 0;
    lista->inicio = NULL;
    lista->fim = NULL;
    return lista;
}

Lista formatarLista(Lista lista) 
{

    Dado tmp = lista->inicio;

    while (tmp != NULL) 
    {
        lista->inicio = tmp->proximo;
        tmp = data_delete(tmp);
        tmp = lista->inicio;
    }

    free(lista);
    lista = NULL;
    return lista;
}

void inserirnofinal(Lista lista, Dado dado) 
{
    Dado ultimo = lista->fim;

    if(ultimo == NULL) 
    {
        lista->inicio = lista->fim = dado;
    } 
    else 
    {
        dado->anterior = ultimo;
        ultimo->proximo = lista->fim = dado;
    }

    lista->size++;
}
static void inserirDentroDe(Lista lista, Dado anterior, Dado atual, Dado dado) 
{
    dado->proximo = atual;
    dado->anterior = anterior;

    if (atual != NULL) 
    {
        atual->anterior = dado;
    } 
    else 
    {
        lista->fim = dado;
    }
    if(anterior == NULL) 
    {
        lista->inicio = dado;
    } 
    else 
    {
        anterior->proximo = dado;
    }
    lista->size++;
}

void inserirOrdenado(Lista lista, Dado dado) 
{

    Dado anterior = NULL;
    Dado atual = lista->inicio;

    while ((atual != NULL)&& (atual->value < dado->value)) 
    {
        anterior = atual;
        atual = atual->proximo;
    }

    inserirDentroDe(lista, anterior, atual, dado);
}

void inseriPosicaoLista(Lista lista, unsigned index, Dado dado) 
{

    Dado anterior = NULL;
    Dado atual = lista->inicio;

    while ((atual != NULL) && ( index > 0)) 
    {
        anterior = atual;
        atual = atual->proximo;
        index--;
    }

    inserirDentroDe(lista, anterior, atual, dado);
}

bool listaVazia(Lista lista) 
{
    return lista->inicio == NULL;
}

Dado removerFinal(Lista lista) 
{
    Dado atual = lista->fim;

    if (atual != NULL) 
    {
        Dado anterior = atual->anterior;

        if (anterior == NULL) 
        {
            lista->inicio = lista->fim = NULL;
        } 
        else 
        {
            anterior->proximo = NULL;
            lista->fim = anterior;
        }

        atual->anterior = atual->proximo = NULL;
        lista->size--;
    }
    return atual;
}

Dado removerInicio(Lista lista) 
{

    Dado atual = lista->inicio;

    if (atual != NULL) 
    {
        if(atual->proximo != NULL) 
        {
            atual->proximo->anterior = NULL;
        } 
        else 
        {
            lista->fim = NULL;
        }

        lista->inicio = atual->proximo;
        atual->anterior = atual->proximo = NULL;
        lista->size--;
    }
    return atual;
}
void mostrarLista(Lista lista) 
{
    if (listaVazia(lista)) 
    {
        printf("empty lista\n");
    } 
    else 
    {
        Dado dado = lista->inicio;

        while(dado != NULL) 
        {
            data_print(dado);
            dado = dado->proximo;
        }
    }
}
void mostrarListaAoContrario(Lista lista) 
{
    if (listaVazia(lista)) 
    {
        printf("empty lista\n");
    } 
    else 
    {
        Dado dado = lista->fim;

        while(dado != NULL) 
        {
            data_print(dado);
            dado = dado->anterior;
        }
    }
}
void inserirNoInicio(Lista lista, Dado dado) 
{

    dado->proximo = lista->inicio;
    if(lista->inicio != NULL) 
    {
        lista->inicio->anterior = dado;
    } 
    else 
    {
        lista->fim = dado;
    }

    lista->inicio = dado;
    lista->size++;
}

static Dado removerDe(Lista lista, Dado anterior, Dado atual) 
{
    if (anterior == NULL) 
    {
        lista->inicio = atual->proximo;
    } 
    else 
    {
        anterior->proximo = atual->proximo;
    }
    if (atual->proximo != NULL) 
    {
        atual->proximo->anterior = anterior;
    }
    else 
    {
        lista->fim = anterior;
    }

    atual->anterior = atual->proximo = NULL;
    lista->size--;
    return atual;
}

Dado removerPosicao(Lista lista, unsigned index) 
{

    Dado atual = lista->inicio;

    Dado anterior = NULL;

    while ((atual->proximo != NULL) && ( index > 0)) 
    {
        anterior = atual;
        atual = atual->proximo;
        index--;
    }

    return (atual != NULL) ? removerDe(lista, anterior, atual) : NULL;
}

Dado buscarERemover(Lista lista, int value) 
{

    Dado atual = lista->inicio;
    Dado anterior = NULL;

    while ((atual != NULL) && (atual->value != value)) 
    {
        anterior = atual;
        atual = atual->proximo;
    }

    return (atual != NULL) ? removerDe(lista, anterior, atual) : NULL;
}