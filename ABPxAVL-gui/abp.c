#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

///Inicializa ABP
pNodoABP* inicializa_ABP()
{
    return NULL;
}

///Insere um nodo na ABP
pNodoABP* insere_arvore(pNodoABP *a, tipoinfo ch, long int *compara)
{
    if (a == NULL)
    {
        (*compara)++;
        a =  (pNodoABP*) malloc(sizeof(pNodoABP));
        a->info = ch;
        a->esq = NULL;
        a->dir = NULL;
        return a;
    }
    else if (ch < a->info)
    {
        (*compara)++;
        a->esq = insere_arvore(a->esq,ch, compara);
    }
    else if (ch > a->info)
    {
        (*compara)++;
        a->dir = insere_arvore(a->dir,ch, compara);
    }
    return a;
}

///Retorna o número de nodos na ABP
int conta_nodos_ABP(pNodoABP *a)
{
    if(a == NULL)
        return 0;
    else
        return (1 + conta_nodos_ABP(a->dir) + conta_nodos_ABP(a->esq));
}

///Imprime o caminhamento Pré-Fixado à esquerda
void pre_fixado(pNodoABP *a)
{
    if (a!= NULL)
    {
        printf("%d\n",a->info);
        pre_fixado(a->esq);
        pre_fixado(a->dir);
    }
}

///Imprime o caminhamento Central à esquerda
void central(pNodoABP *a)
{
    if (a!= NULL)
    {
        central(a->esq);
        printf("%d\n",a->info);
        central(a->dir);
    }
}

///Imprime o caminhamento Pós-Fixado à esquerda
void pos_fixado(pNodoABP *a)
{
    if (a!= NULL)
    {
        pos_fixado(a->esq);
        pos_fixado(a->dir);
        printf("%d\n",a->info);
    }
}

///Retorna ponteiro para o nó pesquisado, NULL caso não encontre
pNodoABP* consulta_ABP(pNodoABP *a, tipoinfo chave, long int * compara)
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

///Retorna ponteiro para o nó pesquisado, NULL caso não encontre(versão com recursão)
pNodoABP* consulta_ABP2(pNodoABP *a, tipoinfo chave)
{
    if (a!=NULL)
    {

        if (a->info == chave)
            return a;
        if (a->info > chave)
            return consulta_ABP2(a->esq,chave);
        if (a->info < chave)
            return consulta_ABP2(a->dir,chave);
        else
            return a;

    }
    else return NULL;
}

///Dada uma arvore e um valor de nodo, retorna o nivel do nodo na arvore e -1 caso não seja encontrado
int nivel_no(pNodoABP* arv, tipoinfo chave, long int * compara)
{
    if (consulta_ABP(arv, chave, compara) == NULL)
        return -1;

    if(arv->info != chave)
    {
        (*compara)++;

        if(arv->info > chave)
            return nivel_no(arv->esq, chave, compara) + 1;
        else
            return nivel_no(arv->dir, chave, compara) + 1;
    }
    else  //é o nodo procurado
        return 1;
}

///Retorna a altura da ABP
int altura_ABP(pNodoABP *a)
{
    int alt_esq, alt_dir;
    if (a == NULL)
      return 0;
    else
    {
       alt_esq = altura_ABP(a->esq);
       alt_dir = altura_ABP(a->dir);
       if (alt_esq > alt_dir)
         return (1 + alt_esq);
       else
         return (1 + alt_dir);
     }
}

///Retorna o fator da ABP
int calcula_FB_ABP(pNodoABP *a)
{
    return (altura_ABP(a->esq) - altura_ABP(a->dir));
}

///Retorna 1 se a árvore é AVL, 0 caso contrário
int ehAVL(pNodoABP *a)
{
    if(abs(calcula_FB(a)) >= 2)  //Se o fator da ráiz é >=2 ou <= -2, não é AVL
        return 0;

    else           //Fator entre -1 e 1 é AVL
        return 1;

}


pNodoABP * minValueNode(pNodoABP* node)
{
   pNodoABP* current = node;

    /* loop down to find the leftmost leaf */
    while (current->esq != NULL)
        current = current->esq;

    return current;
}
/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
pNodoABP* deleteNode(pNodoABP* root, int key, long int * compara)
{
    // base case
    if (root == NULL)
    {
        return root;
        (*compara)++;
    }
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->info)
    {
        root->esq = deleteNode(root->esq, key, compara);
        (*compara)++;
    }
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->info)
    {
        root->dir = deleteNode(root->dir, key, compara);
        (*compara)++;
    }
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->esq == NULL)
        {
            (*compara)++;
            pNodoABP *temp = root->dir;
            free(root);
            return temp;
        }
        else if (root->dir == NULL)
        {
            (*compara)++;
            pNodoABP *temp = root->esq;
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        pNodoABP* temp = minValueNode(root->dir);

        // Copy the inorder successor's content to this node
        root->info = temp->info;

        // Delete the inorder successor
        root->dir = deleteNode(root->dir, temp->info, compara);
    }
    return root;
}

///Dada duas ABP's, retorna true se forem iguais em forma e conteúdo e false caso contrário
int arvores_iguais(pNodoABP* arv1, pNodoABP* arv2)
{
    if ((arv1 == NULL) && (arv2 == NULL))
        return 1;

    else if ((arv1 != NULL) && (arv2 != NULL))
        return  ((arv1->info == arv2->info) &&
                arvores_iguais(arv1->esq, arv2->esq) &&
                arvores_iguais(arv1->dir, arv2->dir));
    else
        return 0;
}
