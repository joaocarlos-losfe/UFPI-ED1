/*
	Quinta questão referente a segunda avaliação da discpina de Estrurura de dados I.

	Autores: João Carlos de Sousa Fé && Vitor José Ferreira dos Santos de Santana.
    
	Data de inicio da resolução deste exercicio: 29/05/2021

	Questão 5. Implementação dinamica
    
            Escalonador é uma parte do Sistema Operacional que escolhe de uma fila de prontos o próximo 
        processo a ocupar o processador. Suponha que nosso escalonador mantenha 3 filas dinâmicas, de 
        acordo com a prioridade do processo. 
        Cada processo possui as seguintes informações: o seu número, o tempo de processamento que o 
        mesmo necessita em segundos e a prioridade do mesmo para que ele possa ser inserido na fila de 
        acordo com a sua prioridade. 
        O escalonador deve sempre escolher primeiro os processos da fila de maior prioridade e somente 
        passar para outra fila quando todos os processos da fila atual tiver sido executado pelo menos 2 vezes, 
        ou seja, ficar vazia. Quando o escalonador retira o primeiro processo da fila para usar o processador, o mesmo só pode 
        ficar 1s utilizando o processador, terminado este tempo o escalonador diminui de 1 o tempo de 
        processamento deste processo e verifica seu valor. Se o valor do tempo de processamento atual for 0, o 
        processo é finalizado, ou seja, retirado da fila, caso contrário, será verificado quantas vezes o processo 
        passou nesta fila para decidir em qual fila o mesmo será inserido. Se o processo passou somente 1 vez 
        será colocado ao final da mesma fila, se passou 2 vezes será colocado ao final da próxima fila de 
        prioridade abaixo da atual. Caso ele já esteja na última fila, ou seja, na fila de menor prioridade, o 
        processo será inserido ao final desta fila até que o mesmo termine independente do número de vezes 
        que já passou por ela.
        Faça um programa em C que tenha um menu de opções para inserir processos em uma fila do 
        escalonador, para o escalonador escolher o processo(caso não existia nenhum processo na fila emitir 
        uma mensagem), para mostrar os processos das filas, para mostrar o próximo processo que irá utilizar 
        o processador, mostrar quantos processos tem em cada fila, para mostrar quanto tempo falta para 
        executar os processos de uma determinada fila e para mostrar quanto tempo de processamento ainda 
        falta para chegar em um determinado processo e mostrar quanto tempo de processamento ainda restam 
        para terminar cada fila e todas as filas
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <time.h>

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

}Processo,  *PontProcesso; // mesma coisa que Processo*

typedef struct
{
	PontProcesso inicio;
	PontProcesso fim;

}FilaProcessos;

int numeroDeProcessoNaFila(FilaProcessos *fila_processos);
void inserirProcessoNaFila(FilaProcessos *fila_processos, ProcessoInfo processo_info);
bool removerProcessoDaFila(FilaProcessos *fila_processos, ProcessoInfo *processo);
void exibirProcessos(FilaProcessos *fila_processos);
void executarProcesso(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *fila_de_processos_nivel_abaixo);
void executarProcessoFilaPrioridadeBaixa(FilaProcessos *processos_prioridade_3);
void proximosProcessos(FilaProcessos *processos_prioridade_1, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);
void proximoProcesso(FilaProcessos *fila_processos);
void mostrarQuantosProcessosTemEmcadaFila(FilaProcessos *processos_prioridade_1, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);
int tempoRestanteParaFinalizarFila(FilaProcessos *fila_processos);
void processamentoRestanteTodasAsfilas(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);

void areaParaDebug(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);
int randomizar();

void menu();
void cadastroProcesso(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);
void exibirListadeprocessosDefinida(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);
void filaProcessoParaExecutar(FilaProcessos *processos_prioridade_1, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);
void tempoRestanteFilasMenu(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);
void processamentoRestanteTodasAsfilas(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3);

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
        case 5:
            mostrarQuantosProcessosTemEmcadaFila(&fila_de_processos_maior_prioridade, &processos_prioridade_2, &processos_prioridade_3);
            break;
        case 6:
            tempoRestanteFilasMenu(&fila_de_processos_maior_prioridade, &processos_prioridade_2, &processos_prioridade_3);
            break;
        case 7:
            processamentoRestanteTodasAsfilas(&fila_de_processos_maior_prioridade, &processos_prioridade_2, &processos_prioridade_3);
            break;
        default:
            break;
        }
    
    }while (op != 0);
    
    return 0;
    
}

void processamentoRestanteTodasAsfilas(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3)
{
    printf("\n Tempo restante fila prioridade alta: %d segundos", tempoRestanteParaFinalizarFila(fila_de_processos_maior_prioridade));
    printf("\n Tempo restante fila prioridade media: %d segundos", tempoRestanteParaFinalizarFila(processos_prioridade_2));
    printf("\n Tempo restante fila prioridade baixa: %d segundos\n", tempoRestanteParaFinalizarFila(processos_prioridade_3));

    int soma_tempo_todas_as_filas = tempoRestanteParaFinalizarFila(fila_de_processos_maior_prioridade) + 
                                    tempoRestanteParaFinalizarFila(processos_prioridade_2) + 
                                    tempoRestanteParaFinalizarFila(processos_prioridade_3);

    printf(" Tempo de processamento ainda restam para terminar todas as filas: %d\n", soma_tempo_todas_as_filas);
}

void tempoRestanteFilasMenu(FilaProcessos *fila_de_processos_maior_prioridade, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3)
{
    int op;

    printf("\n Selecione a fila para ver o tempo restante dos processos: \n");
    printf("\n 1 - Fila de prioridade Alta");
    printf("\n 2 - Fila de prioridade Media");
    printf("\n 3 - Fila de prioridade Baixa\n\n > ");
    scanf("%d", &op);

    int tempo;

    switch (op)
    {
    case 1:
        tempo = tempoRestanteParaFinalizarFila(fila_de_processos_maior_prioridade);
        break;
    case 2:
        tempo = tempoRestanteParaFinalizarFila(processos_prioridade_2);
        break;
    case 3:
        tempo = tempoRestanteParaFinalizarFila(processos_prioridade_3);
        break;
    default:
        break;
    }

    printf("\n Tempo restante: %d segundos\n", tempo);
}


int tempoRestanteParaFinalizarFila(FilaProcessos *fila_processos)
{
    PontProcesso end = fila_processos->inicio;
    int tempo = 0;

    while (end != NULL)
    {
        tempo = tempo + end->processo.tempo_processamento;

        end = end->proximo_processo;
    }
    return tempo;
}

void mostrarQuantosProcessosTemEmcadaFila(FilaProcessos *processos_prioridade_1, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3)
{
    printf("\n Quantidade de processos com prioridade 1 (alta): %d", numeroDeProcessoNaFila(processos_prioridade_1));
    printf("\n Quantidade de processos com prioridade 2 (media): %d", numeroDeProcessoNaFila(processos_prioridade_2));
    printf("\n Quantidade de processos com prioridade 3 (baixa): %d\n", numeroDeProcessoNaFila(processos_prioridade_3));
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
    printf("\n Proximo processo esperado a ser executado da fila de prioridade\n Alta: ");
    proximoProcesso(processos_prioridade_1);

    printf("\n\n Media: \n");
    proximoProcesso(processos_prioridade_2);

    printf("\n\n Baixa: \n");
    proximoProcesso(processos_prioridade_3);
    printf("\n");
}

void filaProcessoParaExecutar(FilaProcessos *processos_prioridade_1, FilaProcessos *processos_prioridade_2, FilaProcessos *processos_prioridade_3)
{
    if (processos_prioridade_1->inicio != NULL)
    {
        executarProcesso(processos_prioridade_1, processos_prioridade_2);
        printf("\n Fila prioridade Alta executada !\n");
    }
    else if(processos_prioridade_2->inicio != NULL)
    {
        executarProcesso(processos_prioridade_2, processos_prioridade_3);
        printf("\n Fila prioridade Media executada !\n");
    }
    else if(processos_prioridade_3->inicio != NULL)
    {
        executarProcessoFilaPrioridadeBaixa(processos_prioridade_3);
        printf("\n Fila prioridade Baixa executada !\n");
    }
    else
        printf("\n Todas as filas de processos estão vazias...\n");
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

        printf("\n Processos com prioridade media: ");
        exibirProcessos(processos_prioridade_2);

        printf("\n Processos com prioridade baixa: ");
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
    processo.numero_processo = randomizar();
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

int randomizar()
{
    int valor;
    srand(time(NULL));
    valor = rand() % 99999;
    return valor;
}

void menu()
{
    printf("\n 0 - Sair");
    printf("\n 1 - Inserir processo na fila");
    printf("\n 2 - Executar processo");
    printf("\n 3 - Mostrar processo das filas");
    printf("\n 4 - Mostrar proximo processo que irá utilizar o processador");
    printf("\n 5 - Mostrar quantos processos tem em cada fila");
    printf("\n 6 - Mostrar quanto tempo falta para executar os processos de uma determinada fila ");
    printf("\n 7 - Mostrar quanto tempo de processamento ainda restam para terminar cada fila e todas as filas");
    printf("\n\n > ");
   
}

int numeroDeProcessoNaFila(FilaProcessos *fila_processos)
{
    PontProcesso end = fila_processos->inicio;
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
    PontProcesso novo_processo = (PontProcesso) malloc(sizeof(Processo));
    novo_processo->processo = processo_info;
    novo_processo->proximo_processo = NULL;

    if(fila_processos->inicio == NULL)
        fila_processos->inicio = novo_processo;
    else
        fila_processos ->fim->proximo_processo = novo_processo;
    
    fila_processos ->fim = novo_processo;
}

bool removerProcessoDaFila(FilaProcessos *fila_processos, ProcessoInfo *processo)
{
    if(fila_processos->inicio == NULL)
    {
        printf("Fila vazia...");
        return false; // fila vazia
    }

    *processo = fila_processos->inicio->processo; // salva o processo do inicio
        
    PontProcesso apagar_processo = fila_processos ->inicio;

    fila_processos->inicio = fila_processos->inicio->proximo_processo;

    free(apagar_processo);

    if(fila_processos->inicio == NULL) 
        fila_processos->fim = NULL;
    
    return true; // processo removido do inicio da fila com sucesso
}

void exibirProcessos(FilaProcessos *fila_processos)
{   
                //edereço  do primeiro elemento da fila
    PontProcesso end = fila_processos->inicio;

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
    ProcessoInfo processo;
    
    if( fila_de_processos_maior_prioridade->inicio != NULL)
    {
        if (fila_de_processos_maior_prioridade->inicio->processo.tempo_processamento > 0) // verica se ainda é maior que 0 para evitar valor negativo
        {
            fila_de_processos_maior_prioridade->inicio->processo.tempo_processamento -= 1;
            fila_de_processos_maior_prioridade->inicio->processo.qtd_vezes_passou_na_fila +=1;
        }
        
        if(fila_de_processos_maior_prioridade->inicio->processo.tempo_processamento == 0)
        {
            removerProcessoDaFila(fila_de_processos_maior_prioridade, &processo);
            printf("\n Processo removido da mesma fila...\n");
        }
        else if(fila_de_processos_maior_prioridade->inicio->processo.qtd_vezes_passou_na_fila == 1)
        {
           removerProcessoDaFila(fila_de_processos_maior_prioridade, &processo);
           inserirProcessoNaFila(fila_de_processos_maior_prioridade, processo);
           printf("\n Processo movido para o topo da mesma fila...\n");
        }
        else if(fila_de_processos_maior_prioridade->inicio->processo.qtd_vezes_passou_na_fila == 2)
        {
            if(fila_de_processos_maior_prioridade->inicio->processo.prioridade == alta) 
                fila_de_processos_maior_prioridade->inicio->processo.prioridade = media;
            else
                fila_de_processos_maior_prioridade->inicio->processo.prioridade = baixa;

            fila_de_processos_maior_prioridade->inicio->processo.qtd_vezes_passou_na_fila = 0;
            
            removerProcessoDaFila(fila_de_processos_maior_prioridade, &processo);
            inserirProcessoNaFila(fila_de_processos_nivel_abaixo, processo);

            printf("\n Processo movido para a fila de menor prioridade...\n");
        }
        
    }
    else
        printf("\n Fila vazia\n");
    
}

void executarProcessoFilaPrioridadeBaixa(FilaProcessos *processos_prioridade_3)
{
    ProcessoInfo processo;

    if (processos_prioridade_3->inicio != NULL)
    {
        if (processos_prioridade_3->inicio->processo.tempo_processamento > 0)
        {
            processos_prioridade_3->inicio->processo.tempo_processamento -= 1;
            processos_prioridade_3->inicio->processo.qtd_vezes_passou_na_fila +=1;
        }
        
        if(processos_prioridade_3->inicio->processo.tempo_processamento == 0)
        {
            removerProcessoDaFila(processos_prioridade_3, &processo);
            printf("\n Processo removido da mesma fila...\n");
        }
        else if(processos_prioridade_3->inicio->processo.qtd_vezes_passou_na_fila > 0)
        {
            removerProcessoDaFila(processos_prioridade_3, &processo);
            inserirProcessoNaFila(processos_prioridade_3, processo);
            printf("\n Processo movido para o topo da mesma fila...\n");
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
        
}