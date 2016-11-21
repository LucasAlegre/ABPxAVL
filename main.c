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
    pNodoAVL* avl = inicializa_AVL();

    clock_t start, end, elapsed; //para contar o tempo DOUBLE

    int lineno=0;
    int nodo;
    int op;

    FILE* roteiro;
    FILE* nodos;

    char space;
    char nomeArq[20];
    char operacao;
    char *palavra, linha[1000]; // linhas a serem lidas do arquivo
    char separador[]= {" 0123456789,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

    if (argc != 2)  //o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
    {
        printf ("N�mero incorreto de par�metros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
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
                        abp = insere_arvore(abp, nodo);
                    }

                    break;
                case 'R':

                    break;
                case 'C':

                    break;
                case 'E':
                    printf("*****ESTATÍSTICAS ABP******\n");
                    break;
                default:
                    printf("Operação Inexistente!\n");

                }

            }
        }
    }

    return 0;

}
