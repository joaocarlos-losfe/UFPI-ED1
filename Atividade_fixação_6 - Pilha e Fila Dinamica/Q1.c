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
    char estilo_musical[10];

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

bool pilhaVazia(Pilha* pilha_de_cds)
{
    if(pilha_de_cds->topo_pilha == NULL)
        return true;
    else
        return false;
}

void exibirPilhaCds(Pilha* pilha_de_cds)
{
    int count = 1;
    Pont end = pilha_de_cds->topo_pilha; 

    while (end!=NULL)
    {
        printf("\n\nCd: %d", count);
        printf("\nCodigo: %d", end->artista.codigo);
        printf("\nTitulo: %s", end->artista.titulo);
        printf("\nArtista: %s", end->artista.artista);
        printf("\nAno: %d", end->artista.ano);
        printf("\nEstilo musical: %s\n", end->artista.estilo_musical);
        
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


void removerCd(Pilha* pilha_de_cds)
{
    if(pilhaVazia(pilha_de_cds))
        return;
    else
    {
        Pont apagar = pilha_de_cds->topo_pilha;
        pilha_de_cds->topo_pilha = pilha_de_cds->topo_pilha->proximo_abaixo;
        free(apagar);
    }
    
}

void separarDesempilharEmpilhar(Pilha *pilha_de_cds, Pilha *segunda_pilha, char estilo[10])
{
    Pilha auxliar;
    auxliar.topo_pilha = NULL;

    while (pilha_de_cds->topo_pilha !=NULL)
    {

        if(strcmp(pilha_de_cds->topo_pilha->artista.estilo_musical, estilo) == 0)
        {
            empilharNovoCd(segunda_pilha, pilha_de_cds->topo_pilha->artista);
            printf("\neh pop\n");
        }
        else
        {
            empilharNovoCd(&auxliar, pilha_de_cds->topo_pilha->artista);
            printf("\nnao eh pop\n");
        }

        Pont apagar = pilha_de_cds->topo_pilha;
        
        pilha_de_cds->topo_pilha = pilha_de_cds->topo_pilha->proximo_abaixo;

        free(apagar);

    }

    while (auxliar.topo_pilha != NULL) // empilhar de volta os removidos na original exeto o disptribuido pra segunda pilha
    {
        empilharNovoCd(pilha_de_cds, auxliar.topo_pilha->artista);

        auxliar.topo_pilha = auxliar.topo_pilha->proximo_abaixo;
    }

}

void distibuirCds(Pilha *pilha_de_cds, int estilo, Pilha *pop, Pilha *rock, Pilha *sertanejo, Pilha *forro, Pilha *axe)
{
    switch (estilo)
    {
    case 1: //pop
        break;
    case 2: // rock
        break;
    case 3: // sertanejo
        break;
    case 4: // forro
        break;
    case 5: // axe
        break;
    default:
        break;
    }
}

int main()
{    
    Pilha pilha_de_cds;
    pilha_de_cds.topo_pilha = NULL;

    Pilha pop, rock, sertanejo, forro, axe;

    pop.topo_pilha = rock.topo_pilha = sertanejo.topo_pilha = forro.topo_pilha = axe.topo_pilha = NULL; 

    int tamanho = tamanhoPilha(&pilha_de_cds);
    printf("%d", tamanho);

    Artista cd;
    cd.codigo = 111;
    strcpy(cd.artista, "Zedd");
    strcpy(cd.titulo, "Roses");
    cd.ano = 2015;
    strcpy(cd.estilo_musical, "Pop");


    empilharNovoCd(&pilha_de_cds, cd);

    cd.codigo = 222;
    strcpy(cd.artista, "Avicci");
    strcpy(cd.titulo, "Life");
    cd.ano = 2014;
    strcpy(cd.estilo_musical, "Rock");
    empilharNovoCd(&pilha_de_cds, cd);

    cd.codigo = 333;
    strcpy(cd.artista, "Martin garrix");
    strcpy(cd.titulo, "friend");
    cd.ano = 2017;
    strcpy(cd.estilo_musical, "sertanejo");
    empilharNovoCd(&pilha_de_cds, cd);
    
    //exibirPilhaCds(&pilha_de_cds);

    /*
    printf("\nremover cd topo...\n");
    removerCd(&pilha_de_cds);
    */

    //exibirPilhaCds(&pilha_de_cds);

    printf("\nseparando...\n");
    char estilo[10];
    strcpy(estilo, "Pop");
    separarDesempilharEmpilhar(&pilha_de_cds, &pop, estilo);

    exibirPilhaCds(&pop);
    printf("\n\n");
    exibirPilhaCds(&pilha_de_cds);

    return 0;
}