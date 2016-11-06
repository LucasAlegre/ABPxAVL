#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

pNodoABP* inicializa()
{
    return NULL;
}

pNodoABP* InsereArvore(pNodoABP *a, tipoinfo ch)
{
    if (a == NULL)
    {
        a =  (pNodoABP*) malloc(sizeof(pNodoABP));
        a->info = ch;
        a->esq = NULL;
        a->dir = NULL;
        return a;
    }
    else if (ch < a->info)
        a->esq = InsereArvore(a->esq,ch);
    else if (ch > a->info)
        a->dir = InsereArvore(a->dir,ch);
    return a;
}

void preFixado(pNodoABP *a)
{
    if (a!= NULL)
    {
        printf("%d\n",a->info);
        preFixado(a->esq);
        preFixado(a->dir);
    }
}

void Central(pNodoABP *a)
{
    if (a!= NULL)
    {
        Central(a->esq);
        printf("%d\n",a->info);
        Central(a->dir);
    }
}

void posFixado(pNodoABP *a)
{
    if (a!= NULL)
    {
        posFixado(a->esq);
        posFixado(a->dir);
        printf("%d\n",a->info);
    }
}

pNodoABP* consultaABP(pNodoABP *a, tipoinfo chave)
{

    while (a!=NULL)
    {
        if (a->info == chave )
            return a;     //achou então retorna o ponteiro para o nodo
        if (a->info > chave)
            a = a->esq;
        else
            a = a->dir;
    }
    return NULL; //se não achou
}

pNodoABP* consultaABP2(pNodoABP *a, tipoinfo chave)
{
    if (a!=NULL)
    {

        if (a->info == chave)
            return a;
        if (a->info > chave)
            return consultaABP2(a->esq,chave);
        if (a->info < chave)
            return consultaABP2(a->dir,chave);
        else
            return a;

    }
    else return NULL;
}

///Dada uma arvore e um valor de nodo, retorna o nivel do nodo na arvore e -1 caso não seja encontrado
int nivelNo(pNodoABP* arv, tipoinfo chave)
{
    if (consultaABP(arv, chave) == NULL)
        return -1;

    if(arv->info != chave)
    {
        if(arv->info > chave)
            return nivelNo(arv->esq, chave) + 1;
        else
            return nivelNo(arv->dir, chave) + 1;
    }
    else  //é o nodo procurado
        return 1;
}

int Altura (pNodoABP *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
      return 0;
    else
    {
       Alt_Esq = Altura (a->esq);
       Alt_Dir = Altura (a->dir);
       if (Alt_Esq > Alt_Dir)
         return (1 + Alt_Esq);
       else
         return (1 + Alt_Dir);
     }
}

int Calcula_FB(pNodoABP *a)
{
    return (Altura(a->esq) - Altura(a->dir));
}

int fator(pNodoABP *a, int ch)
{
    pNodo a = consultaABP(a, ch);

    if(a != NULL)   //Se o nó está na árvore retorna seu fator
        return Calcula_FB(a);

    else{
        printf("No não encontrado\n");
        return -111;                    //Nó não está na árvore
    }
}

int ehAVL(pNodoABP *a)
{
    if(abs(Calcula_FB(a)) >= 2)  //Se o fator da ráiz é >=2 ou <= -2, não é AVL
        return 0;

    else           //Fator entre -1 e 1 é AVL
        return 1;

}

int ehARB(pNodoABP *a)
{
    if(Altura(a->esq)+1 > (2 * (Altura(a->dir)+1)) || Altura(a->dir)+1 > (2 * (Altura(a->esq)+1)))
        return 0;
    else
        return 1;

}

///Dada uma arvore e duas chavees, retorna true se houver caminho entre as duas na arvore, e false caso contrário
bool achaCaminho(pNodoABP* arv, tipoinfo chave1, tipoinfo chave2)
{
    if(consultaABP(arv, chave1) == NULL || consultaABP(arv, chave2) == NULL)
        return false;

    if(arv->info == chave1)
        return true;

    if((arv->info > chave1) && (arv->info > chave2))
        return achaCaminho(arv->esq, chave1, chave2);

    if((arv->info < chave1) && (arv->info < chave2))
        return achaCaminho(arv->dir, chave1, chave2);

    else
        return false;

}

///Dada duas ABP's, retorna true se forem iguais em forma e conteúdo e false caso contrário
int arvoresIguais(pNodoABP* arv1, pNodoABP* arv2)
{
    if ((arv1 == NULL) && (arv2 == NULL))
        return 1;

    else if ((arv1 != NULL) && (arv2 != NULL))
        return  ((arv1->info == arv2->info) &&
                arvoresIguais(arv1->esq, arv2->esq) &&
                arvoresIguais(arv1->dir, arv2->dir));
    else
        return 0;
}
