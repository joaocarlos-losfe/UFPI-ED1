#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>

#define alta 1
#define media 2
#define baixa 3

typedef struct 
{
    int numero_processo;
    int tempo_processamento;
    int prioridade;
    int qtd_vezes_passou_na_fila;

}ProcessoInfo;

typedef struct aux
{
	ProcessoInfo processo;
	struct aux* proximo_processo;

}Processo,  *DadosProcesso;

typedef struct
{
	DadosProcesso inicio;
	DadosProcesso fim;

}FilaProcessos;

int numeroDeProcessoNaFila(FilaProcessos *fila_processos);
void inserirProcessoNaFila(FilaProcessos *fila_processos, ProcessoInfo processo_info);
bool removerProcessoDaFila(FilaProcessos *fila_processos);
void exibirProcessos(FilaProcessos *fila_processos);
void executarProcesso(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *fila_de_processos_nivel_abaixo);
void executarProcessoFilaPrioridadeBaixa(FilaProcessos *processos_prioridade_3);
void proximosProcessos(FilaProcessos *processos_prioridade_1, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);
void proximoProcesso(FilaProcessos *fila_processos);

void areaParaDebug(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);
int rand();

void menu();
void cadastroProcesso(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);
void exibirListadeprocessosDefinida(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);
void filaProcessoParaExecutar(FilaProcessos *processos_prioridade_1, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);


int main()
{
    setlocale(LC_ALL, "Portuguese");

    FilaProcessos fila_de_processos_maior_prioridade; fila_de_processos_maior_prioridade.inicio = fila_de_processos_maior_prioridade.fim = NULL; // alta
    FilaProcessos processos_prioridade_2; processos_prioridade_2.inicio = processos_prioridade_2.fim = NULL; // media
    FilaProcessos processos_prioridade_3; processos_prioridade_3.inicio = processos_prioridade_3.fim = NULL; // baixa

    //areaParaDebug(&fila_de_processos_maior_prioridade, &processos_prioridade_2, &processos_prioridade_3);

    
    int op;
    do
    {
        menu();
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            cadastroProcesso(&fila_de_processos_maior_prioridade, &processos_prioridade_2, &processos_prioridade_3);
            break;
        case 2:
            filaProcessoParaExecutar(&fila_de_processos_maior_prioridade, &processos_prioridade_2, &processos_prioridade_3);
            break;
        case 3:
            exibirListadeprocessosDefinida(&fila_de_processos_maior_prioridade, &processos_prioridade_2, &processos_prioridade_3);
            break;
        case 4:
            proximosProcessos(&fila_de_processos_maior_prioridade, &processos_prioridade_2, &processos_prioridade_3);
            break;
        default:
            break;
        }
    
    }while (op != 0);
    
    return 0;
    
}

void proximoProcesso(FilaProcessos *fila_processos)
{
    if (numeroDeProcessoNaFila(fila_processos) != 0)
    {
        printf("\n Numero: %d", fila_processos->inicio->processo.numero_processo);
        printf("\n Tempo: %d", fila_processos->inicio->processo.tempo_processamento);
        printf("\n Prioridade: %d ", fila_processos->inicio->processo.prioridade);
        if(fila_processos->inicio->processo.prioridade == alta)
            printf("(alta)");
        else if (fila_processos->inicio->processo.prioridade == media)
            printf("(media)");
        else if (fila_processos->inicio->processo.prioridade == baixa)
            printf("(baixa)");
    }
    else
        printf("Lista de processos vazia...");
    
}

void proximosProcessos(FilaProcessos *processos_prioridade_1, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3)
{
    printf("\n Proximo processo esperado a ser executado da fila de prioridade alta: ");
    proximoProcesso(processos_prioridade_1);

    printf("\n\n Proximo processo esperado a ser executado da fila de prioridade media: ");
    proximoProcesso(processos_prioridade_2);

    printf("\n\n Proximo processo esperado a ser executado da fila de prioridade baixa: ");
    proximoProcesso(processos_prioridade_3);
}

void filaProcessoParaExecutar(FilaProcessos *processos_prioridade_1, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3)
{
    int op;

    printf("\n Executar processos de: \n");
    printf("\n 1 - Fila de prioridade Alta");
    printf("\n 2 - Fila de prioridade Media");
    printf("\n 3 - Fila de prioridade Baixa\n\n > ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        executarProcesso(processos_prioridade_1, processos_prioridade_2);
        break;
    case 2:
        executarProcesso(processos_prioridade_2, processos_prioridade_3);
        break;
    case 3:
        executarProcessoFilaPrioridadeBaixa(processos_prioridade_3);
        break;
    default:
        break;
    }
}

void exibirListadeprocessosDefinida(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3)
{
    int op;

    printf("\n Exibir processos de: \n");
    printf("\n 1 - Fila de prioridade Alta");
    printf("\n 2 - Fila de prioridade Media");
    printf("\n 3 - Fila de prioridade Baixa");
    printf("\n 4 - Todos as filas de prioridade\n\n > ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        printf("\n Processos com prioridade alta: ");
        exibirProcessos(fila_de_processos_maior_prioridade);
        break;

    case 2:
        printf("\n Processos com prioridade media: ");
        exibirProcessos(processos_prioridade_2);
        break;

    case 3:
        printf("\n Processos com prioridade baixa: ");
        exibirProcessos(processos_prioridade_3);
        break;
    
    case 4:
        printf("\n Processos com prioridade alta: ");
        exibirProcessos(fila_de_processos_maior_prioridade);

        printf("\n Processos com prioridade baixa: ");
        exibirProcessos(processos_prioridade_2);

        printf("\n Processos com prioridade media: ");
        exibirProcessos(processos_prioridade_3);

        break;
    
    default:
        break;
    }
}

void cadastroProcesso(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3)
{
    ProcessoInfo processo;

    printf("\n Inserindo processo...\n");
    processo.numero_processo = randomizar(100, 9999);
    printf("\n Defina uma prioridade: 1 - alta, 2 - média, 3 - baixa: ");
    scanf("%d", &processo.prioridade);
    printf("\n Defina um tempo de processamento: ");
    scanf("%d", &processo.tempo_processamento);
    processo.qtd_vezes_passou_na_fila = 0;

    printf("\n Processo inserido na fila de processos com prioridade ");

    switch (processo.prioridade)
    {
    case alta:
        inserirProcessoNaFila(fila_de_processos_maior_prioridade, processo);
        printf("Alta");
        break;
    case media:
        inserirProcessoNaFila(processos_prioridade_2, processo);
        printf("Media");
        break;
    case baixa:
        inserirProcessoNaFila(processos_prioridade_3, processo);
        printf("Baixa");
        break;
    default:
        break;
    }

}

int randomizar(int inicio_intervalo, int fim_intervalo)
{
    int valor;
    srand((unsigned) time(NULL));
    valor = inicio_intervalo + (rand()) % fim_intervalo;

    return valor;
}

void menu()
{
    int op;
    printf("\n 0 - Sair");
    printf("\n 1 - Inserir processo na fila");
    printf("\n 2 - Executar processo");
    printf("\n 3 - Mostrar processo das filas");
    printf("\n 4 - Mostrar proximo processo que irá utilizar o processador");
    printf("\n 5 - Mostrar quantos processos tem em cada fila");
    printf("\n 6 - Mostrar quanto tempo falta para executar os processos de uma determinada fila ");
    printf("\n 7 - Mostrar quanto tempo de processamento ainda falta para chegar em um determinado processo");
    printf("\n 8 - Mostrar quanto tempo de processamento ainda falta para chegar em um determinado processo");
    printf("\n 9 - Mostrar quanto tempo de processamento ainda restam para terminar cada fila e todas as filas");
    printf("\n\n > ");
   
}

int numeroDeProcessoNaFila(FilaProcessos *fila_processos)
{
    DadosProcesso end = fila_processos->inicio;
    int contador = 0;

    while (end != NULL)
    {
        contador+=1;

        end = end->proximo_processo;
    }
    
    return contador;
}

void inserirProcessoNaFila(FilaProcessos *fila_processos, ProcessoInfo processo_info)
{
    DadosProcesso novo_processo = (DadosProcesso) malloc(sizeof(Processo));
    novo_processo->processo = processo_info;
    novo_processo->proximo_processo = NULL;

    if(fila_processos->inicio == NULL)
        fila_processos->inicio = novo_processo;
    else
        fila_processos ->fim->proximo_processo = novo_processo;
    
    fila_processos ->fim = novo_processo;
}

bool removerProcessoDaFila(FilaProcessos *fila_processos)
{
    if(fila_processos->inicio == NULL)
    {
        printf("Fila vazia...");
        return false; // fila vazia
    }
        
    DadosProcesso apagar_processo = fila_processos ->inicio;

    fila_processos->inicio = fila_processos->inicio->proximo_processo;

    free(apagar_processo);

    if(fila_processos->inicio == NULL) 
        fila_processos->fim = NULL;
    
    return true; // processo removido do inicio da fila com sucesso
}

void exibirProcessos(FilaProcessos *fila_processos)
{   
                //edereço  do primeiro elemento da fila
    DadosProcesso end = fila_processos->inicio;

    if(end != NULL)
    {
        int n_processo = 1;

        while (end != NULL)
        {
            printf("\n processo %d: \n", n_processo);

            printf("\n Numero: %d", end->processo.numero_processo);
            printf("\n Tempo: %d", end->processo.tempo_processamento);
            printf("\n Prioridade: %d ", end->processo.prioridade);
            if(end->processo.prioridade == alta)
                printf("(alta)");
            else if (end->processo.prioridade == media)
                printf("(media)");
            else if (end->processo.prioridade == baixa)
                printf("(baixa)");

            printf("\n quantidade de vezes que passou na fila: %d\n", end->processo.qtd_vezes_passou_na_fila);
        
            end = end->proximo_processo;
            n_processo++;
        }
    }
    else
        printf("\n fila vazia...\n");
    
}

void executarProcesso(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *fila_de_processos_nivel_abaixo)
{
    if (numeroDeProcessoNaFila(fila_de_processos_maior_prioridade) != 0)
    {
        fila_de_processos_maior_prioridade->inicio->processo.qtd_vezes_passou_na_fila+=1;
        fila_de_processos_maior_prioridade->inicio->processo.tempo_processamento -= 1;

        if(fila_de_processos_maior_prioridade->inicio->processo.tempo_processamento == 0)
        {
            removerProcessoDaFila(fila_de_processos_maior_prioridade);
        }
        else
        {
            if(fila_de_processos_maior_prioridade->inicio->processo.qtd_vezes_passou_na_fila == 1)
            {
                inserirProcessoNaFila(fila_de_processos_maior_prioridade, fila_de_processos_maior_prioridade->inicio->processo);
                removerProcessoDaFila(fila_de_processos_maior_prioridade);
            }
            else
            {
                if(fila_de_processos_maior_prioridade->inicio->processo.prioridade = media)
                {
                    fila_de_processos_maior_prioridade->inicio->processo.prioridade = baixa;
                }
                else
                {
                    fila_de_processos_maior_prioridade->inicio->processo.prioridade = media;
                }

                fila_de_processos_maior_prioridade->inicio->processo.qtd_vezes_passou_na_fila = 0;
                
                inserirProcessoNaFila(fila_de_processos_nivel_abaixo, fila_de_processos_maior_prioridade->inicio->processo);
                removerProcessoDaFila(fila_de_processos_maior_prioridade);
            }
        }
        
    }
    else
    {
        printf("\n Fila vazia\n");
    }

}

void executarProcessoFilaPrioridadeBaixa(FilaProcessos *processos_prioridade_3)
{
    if (numeroDeProcessoNaFila(processos_prioridade_3) != 0)
    {
        processos_prioridade_3->inicio->processo.qtd_vezes_passou_na_fila+=1;
        processos_prioridade_3->inicio->processo.tempo_processamento -= 1;

        if(processos_prioridade_3->inicio->processo.tempo_processamento == 0)
        {
            removerProcessoDaFila(processos_prioridade_3);
        }
        else if(processos_prioridade_3->inicio->processo.qtd_vezes_passou_na_fila > 0)
        {
            inserirProcessoNaFila(processos_prioridade_3, processos_prioridade_3->inicio->processo);
            removerProcessoDaFila(processos_prioridade_3);
        }
    }
    else
    {
        printf("\n Fila vazia\n");
    }
}


void areaParaDebug(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3)
{
    ProcessoInfo processo;

    processo.numero_processo = 1; 
    processo.tempo_processamento = 3; // 1, 
    processo.prioridade = alta;
    processo.qtd_vezes_passou_na_fila = 0; //1

    inserirProcessoNaFila(fila_de_processos_maior_prioridade, processo);

    processo.numero_processo = 7777;
    processo.tempo_processamento = 3;
    processo.prioridade = alta;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(fila_de_processos_maior_prioridade, processo);

    processo.numero_processo = 5555;
    processo.tempo_processamento = 4;
    processo.prioridade = alta;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(fila_de_processos_maior_prioridade, processo);


    // fila de processos 2
    processo.numero_processo = 11;
    processo.tempo_processamento = 4;
    processo.prioridade = media;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(processos_prioridade_2, processo);

    processo.numero_processo = 22;
    processo.tempo_processamento = 1;
    processo.prioridade = media;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(processos_prioridade_2, processo);

    processo.numero_processo = 33;
    processo.tempo_processamento = 2;
    processo.prioridade = media;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(processos_prioridade_2, processo);


    // fila de processos 3
    processo.numero_processo = 1111;
    processo.tempo_processamento = 5;
    processo.prioridade = baixa;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(processos_prioridade_3, processo);

    processo.numero_processo = 2222;
    processo.tempo_processamento = 2;
    processo.prioridade = baixa;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(processos_prioridade_3, processo);

    processo.numero_processo = 3333;
    processo.tempo_processamento = 3;
    processo.prioridade = baixa;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(processos_prioridade_3, processo);

    //exibindos os processos

    executarProcesso(fila_de_processos_maior_prioridade, processos_prioridade_2);
    executarProcesso(fila_de_processos_maior_prioridade, processos_prioridade_2);
    executarProcesso(fila_de_processos_maior_prioridade, processos_prioridade_2);
    executarProcesso(fila_de_processos_maior_prioridade, processos_prioridade_2);
    executarProcesso(fila_de_processos_maior_prioridade, processos_prioridade_2);
    executarProcesso(fila_de_processos_maior_prioridade, processos_prioridade_2);
    executarProcesso(fila_de_processos_maior_prioridade, processos_prioridade_2);
    executarProcesso(fila_de_processos_maior_prioridade, processos_prioridade_2);

    exibirProcessos(processos_prioridade_2);

    
        
}