/*
UFRGS - INF 01203 – Estruturas de Dados
Trabalho Final 2016/2
Comparação	do	Desempenho	de	Árvores Binárias
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

/* Exemplo de uso dos argumentos para main
O programa l� um arquivo texto como entrada e gera um arquivo como sa�da com o conte�do do arquivo de entrada convertido para letras mai�sculas
Para chamar, digite "exemplo entrada.txt saida.txt" */

int main(int argc, char* argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{

    int lineno=0;

    FILE * entrada;
    FILE * saida;

    char *palavra, linha[1000]; // linhas a serem lidas do arquivo
    char separador[]= {" 0123456789,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

    if (argc != 3)  //o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
    {
        printf ("N�mero incorreto de par�metros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
        return 1;
    }
    else
    {











    }
}
