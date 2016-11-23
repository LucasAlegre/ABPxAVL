#include <stdio.h>
#include <time.h>
#include "arquivos.h"
#include "abp.h"
#include "avl.h"

///Le opção referente à AVL ou ABP
int le_opcao()
{
    int op;

    do
    {
        printf("Executar para ABP ou AVL? (ABP - 1, AVL - 2)\n");
        scanf("%d", &op);
    }
    while(op != 1 && op != 2);

    return op;
}

///Processa o arquivo roteiro, realizando as operações informadas e escrevendo
///no arquivo de saida. Retorna 1 em caso de erro
int processa_ABP(FILE* roteiro, FILE* saida)
{
    pNodoABP* abp = inicializa_ABP();
    pNodoABP* abpAux = inicializa_ABP();

    clock_t start, end, elapsed=0; //para contar o tempo DOUBLE
    unsigned long int comparacoes = 0;

    char space;
    char nome_arq[20];
    char operacao;

    FILE* nodos;
    int nodo;

    fprintf(saida,"**********VERSÃO COM ABP**********\n");
    while(fscanf(roteiro,"%c",&operacao) != EOF)
    {

        fscanf(roteiro,"%c", &space);
        operacao = toupper(operacao);
        switch(operacao)
        {
        case 'I':
            fscanf(roteiro,"%s\n",nome_arq);
            nodos = fopen(nome_arq,"r");
            if (nodos == NULL) //se n�o conseguiu abrir o arquivo
            {
                fprintf (saida,"Erro ao abrir o arquivo %s", nome_arq);
                return 1;
            }
            fprintf(saida, "Inserindo dados do arquivo %s\n", nome_arq);
            while(fscanf(nodos,"%d\n",&nodo) != EOF)
            {
                start = clock();
                abp = insere_arvore(abp, nodo, &comparacoes);
                end = clock();
                elapsed += (end - start)*1000/CLOCKS_PER_SEC;
            }

            break;
        case 'R':
            fscanf(roteiro,"%s\n",nome_arq);
            nodos = fopen(nome_arq,"r");
            if (nodos == NULL) //se n�o conseguiu abrir o arquivo
            {
                fprintf (saida,"Erro ao abrir o arquivo %s", nome_arq);
                return 1;
            }
            fprintf(saida,"Removendo dados do arquivo %s\n", nome_arq);
            while(fscanf(nodos,"%d\n",&nodo) != EOF)
            {
                start = clock();
                abp = deleteNode(abp, nodo, &comparacoes);
                end = clock();
                elapsed += (end - start)*1000/CLOCKS_PER_SEC;
            }
            break;
        case 'C':
            fscanf(roteiro,"%s\n",nome_arq);
            nodos = fopen(nome_arq,"r");
            if (nodos == NULL) //se n�o conseguiu abrir o arquivo
            {
                fprintf (saida,"Erro ao abrir o arquivo %s", nome_arq);
                return 1;
            }
            fprintf(saida,"Consultando dados do arquivo %s\n", nome_arq);
            while(fscanf(nodos,"%d\n",&nodo) != EOF)
            {
                start = clock();
                abpAux = consulta_ABP(abp, nodo, &comparacoes);
                end = clock();
                elapsed += (end - start)*1000/CLOCKS_PER_SEC;
            }

            break;
        case 'E':
            fprintf(saida,"**********ESTATÍSTICAS ABP**********\n");

            fprintf(saida,"Tempo: %ld ms\n", elapsed);
            fprintf(saida,"Nodos: %d\n", conta_nodos_ABP(abp));
            fprintf(saida,"Altura: %d\n", altura_ABP(abp));
            fprintf(saida,"Fator: %d\n", maior_fator_ABP(abp));
            fprintf(saida,"Comparacoes: %lu\n", comparacoes);
            fprintf(saida,"Rotações: 0\n");
            fprintf(saida,"---------------------------------------\n");

            comparacoes = 0;
            elapsed = 0;
            break;
        default:
            fprintf(saida,"Operação Inexistente!\n");

        }

    }
    return 0;
}

///Processa o arquivo roteiro, realizando as operações informadas e escrevendo
///no arquivo de saida. Retorna 1 em caso de erro
int processa_AVL(FILE* roteiro, FILE* saida)
{

    pNodoAVL* avl = inicializa_AVL();
    pNodoAVL* avlAux = inicializa_AVL();

    char space;
    char nome_arq[20];
    char operacao;

    clock_t start, end, elapsed=0;
    unsigned long int comparacoes = 0;

    int rotacoes = 0;
    int ok;

    FILE* nodos;
    int nodo;

    fprintf(saida,"**********VERSÃO COM AVL**********\n");
    while(fscanf(roteiro,"%c",&operacao) != EOF)    //le operacao do arquivo
    {

        fscanf(roteiro,"%c", &space);   //le espaço em branco
        operacao = toupper(operacao);   //torna maisculo o char de operaçao
        switch(operacao)
        {
        case 'I':

            fscanf(roteiro,"%s\n",nome_arq);
            nodos = fopen(nome_arq,"r");
            if (nodos == NULL) //se n�o conseguiu abrir o arquivo
            {
                fprintf (saida,"Erro ao abrir o arquivo %s", nome_arq);
                return 1;
            }
            fprintf(saida,"Inserindo dados do arquivo %s\n", nome_arq);
            while(fscanf(nodos,"%d\n",&nodo) != EOF)
            {
                ok = 0;
                start = clock();
                avl = insere_AVL(avl, nodo, &ok, &comparacoes,&rotacoes);
                end = clock();
                elapsed += (end - start)*1000/CLOCKS_PER_SEC;
            }

            break;
        case 'R':
            fscanf(roteiro,"%s\n",nome_arq);
            nodos = fopen(nome_arq,"r");
            if (nodos == NULL) //se n�o conseguiu abrir o arquivo
            {
                fprintf (saida,"Erro ao abrir o arquivo %s", nome_arq);
                return 1;
            }
            fprintf(saida,"Removendo dados do arquivo %s\n", nome_arq);
            while(fscanf(nodos,"%d\n",&nodo) != EOF)
            {
                start = clock();
                avl = remove_no(avl, nodo, &comparacoes,&rotacoes);
                end = clock();
                elapsed += (end - start)*1000/CLOCKS_PER_SEC;
            }
            break;
        case 'C':
            fscanf(roteiro,"%s\n",nome_arq);
            nodos = fopen(nome_arq,"r");
            if (nodos == NULL) //se n�o conseguiu abrir o arquivo
            {
                fprintf (saida,"Erro ao abrir o arquivo %s", nome_arq);
                return 1;
            }
            fprintf(saida,"Consultando dados do arquivo %s\n", nome_arq);
            while(fscanf(nodos,"%d\n",&nodo) != EOF)
            {
                start = clock();
                avlAux = consulta_AVL(avl, nodo, &comparacoes);
                end = clock();
                elapsed += (end - start)*1000/CLOCKS_PER_SEC;
            }

            break;
        case 'E':
            fprintf(saida,"**********ESTATÍSTICAS AVL**********\n");

            fprintf(saida,"Tempo: %ld ms\n", elapsed);
            fprintf(saida,"Nodos: %d\n", conta_nodos_AVL(avl));
            fprintf(saida,"Altura: %d\n", altura_AVL(avl));
            fprintf(saida,"Fator: %d\n", maior_fator_AVL(avl));
            fprintf(saida,"Comparacoes: %lu\n", comparacoes);
            fprintf(saida,"Rotações: %d\n", rotacoes);
            fprintf(saida,"---------------------------------------\n");

            comparacoes = 0;   //Zera contadores
            elapsed = 0;
            rotacoes = 0;

            break;
        default:
            fprintf(saida,"Operação Inexistente!\n");

        }

    }
    return 0;
}

