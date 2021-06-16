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
    Dado inicio;
};

Dado novoDado();
Dado deletarDado(Dado dado);
void mostrarDado(Dado dado);

ListaE novLista();
ListaE formatarLista(ListaE lista);

void inserirNofinal(ListaE lista, Dado dado);
bool listaVazia(ListaE lista);
void inserirOrdenadoLista(ListaE lista, Dado dado);
void inserirPosicaoLista(ListaE lista, unsigned index, Dado dado);
Dado removerFinalLista(ListaE lista);
Dado removerInicioFila(ListaE lista);
void imprimirTodaLista(ListaE lista);
void inserirNoInicio(ListaE lista, Dado dado); //
Dado removerPosicaoLista(ListaE lista, unsigned index);
Dado buscarERemover(ListaE lista, int value);

int main()
{
    int i = 0;

    ListaE lista = novLista();

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

    inserirNoInicio(lista, dado3);

    printf("\n");
    imprimirTodaLista(lista);

    printf("\n\n----\n");

    Dado d = novoDado();

    d->valor = 5555;

    inserirNofinal(lista, d);

    imprimirTodaLista(lista);

    d = novoDado();
    d->valor = 333;

    printf("\n--\n");

    inserirNoInicio(lista, d);

    imprimirTodaLista(lista);

    removerFinalLista(lista);

    printf("----\n");

    imprimirTodaLista(lista);

    printf("\n----\n");

    removerInicioFila(lista);
    imprimirTodaLista(lista);

    return 0;
}

Dado novoDado() 
{
    Dado dado = malloc(sizeof(struct Dado));
    dado->valor = 0;
    dado->proximo = NULL;
    return dado;
}

Dado deletarDado(Dado dado) 
{
    free(dado);
    dado = NULL;
    return dado;
}

void mostrarDado(Dado dado) 
{
    printf("[ %d ]\n", dado->valor);
}

ListaE novLista() 
{
    ListaE lista = malloc(sizeof(struct ListaE));
    lista->n_elementos = 0;
    lista->inicio = NULL;
    return lista;
}

ListaE formatarLista(ListaE lista) 
{

    Dado tmp = lista->inicio;

    while (tmp != NULL)
    {
        lista->inicio = tmp->proximo;
        tmp = deletarDado(tmp);
        tmp = lista->inicio;
    }

    free(lista);
    lista = NULL;
    return lista;
}
void inserirNofinal(ListaE lista, Dado dado) 
{

    Dado atual = lista->inicio;
    Dado anterior = NULL;

    while (atual != NULL) 
    {
        anterior = atual;
        atual = atual->proximo;
    }
    if(lista->inicio == NULL) 
    {
        lista->inicio = dado;
    } 
    else if(anterior == NULL) 
    {
        atual->proximo = dado;
    } 
    else 
    {
        anterior->proximo = dado;
    }
    lista->n_elementos++;
}

void inserirOrdenadoLista(ListaE lista, Dado dado) 
{

    Dado atual = lista->inicio;
    Dado anterior = NULL;

    while ((atual!=NULL) && (atual->valor < dado->valor)) 
    {
        anterior = atual;
        atual = atual->proximo;
    }

    dado->proximo = atual;

    if (anterior == NULL) 
    {
        lista->inicio = dado;
    } 
    else 
    {
        anterior->proximo = dado;
    }

    lista->n_elementos++;
}

void inserirPosicaoLista(ListaE lista, unsigned index, Dado dado) 
{

    Dado atual = lista->inicio;
    Dado anterior = NULL;

    while ((atual!=NULL) && index > 0) 
    {
        anterior = atual;
        atual = atual->proximo;
        index--;
    }

    dado->proximo = atual;

    if (anterior == NULL) 
    {
        lista->inicio = dado;
    } 
    else 
    {
        anterior->proximo = dado;
    }

    lista->n_elementos++;
}

bool listaVazia(ListaE lista) 
{
    return lista->inicio == NULL;
}

Dado removerFinalLista(ListaE lista) {

    Dado atual = lista->inicio;

    if (atual != NULL) 
    {

        Dado anterior = NULL;

        while ((atual->proximo != NULL)) 
        {
            anterior = atual;
            atual = atual->proximo;
        }
        if(anterior == NULL) 
        {
            lista->inicio = NULL;
        } 
        else 
        {
            anterior->proximo = NULL;
        }

        lista->n_elementos--;
    }
    return atual;
}
Dado removerInicioFila(ListaE lista) 
{

    Dado atual = lista->inicio;

    if (atual != NULL) {
        lista->inicio = atual->proximo;
        lista->n_elementos--;
    }
    return atual;
}
void imprimirTodaLista(ListaE lista) 
{
    if (listaVazia(lista)) 
    {
        printf("lista vazia\n");
    } 
    else 
    {
        Dado dado = lista->inicio;

        while(dado != NULL) 
        {
            mostrarDado(dado);
            dado = dado->proximo;
        }
    }
}
void inserirNoInicio(ListaE lista, Dado dado) {

    dado->proximo = lista->inicio;
    lista->inicio = dado;
    lista->n_elementos++;
}
Dado removerPosicaoLista(ListaE lista, unsigned index) {

    Dado atual = lista->inicio;

    if (atual != NULL) 
    {
        Dado anterior = NULL;

        while ((atual->proximo != NULL) && (index > 0)) 
        {
            anterior = atual;
            atual = atual->proximo;
            index--;
        }
        if (anterior == NULL) 
        {
            lista->inicio = atual->proximo;
        } else if(atual != NULL) 
        {
            anterior->proximo = atual->proximo;
        }

        lista->n_elementos--;
    }

    return atual;
}

Dado buscarERemover(ListaE lista, int value) 
{

    Dado atual = lista->inicio;

    if (atual != NULL) {
        Dado anterior = NULL;

        while ((atual != NULL) && (atual->valor != value)) 
        {
            anterior = atual;
            atual = atual->proximo;
        }

        if (anterior == NULL) 
        {
            lista->inicio = atual->proximo;
            lista->n_elementos--;
        } 
        else if (atual != NULL) 
        {
            anterior->proximo = atual->proximo;
            lista->n_elementos--;
        }
    }
    return atual;
}
