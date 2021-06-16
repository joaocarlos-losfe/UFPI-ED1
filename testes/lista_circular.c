#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Dado* Dado;
typedef struct ListaC* Lista;

struct Dado
{
    int value;
    Dado proximo;
};

Dado novoDado();
Dado apagarDado(Dado dado);
void mostrarDado(Dado dado);

struct ListaC 
{
    unsigned int n_elementos;
    Dado topo;
    Dado ultimo;
};


Lista criarLista();
Lista formatarLista(Lista lista);
void inserirNofinalLista(Lista lista, Dado dado);
bool listaVazia(Lista lista);
void inserirOrdenadoLista(Lista lista, Dado dado);
void inserirnaPosicaoLista(Lista lista, unsigned index, Dado dado);
Dado removerDoinicio(Lista lista);
Dado removerDoFim(Lista lista);
void mostrarLista(Lista lista);
void inserirNoinicio(Lista lista, Dado dado);
Dado removerPorPosicaoLista(Lista lista, unsigned index);
Dado buscarERemover(Lista lista, int value);

int main()
{
    return 0;
}

Dado novoDado() 
{
    Dado dado = malloc(sizeof(struct Dado));
    dado->value = 0;
    dado->proximo = NULL;
    return dado;
}

Dado apagarDado(Dado dado) 
{
    free(dado);
    dado = NULL;
    return dado;
}

void mostrarDado(Dado dado) 
{
    printf("[ %d ]\n", dado->value);
}

Lista criarLista() 
{
    Lista lista = malloc(sizeof(struct ListaC));
    lista->n_elementos = 0;
    lista->topo = NULL;
    lista->ultimo = NULL;
    return lista;
}

Lista formatarLista(Lista lista) 
{
    Dado dado = lista->topo;

    if(dado != NULL) {
        Dado tmp = NULL;

        do {
            tmp = dado;
            dado = dado->proximo;
            tmp = apagarDado(tmp);
        } while(dado != lista->topo );

        dado = lista->topo = lista->ultimo = NULL;
    }
    free(lista);
    lista = NULL;
    return lista;
}

static void inserirEntre(Lista lista, Dado anterior, Dado atual, Dado dado) 
{
    dado->proximo = atual;

    if (anterior == NULL) 
    {
        lista->topo = dado = lista->ultimo->proximo = dado;
    } 
    else 
    {
        anterior->proximo = dado;

        if(atual == lista->topo) 
        {
            lista->ultimo = dado;
        }
    }
}

static Dado removerDe(Lista lista, Dado anterior, Dado atual) 
{
    if (anterior == NULL) 
    {
        return removerDoFim(lista);
    }

    anterior->proximo = atual->proximo;

    if(atual == lista->ultimo) 
    {
        lista->ultimo = anterior;
    }

    lista->n_elementos--;
    atual->proximo = NULL;
    return atual;
}

void inserirNofinalLista(Lista lista, Dado dado) 
{

    Dado atual = lista->topo;

    if(atual == NULL) 
    {
        lista->topo = lista->ultimo = dado->proximo = dado;
    } 
    else 
    {
        dado->proximo = lista->topo;
        lista->ultimo = lista->ultimo->proximo = dado;
    }

    lista->n_elementos++;
}

void inserirOrdenadoLista(Lista lista, Dado dado) 
{

    Dado atual = lista->topo;
    Dado anterior = NULL;

    if(atual == NULL) {
        lista->topo = lista->ultimo = dado->proximo = dado;
    } else {
        do {
            if (atual->value > dado->value) {
                break;
            }
            anterior = atual;
            atual = atual->proximo;
        } while (atual != lista->topo);

        inserirEntre(lista, anterior, atual, dado);
    }
    lista->n_elementos++;
}
void inserirnaPosicaoLista(Lista lista, unsigned index, Dado dado) {

    Dado atual = lista->topo;
    Dado anterior = NULL;
    if(atual == NULL) {
        lista->topo = lista->ultimo = dado->proximo = dado;
    } else {
        do {
            if (index < 1) {
                break;
            }
            index--;
            anterior = atual;
            atual = atual->proximo;
        } while (atual != lista->topo);

        inserirEntre(lista, anterior, atual, dado);
    }
    lista->n_elementos++;
}
bool listaVazia(Lista lista) {
    return lista->topo == NULL;
}

Dado removerDoinicio(Lista lista) {
    Dado atual = lista->topo;
    if(atual != NULL) {
        Dado anterior = NULL;
        while (atual != lista->ultimo) {
            anterior = atual;
            atual = atual->proximo;
        }
        atual = removerDe(lista, anterior, atual);
    }
    return atual;
}
Dado removerDoFim(Lista lista) {
    Dado atual = lista->topo;
    if(atual != NULL) {
        if(atual == lista->ultimo) {
            lista->topo = lista->ultimo = NULL;
        } else {
            lista->ultimo->proximo = lista->topo = atual->proximo;
        }
        atual->proximo = NULL;
        lista->n_elementos--;
    }
    return atual;
}
void mostrarLista(Lista lista) {
    if (listaVazia(lista)) {
        printf("empty lista\n");
    } else {
        Dado dado = lista->topo;
        do {
            mostrarDado(dado);
            dado = dado->proximo;
        } while(dado != lista->topo );
    }
}
void inserirNoinicio(Lista lista, Dado dado) {

    dado->proximo = lista->topo;
    lista->topo = dado;
    if(lista->ultimo == NULL) {
        lista->ultimo = dado;
    } else {
        lista->ultimo->proximo = dado;
    }
    lista->n_elementos++;
}
Dado removerPorPosicaoLista(Lista lista, unsigned index) {

    Dado atual = lista->topo;

    if (atual != NULL) {
        Dado anterior = NULL;
        index = (index < lista->n_elementos) ? index : (lista->n_elementos - 1);
        do {
            if ( index < 1 ) {
                break;
            }
            index--;
            anterior = atual;
            atual = atual->proximo;
        } while (atual != lista->topo);

        atual = removerDe(lista, anterior, atual);
    }
    return atual;
}

Dado buscarERemover(Lista lista, int value) {

    Dado atual = lista->topo;

    if (atual != NULL) {
        Dado anterior = NULL;

        do {
            if (atual->value == value) {
                break;
            }
            anterior = atual;
            atual = atual->proximo;
        } while (atual != lista->topo);

        atual = (atual->value == value) ? removerDe(lista, anterior, atual) : NULL;
    }
    return atual;
}