/*
	Exercicio resolvido por: 
        João Carlos de Sousa Fé.
	    Vitor José Ferreira dos Santos de Santana.
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define MSGERRO "\nERRO! - Entrada inválida!\nSelecione a opção correta!\n"

void menu()
{
  printf("\n0 - Sair");
  printf("\n1 - Empilhar cd");
  printf("\n2 - Ver todos os cd da pilha principal");
  printf("\n3 - criar pilhas para os seus CDs");
  printf("\n4 - Imprima todos os elementos de uma da pilha escolhida");
  printf("\n5 - montar um outra pilha baseada no ano de lancamento\n: ");
}

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

    if(pilhaVazia(pilha_de_cds))
    {
        printf("Pilha vazia...");
        return;
    }

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

void separarPorEstilo(Pilha *pilha_de_cds, Pilha *segunda_pilha, char estilo[10])
{
    Pilha auxliar;
    auxliar.topo_pilha = NULL;

    while (pilha_de_cds->topo_pilha !=NULL)
    {
        if(strcmp(pilha_de_cds->topo_pilha->artista.estilo_musical, estilo) == 0)
        {
            empilharNovoCd(segunda_pilha, pilha_de_cds->topo_pilha->artista);
        }
        else
        {
            empilharNovoCd(&auxliar, pilha_de_cds->topo_pilha->artista);
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

void separarPorAnoDeLancamento(Pilha *pilha_de_cds, Pilha *pilha_lancamentos, int ano_lancamento, bool *ano_l_d)
{
    Pilha auxliar;
    auxliar.topo_pilha = NULL;
    //bool ano_lancamento_disponivel = false;

    while (pilha_de_cds->topo_pilha !=NULL)
    {
        if(pilha_de_cds->topo_pilha->artista.ano == ano_lancamento)
        {
            empilharNovoCd(pilha_lancamentos, pilha_de_cds->topo_pilha->artista);
            *ano_l_d = true;
        }
        else
        {
            empilharNovoCd(&auxliar, pilha_de_cds->topo_pilha->artista);
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
        separarPorEstilo(pilha_de_cds, pop, "Pop");
        break;
    case 2: // rock
        separarPorEstilo(pilha_de_cds, rock, "Rock");
        break;
    case 3: // sertanejo
        separarPorEstilo(pilha_de_cds, sertanejo, "Sertanejo");
        break;
    case 4: // forro
        separarPorEstilo(pilha_de_cds, forro, "Forro");
        break;
    case 5: // axe
        separarPorEstilo(pilha_de_cds, axe, "Axe");
        break;
    default:
        break;
    }
}

void empilharNovamente(Pilha *pilha_ano_lancamento, Pilha *pop, Pilha *rock, Pilha *sertanejo, Pilha *forro, Pilha *axe, Pilha *pilha_de_cds)
{
    while (pilha_ano_lancamento->topo_pilha !=NULL)
    {
        if(strcmp(pilha_ano_lancamento->topo_pilha->artista.estilo_musical, "Pop") == 0)
            empilharNovoCd(pop, pilha_ano_lancamento->topo_pilha->artista);

        else if(strcmp(pilha_ano_lancamento->topo_pilha->artista.estilo_musical, "Rock") == 0)
            empilharNovoCd(rock, pilha_ano_lancamento->topo_pilha->artista);
        
        else if(strcmp(pilha_ano_lancamento->topo_pilha->artista.estilo_musical, "Sertanejo") == 0)
            empilharNovoCd(sertanejo, pilha_ano_lancamento->topo_pilha->artista);
        
        else if(strcmp(pilha_ano_lancamento->topo_pilha->artista.estilo_musical, "Forro") == 0)
            empilharNovoCd(forro, pilha_ano_lancamento->topo_pilha->artista);
        
        else if(strcmp(pilha_ano_lancamento->topo_pilha->artista.estilo_musical, "Axe") == 0)
            empilharNovoCd(axe, pilha_ano_lancamento->topo_pilha->artista);
        else
            empilharNovoCd(pilha_de_cds, pilha_ano_lancamento->topo_pilha->artista);

        Pont apagar = pilha_ano_lancamento->topo_pilha;

        pilha_ano_lancamento->topo_pilha = pilha_ano_lancamento->topo_pilha->proximo_abaixo;

        free(apagar);
    }
    
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    Pilha pilha_de_cds;
    pilha_de_cds.topo_pilha = NULL;

    Pilha pop, rock, sertanejo, forro, axe;

    pop.topo_pilha = rock.topo_pilha = sertanejo.topo_pilha = forro.topo_pilha = axe.topo_pilha = NULL;

    Pilha pilha_ano_lancamento;
    pilha_ano_lancamento.topo_pilha = NULL;
    unsigned int ano;

    int op = 0;
    int estilo = 0;

    bool ano_lancamento_disponivel = false;

    Artista cd;

    do
    {
        menu();

        scanf("%d", &op);

        switch (op)
        {
        case 0:
            break;
        case 1:
            printf("\n\n(int) Codigo: "); scanf("%d", &cd.codigo);
            printf("\n(str) Titulo: "); scanf(" %[^\n]s", cd.titulo);
            printf("\n(str) Artista: "); scanf(" %[^\n]s", cd.artista);
            printf("\n(int) Ano: "); scanf("%d", &cd.ano);
            printf("\n(int) Estilo: 1 - Pop, 2 - Rock, 3 - Sertanejo, 4 - Forro, 5 - Axe\n: ");
            scanf("%d", &estilo);

            switch (estilo)
            {
            case 1:
                strcpy(cd.estilo_musical, "Pop");
                break;
            case 2:
                strcpy(cd.estilo_musical, "Rock");
                break;
            case 3:
                strcpy(cd.estilo_musical, "Sertanejo");
                break;
            case 4:
                strcpy(cd.estilo_musical, "Forro");
                break;
            case 5:
                strcpy(cd.estilo_musical, "Axe");
                break;
            }
            empilharNovoCd(&pilha_de_cds, cd);
            break;

        case 2:
            exibirPilhaCds(&pilha_de_cds);
            break;
        case 3:
            printf("\n(int) Estilo que deseja separar: \n1 - Pop, 2 - Rock, 3 - Sertanejo, 4 - Forro, 5 - Axe: ");
            scanf("%d", &estilo);
            distibuirCds(&pilha_de_cds, estilo, &pop, &rock, &sertanejo, &forro, &axe);
            break;
        case 4:
            printf("\n(int) Estilo que deseja imprimir: 1 - Pop, 2 - Rock, 3 - Sertanejo, 4 - Forro, 5 - Axe\n: ");
            scanf("%d", &estilo);

            switch (estilo)
            {
            case 1:
                exibirPilhaCds(&pop);
                break;
            case 2:
                exibirPilhaCds(&rock);
                break;
            case 3:
                exibirPilhaCds(&sertanejo);
                break;
            case 4:
                exibirPilhaCds(&forro);
                break;
            case 5:
                exibirPilhaCds(&axe);
                break;

            default:
                break;
            }
            break;
        case 5:

            printf("\nAno de lançamento que deseja empilhar: ");
            scanf("%d", &ano);
            separarPorAnoDeLancamento(&pop, &pilha_ano_lancamento, ano, &ano_lancamento_disponivel);
            separarPorAnoDeLancamento(&rock, &pilha_ano_lancamento, ano, &ano_lancamento_disponivel);
            separarPorAnoDeLancamento(&sertanejo, &pilha_ano_lancamento, ano, &ano_lancamento_disponivel);
            separarPorAnoDeLancamento(&forro, &pilha_ano_lancamento, ano, &ano_lancamento_disponivel);
            separarPorAnoDeLancamento(&axe, &pilha_ano_lancamento, ano, &ano_lancamento_disponivel);
            separarPorAnoDeLancamento(&pilha_de_cds, &pilha_ano_lancamento, ano, &ano_lancamento_disponivel);
            if(ano_lancamento_disponivel == true)
            {
                printf("\nMostrando a nova pilha baseado no ano: \n");
                exibirPilhaCds(&pilha_ano_lancamento);
                empilharNovamente(&pilha_ano_lancamento, &pop, &rock, &sertanejo, &forro, &axe, &pilha_de_cds);
            }
            else
            {
                printf("\nErro[404]\nNão houve CDs lançados nesse período\n");
            }

            break;

        default:
            printf("%s\n",MSGERRO);
            break;
        }

    }while(op != 0);

    return 0;
}
