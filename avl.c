#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "avl.h"

///Inicializa AVL
pNodoAVL* inicializa_AVL()
{
    return NULL;
}

///Retorna o numero de nodos na AVL
int conta_nodos_AVL(pNodoAVL *a)
{
    if(a == NULL)
        return 0;
    else
        return (1 + conta_nodos_AVL(a->dir) + conta_nodos_AVL(a->esq));
}

///Retorna a altura na AVL
int altura_AVL(pNodoAVL *a)
{
    int alt_esq, alt_dir;
    if (a == NULL)
        return 0;
    else
    {
        alt_esq = altura_AVL(a->esq);
        alt_dir = altura_AVL(a->dir);
        if (alt_esq > alt_dir)
            return (1 + alt_esq);
        else
            return (1 + alt_dir);
    }
}

///Calcula o fator do nodo dado
int calcula_FB(pNodoAVL *a)
{
    return (altura_AVL(a->esq) - altura_AVL(a->dir));
}

///Retorna o maior fator da árvore
int maior_fator_AVL(pNodoAVL* a)
{
    int maior_direita, maior_esquerda;
    int maior;

    if(a == NULL)
        return 0;

    maior_direita = maior_fator_AVL(a->dir);
    maior_esquerda = maior_fator_AVL(a->esq);
    maior = abs(a->FB);

    if(maior < maior_direita)
        maior = maior_direita;

    if(maior < maior_esquerda)
        maior = maior_esquerda;

    return maior;

}

///Desenha a AVL
void desenha(pNodoAVL *a, int nivel)
{
    int x;

    if (a !=NULL)
    {
        for (x=1; x<=nivel; x++)
            printf("=");
        printf("%d FB= %d\n", a->info, calcula_FB(a));
        if (a->esq != NULL) desenha(a->esq, (nivel+1));
        if (a->dir != NULL) desenha(a->dir, (nivel+1));
    }
}

///Retorna 1 se a árvore é AVL, 0 caso contrário
int is_AVL(pNodoAVL *a)
{
    int alt_esq, alt_dir;

    if (a!=NULL)
    {
        alt_esq = altura_AVL(a->esq);
        alt_dir = altura_AVL(a->dir);
        return ( (alt_esq - alt_dir <2) && (alt_dir - alt_esq <2) && (is_AVL(a->esq)) && (is_AVL(a->dir)) );
    }
    else
        return 1;
}

///Rotação direita
pNodoAVL* rotacao_direita(pNodoAVL *pt, int *rotacoes)
{
    pNodoAVL* ptu;

    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0;
    pt = ptu;

    (*rotacoes)++;

    return pt;
}

///Rotação esquerda
pNodoAVL* rotacao_esquerda(pNodoAVL *pt, int *rotacoes)
{
    pNodoAVL* ptu;

    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0;
    pt = ptu;

    (*rotacoes)++;

    return pt;
}

///Rotação dupla direita
pNodoAVL* rotacao_dupla_direita (pNodoAVL* pt, int *rotacoes)
{
    pNodoAVL* ptu, *ptv;

    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;

    if (ptv->FB == 1)
        pt->FB = -1;
    else
        pt->FB = 0;
    if (ptv->FB == -1)
        ptu->FB = 1;
    else
        ptu->FB = 0;
    pt = ptv;

    (*rotacoes)++;
    (*rotacoes)++;

    return pt;
}

///Rotação dupla esquerda
pNodoAVL* rotacao_dupla_esquerda (pNodoAVL* pt, int *rotacoes)
{
    pNodoAVL *ptu, *ptv;

    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;
    if (ptv->FB == -1)
        pt->FB = 1;
    else
        pt->FB = 0;
    if (ptv->FB == 1)
        ptu->FB = -1;
    else
        ptu->FB = 0;
    pt = ptv;

    (*rotacoes)++;
    (*rotacoes)++;

    return pt;
}


pNodoAVL* caso1 (pNodoAVL* a, int *ok, int *rotacoes)
{
    pNodoAVL *ptu;

    ptu = a->esq;
    if (ptu->FB == 1)
    {
        a = rotacao_direita(a, rotacoes);
    }
    else
    {
        a = rotacao_dupla_direita(a, rotacoes);
    }

    a->FB = 0;
    *ok = 0;

    return a;
}

pNodoAVL* caso2 (pNodoAVL *a, int *ok, int *rotacoes)
{
    pNodoAVL *ptu;

    ptu = a->dir;
    if (ptu->FB == -1)
    {
        a = rotacao_esquerda(a,rotacoes);
    }
    else
    {
        a = rotacao_dupla_esquerda(a,rotacoes);
    }
    a->FB = 0;
    *ok = 0;

    return a;
}

///Insere o nodo na AVL
pNodoAVL* insere_AVL(pNodoAVL *a, TipoInfo x, int *ok , unsigned long int *comparacoes, int* rotacoes)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
      x, a chave a ser inserida e h a altura da árvore */
    (*comparacoes)++;

    if (a == NULL)   //Chegou no fim da árvore, insere o nodo
    {
        a = (pNodoAVL*) malloc(sizeof(pNodoAVL));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (x < a->info)
    {
        a->esq = insere_AVL(a->esq, x, ok, comparacoes, rotacoes);
        if (*ok)
        {
            switch (a->FB)     //Testa o fator para poder alterá-lo de acordo com cada caso
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case  0:
                a->FB = 1;
                break;
            case  1:
                a = caso1(a,ok,rotacoes);
                break;
            }
        }
    }
    else
    {
        a->dir = insere_AVL(a->dir,x,ok,comparacoes,rotacoes);
        if (*ok)
        {
            switch (a->FB)      //Testa o fator para poder alterá-lo de acordo com cada caso
            {
            case  1:
                a->FB = 0;
                *ok = 0;
                break;
            case  0:
                a->FB = -1;
                break;
            case -1:
                a = caso2(a,ok,rotacoes);
                break;
            }
        }
    }

    return a;
}

///Retorna o maior no da AVL
pNodoAVL* maior_no_AVL(pNodoAVL* a)
{
    pNodoAVL* aux = a;

    while (aux->dir != NULL)
        aux = aux->dir;

    return aux;
}

///Remoção de um nodo na AVL
pNodoAVL* remove_no(pNodoAVL *a, int key, unsigned long int* comparacoes ,int* rotacoes)
{
    pNodoAVL *temp;

    (*comparacoes)++;

    if (a == NULL)  //Chegou no fim, retorna NULL
    {
        return a;
    }

    if ( key < a->info )   //Nó a ser removido está a esquerda
    {
        a->esq = remove_no(a->esq, key, comparacoes,rotacoes);
    }

    else if( key > a->info )   //Nó a ser removido está a esquerda
    {
        a->dir = remove_no(a->dir, key, comparacoes,rotacoes);
    }

    else   //É o nó a ser removido
    {

        if( (a->esq == NULL) || (a->dir == NULL) )
        {
            if(a->esq == NULL)
                temp = a->dir;
            else
                temp = a->esq;

            if (temp == NULL)  //Se o nó a ser removido não tem filhos, o remove
            {
                temp = a;
                a = NULL;
                free(temp);
            }
            else             //Se um dos filhos não é NULL, remove o nodo e retorna o filho
            {
                free(a);
                a = temp;
                return a;
            }

        }
        else   //Se o nodo possui dois filhos, remove e troca pelo maior da subarvore esquerda
        {
            temp = maior_no_AVL(a->esq);
            a->info = temp->info;
            a->esq = remove_no(a->esq, temp->info, comparacoes, rotacoes);
        }
    }

    if (a == NULL)
        return a;

    a->FB = calcula_FB(a);

    // Left Left Case
    if(a->esq != NULL && a->FB > 1)
    {
        if (a->esq->FB >= 0)
            return rotacao_direita(a,rotacoes);

        // Left Right Case
        if (a->esq->FB < 0)
        {
            a->esq = rotacao_esquerda(a->esq, rotacoes);
            return rotacao_direita(a,rotacoes);
        }
    }
    else if(a->FB > 1)
        return rotacao_direita(a, rotacoes);

    else if(a->dir != NULL && a->FB < -1)
    {
        // Right Right Case
        if (a->dir->FB <= 0)
            return rotacao_esquerda(a,rotacoes);

        // Right Left Case
        if (a->dir->FB > 0)
        {
            a->dir = rotacao_direita(a->dir,rotacoes);
            return rotacao_esquerda(a,rotacoes);
        }

    }
    else if(a->FB < -1)
        return rotacao_esquerda(a,rotacoes);

    return a;
}

///Retorna o ponteiro para o nodo procurado, NULL caso não encontrado
pNodoAVL* consulta_AVL(pNodoAVL *a, TipoInfo chave, unsigned long int* comparacoes)
{

    while (a != NULL)
    {
        (*comparacoes)++;

        if (a->info == chave )
        {
            return a;     //achou então retorna o ponteiro para o nodo
        }

        if (a->info > chave)
            a = a->esq;
        else
            a = a->dir;
    }
    return NULL; //se não achou
}
