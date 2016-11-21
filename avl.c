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
    maior = a->FB;

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
        a=rotacao_esquerda(a,rotacoes);
    }
    else
    {
        a=rotacao_dupla_esquerda(a,rotacoes);
    }
    a->FB = 0;
    *ok = 0;

    return a;
}

///Insere o nodo na AVL
pNodoAVL* insere_AVL(pNodoAVL *a, TipoInfo x, int *ok,unsigned long int *compara, int* rotacoes)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
      x, a chave a ser inserida e h a altura da árvore */

    if (a == NULL)
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
        a->esq = insere_AVL(a->esq,x,ok, compara,rotacoes);
        if (*ok)
        {
            switch (a->FB)
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
        a->dir = insere_AVL(a->dir,x,ok,compara,rotacoes);
        if (*ok)
        {
            switch (a->FB)
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

pNodoAVL * maior_noAVL(pNodoAVL* node)
{
    pNodoAVL* current = node;

    /* loop down to find the leftmost leaf */
    while (current->dir != NULL)
        current = current->dir;

    return current;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

pNodoAVL* removeNO(pNodoAVL *a, int key,unsigned long int* compara,int* rotacoes)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (a == NULL)
    {
        (*compara)++;
        return a;
    }

    // If the key to be deleted is smaller than the
    // a's key, then it lies in left subtree
    if ( key < a->info )
    {
        (*compara)++;
        a->esq = removeNO(a->esq, key, compara,rotacoes);
    }

    // If the key to be deleted is greater than the
    // a's key, then it lies in right subtree
    else if( key > a->info )
    {
        a->dir = removeNO(a->dir, key, compara,rotacoes);
        (*compara)++;
    }

    // if key is same as a's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (a->esq == NULL) || (a->dir == NULL) )
        {
            pNodoAVL *temp = a->esq ? a->esq :
                             a->dir;

            // No child case
            if (temp == NULL)
            {
                temp = a;
                a = NULL;
            }
            else // One child case
                *a = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            pNodoAVL* temp = maior_noAVL(a->esq);

            // Copy the inorder successor's data to this node
            a->info = temp->info;

            // Delete the inorder successor
            a->esq = removeNO(a->esq, temp->info, compara,rotacoes);
        }
    }

    // If the tree had only one node then return
    if (a == NULL)
        return a;


    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = calcula_FB(a);

    // If this node becomes unbalanced, then there are 4 cases



        // Left Left Case
    if (balance > 1 && calcula_FB(a->esq) >= 0)
        return rotacao_direita(a, rotacoes);

    // Left Right Case
    if (balance > 1 && calcula_FB(a->esq) < 0)
    {
        a->esq =  rotacao_esquerda(a->esq,rotacoes);
        return rotacao_direita(a,rotacoes);
    }

    // Right Right Case
    if (balance < -1 && calcula_FB(a->dir) <= 0)
        return rotacao_esquerda(a, rotacoes);

    // Right Left Case
    if (balance < -1 && calcula_FB(a->dir) > 0)
    {
        a->dir = rotacao_direita(a->dir,rotacoes);
        return rotacao_esquerda(a,rotacoes);
    }



/*

    // Left Left Case
    if(a->esq != NULL && balance > 1)
    {
        if (a->esq->FB >= 0)
            return rotacao_direita(a,rotacoes);

        // Left Right Case
        if (a->esq->FB < 0)
        {
            a->esq =  rotacao_esquerda(a->esq,rotacoes);
            return rotacao_direita(a,rotacoes);
        }
    }
    else if(balance > 1)
        return rotacao_direita(a, rotacoes);

    else if(a->dir != NULL && balance < -1)
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
    else if(balance < -1)
        return rotacao_esquerda(a,rotacoes);
*/
    else
        return a;
}

///Retorna o ponteiro para o nodo procurado, NULL caso não encontrado
pNodoAVL* consulta_AVL(pNodoAVL *a, TipoInfo chave,unsigned long int* compara)
{

    while (a!=NULL)
    {
        (*compara)++;
        if (a->info == chave )
            return a;     //achou então retorna o ponteiro para o nodo
        if (a->info > chave)
            a = a->esq;
        else
            a = a->dir;
    }
    return NULL; //se não achou
}
