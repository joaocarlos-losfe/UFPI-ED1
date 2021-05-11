#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

typedef struct 
{
    int codigo;
    char titulo[20];
    char artista[20];
    int ano;

}Artista;

typedef struct aux
{
    Artista artista;
    struct aux* proximo_abaixo;

}Elemento, *Pont;

typedef struct
{
    Pont topo_pilha;
}Pilha;

int tamanhoPilha(Pilha* pilha_de_cds)
{
    int cont = 0;

    Pont end = pilha_de_cds->topo_pilha; 

    while (end!=NULL)
    {
        cont++;
        end = end->proximo_abaixo;
    }
    return cont;
}

void exibirPilhaCds(Pilha* pilha_de_cds)
{
    int count = 1;
    Pont end = pilha_de_cds->topo_pilha; 

    while (end!=NULL)
    {
        printf("\n\nCd: %d\n", count);
        printf("\nCodigo: %d", end->artista.codigo);
        printf("\nTitulo: %s", end->artista.titulo);
        printf("\nArtista: %s", end->artista.artista);
        printf("\nAno: %d\n", end->artista.ano);
        
        count++;
        end = end->proximo_abaixo;
    }
}

void empilharNovoCd(Pilha* pilha_de_cds, Artista cd)
{
    Pont novo_cd = (Pont) malloc(sizeof(Elemento));
    novo_cd->artista = cd;
    novo_cd->proximo_abaixo = pilha_de_cds->topo_pilha;
    pilha_de_cds->topo_pilha = novo_cd;
}

bool pilhaVazia(Pilha* pilha_de_cds)
{
    if(pilha_de_cds->topo_pilha == NULL)
        return true;
    else
        return false;
}

int main()
{    
    Pilha pilha_de_cds;
    pilha_de_cds.topo_pilha = NULL;

    int tamanho = tamanhoPilha(&pilha_de_cds);
    printf("%d", tamanho);

    Artista cd;
    cd.codigo = 111;
    strcpy(cd.artista, "Zedd");
    strcpy(cd.titulo, "Roses");
    cd.ano = 2015;

    empilharNovoCd(&pilha_de_cds, cd);
    empilharNovoCd(&pilha_de_cds, cd);
    empilharNovoCd(&pilha_de_cds, cd);
    empilharNovoCd(&pilha_de_cds, cd);

    exibirPilhaCds(&pilha_de_cds);

    return 0;
}