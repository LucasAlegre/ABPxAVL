/*
UFRGS - INF 01203 – Estruturas de Dados
Trabalho Final 2016/2
Comparação do Desempenho de	Árvores Binárias
ABP X AVL
Alunos:
Lucas Nunes Alegre
Guilherme Gomes Haetinger
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#include "abp.h"
#include "avl.h"

int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{
    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    pNodoABP* abp = inicializa_ABP();
    pNodoABP* abpAux = inicializa_ABP();
    pNodoAVL* avl = inicializa_AVL();
    pNodoAVL* avlAux = inicializa_AVL();

    clock_t start, end, elapsed=0; //para contar o tempo DOUBLE

    int nodo;
    int op;
    unsigned long int comparacoes = 0;
    int rotacoes = 0;
    int ok = 0;

    FILE* roteiro;
    FILE* nodos;

    char space;
    char nomeArq[20];
    char operacao;

    if (argc != 2)  //o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
    {
        printf ("Número incorreto de parâmetros.\n");
        return 1;
    }
    else
    {

        do
        {
            printf("Executar para ABP ou AVL? (ABP - 1, AVL - 2)\n");
            scanf("%d", &op);
        }
        while(op != 1 && op != 2);

        if(op == 1)  //ABP
        {

            roteiro = fopen(argv[1], "r"); // abre o arquivo para leitura -- argv[1] � o primeiro par�metro ap�s o nome do arquivo.
            if (roteiro == NULL) //se n�o conseguiu abrir o arquivo
            {
                printf ("Erro ao abrir o arquivo %s",argv[1]);
                perror("oi");
                return 1;
            }
            printf("******VERSÃO COM ABP*********\n");
            while(fscanf(roteiro,"%c",&operacao) != EOF)
            {

                fscanf(roteiro,"%c", &space);
                operacao = toupper(operacao);
                switch(operacao)
                {
                case 'I':
                    fscanf(roteiro,"%s\n",nomeArq);
                    nodos = fopen(nomeArq,"r");
                    if (nodos == NULL) //se n�o conseguiu abrir o arquivo
                    {
                        printf ("Erro ao abrir o arquivo %s", nomeArq);
                        return 1;
                    }
                    printf("Inserindo dados do arquivo %s\n", nomeArq);
                    while(fscanf(nodos,"%d\n",&nodo) != EOF)
                    {
                        start = clock();
                        abp = insere_arvore(abp, nodo, &comparacoes);
                        end = clock();
                        elapsed += (end - start)*1000/CLOCKS_PER_SEC;
                    }

                    break;
                case 'R':
                    fscanf(roteiro,"%s\n",nomeArq);
                    nodos = fopen(nomeArq,"r");
                    if (nodos == NULL) //se n�o conseguiu abrir o arquivo
                    {
                        printf ("Erro ao abrir o arquivo %s", nomeArq);
                        return 1;
                    }
                    printf("Removendo dados do arquivo %s\n", nomeArq);
                    while(fscanf(nodos,"%d\n",&nodo) != EOF)
                    {
                        start = clock();
                        abp = deleteNode(abp, nodo, &comparacoes);
                        end = clock();
                        elapsed += (end - start)*1000/CLOCKS_PER_SEC;
                    }
                    break;
                case 'C':
                    fscanf(roteiro,"%s\n",nomeArq);
                    nodos = fopen(nomeArq,"r");
                    if (nodos == NULL) //se n�o conseguiu abrir o arquivo
                    {
                        printf ("Erro ao abrir o arquivo %s", nomeArq);
                        return 1;
                    }
                    printf("Consultando dados do arquivo %s\n", nomeArq);
                    while(fscanf(nodos,"%d\n",&nodo) != EOF)
                    {
                        start = clock();
                        abpAux = consulta_ABP(abp, nodo, &comparacoes);
                        end = clock();
                        elapsed += (end - start)*1000/CLOCKS_PER_SEC;
                    }

                    break;
                case 'E':
                    printf("*****ESTATÍSTICAS ABP******\n");

                    printf("Tempo: %ld ms\n", elapsed);
                    printf("Nodos : %d\n", conta_nodos_ABP(abp));
                    printf("Altura: %d\n", altura_ABP(abp));
                    printf("Fator: %d\n", maior_fator_ABP(abp));
                    printf("Comparacoes:   %lu\n", comparacoes);
                    printf("Rotações: 0\n");
                    printf("---------------------------------------\n");

                    comparacoes = 0;
                    elapsed = 0;
                    break;
                default:
                    printf("Operação Inexistente!\n");

                }

            }
        }
        else if(op == 2)  //Roda AVL
        {

            roteiro = fopen(argv[1], "r"); // abre o arquivo para leitura -- argv[1] � o primeiro par�metro ap�s o nome do arquivo.
            if (roteiro == NULL) //se n�o conseguiu abrir o arquivo
            {
                printf ("Erro ao abrir o arquivo %s",argv[1]);
                perror("oi");
                return 1;
            }
            printf("******VERSÃO COM AVL*********\n");
            while(fscanf(roteiro,"%c",&operacao) != EOF)
            {

                fscanf(roteiro,"%c", &space);
                operacao = toupper(operacao);
                switch(operacao)
                {
                case 'I':
                    ok = 0;
                    fscanf(roteiro,"%s\n",nomeArq);
                    nodos = fopen(nomeArq,"r");
                    if (nodos == NULL) //se n�o conseguiu abrir o arquivo
                    {
                        printf ("Erro ao abrir o arquivo %s", nomeArq);
                        return 1;
                    }
                    printf("Inserindo dados do arquivo %s\n", nomeArq);
                    while(fscanf(nodos,"%d\n",&nodo) != EOF)
                    {
                        start = clock();
                        avl = insere_AVL(avl, nodo, &ok, &comparacoes,&rotacoes);
                        end = clock();
                        elapsed += (end - start)*1000/CLOCKS_PER_SEC;
                    }

                    break;
                case 'R':
                    fscanf(roteiro,"%s\n",nomeArq);
                    nodos = fopen(nomeArq,"r");
                    if (nodos == NULL) //se n�o conseguiu abrir o arquivo
                    {
                        printf ("Erro ao abrir o arquivo %s", nomeArq);
                        return 1;
                    }
                    printf("Removendo dados do arquivo %s\n", nomeArq);
                    while(fscanf(nodos,"%d\n",&nodo) != EOF)
                    {
                        start = clock();
                        avl = removeNO(avl, nodo, &comparacoes,&rotacoes);
                        end = clock();
                        elapsed += (end - start)*1000/CLOCKS_PER_SEC;
                    }
                    break;
                case 'C':
                    fscanf(roteiro,"%s\n",nomeArq);
                    nodos = fopen(nomeArq,"r");
                    if (nodos == NULL) //se n�o conseguiu abrir o arquivo
                    {
                        printf ("Erro ao abrir o arquivo %s", nomeArq);
                        return 1;
                    }
                    printf("Consultando dados do arquivo %s\n", nomeArq);
                    while(fscanf(nodos,"%d\n",&nodo) != EOF)
                    {
                        start = clock();
                        avlAux = consulta_AVL(avl, nodo, &comparacoes);
                        end = clock();
                        elapsed += (end - start)*1000/CLOCKS_PER_SEC;
                    }

                    break;
                case 'E':
                    printf("******ESTATÍSTICAS AVL*******\n");

                    printf("Tempo: %ld ms\n", elapsed);
                    printf("Nodos : %d\n", conta_nodos_AVL(avl));
                    printf("Altura: %d\n", altura_AVL(avl));
                    printf("Fator: %d\n", maior_fator_AVL(avl));
                    printf("Comparacoes:   %lu\n", comparacoes);
                    printf("Rotações: %d\n", rotacoes);
                    printf("---------------------------------------\n");

                    comparacoes = 0;
                    elapsed = 0;
                    rotacoes = 0;

                    break;
                default:
                    printf("Operação Inexistente!\n");

                }

            }


        }
    }

    return 0;

}
