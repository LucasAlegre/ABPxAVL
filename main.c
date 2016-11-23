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
#include "arquivos.h"

int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{
    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    int op;

    FILE* roteiro;
    FILE* saida;

    if (argc != 3)  //o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
    {
        printf("Número incorreto de parâmetros.\n Digite ABPxAVL roteiro.txt saida.txt\n");
        return 1;
    }
    else
    {

        saida = fopen(argv[2], "w");
        if (saida == NULL) //se n�o conseguiu abrir o arquivo
        {
            printf ("Erro ao criar o arquivo %s",argv[2]);
            return 1;
        }

        roteiro = fopen(argv[1], "r"); // abre o arquivo para leitura -- argv[1] � o primeiro par�metro ap�s o nome do arquivo.
        if (roteiro == NULL) //se n�o conseguiu abrir o arquivo
        {
            printf ("Erro ao abrir o arquivo %s",argv[1]);
            return 1;
        }

        op = le_opcao();

        if(op == 1)
        {
            if(processa_ABP(roteiro, saida))
                printf("ERROR\n");
        }
        else if(op == 2)
        {
            if(processa_AVL(roteiro, saida))
                printf("ERROR\n");
        }

    }

    fclose(roteiro);
    fclose(saida);

    return 0;

}
