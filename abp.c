#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

///Inicializa ABP
pNodoABP* inicializa_ABP()
{
    return NULL;
}

///Insere um nodo na ABP
pNodoABP* insere_arvore(pNodoABP *a, tipoinfo ch)
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
        a->esq = insere_arvore(a->esq,ch);
    else if (ch > a->info)
        a->dir = insere_arvore(a->dir,ch);
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
pNodoABP* consulta_ABP(pNodoABP *a, tipoinfo chave)
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
int nivel_no(pNodoABP* arv, tipoinfo chave)
{
    if (consultaABP(arv, chave) == NULL)
        return -1;

    if(arv->info != chave)
    {
        if(arv->info > chave)
            return nivel_no(arv->esq, chave) + 1;
        else
            return nivel_no(arv->dir, chave) + 1;
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
    if(abs(Calcula_FB(a)) >= 2)  //Se o fator da ráiz é >=2 ou <= -2, não é AVL
        return 0;

    else           //Fator entre -1 e 1 é AVL
        return 1;

}

///Dada uma arvore e duas chavees, retorna true se houver caminho entre as duas na arvore, e false caso contrário
int acha_caminho(pNodoABP* arv, tipoinfo chave1, tipoinfo chave2)
{
    if(consulta_ABP(arv, chave1) == NULL || consulta_ABP(arv, chave2) == NULL)
        return 0;

    if(arv->info == chave1)
        return 1;

    if((arv->info > chave1) && (arv->info > chave2))
        return acha_caminho(arv->esq, chave1, chave2);

    if((arv->info < chave1) && (arv->info < chave2))
        return acha_caminho(arv->dir, chave1, chave2);

    else
        return 0;

}

///exclui a raíz, substituindo-a pelo antecessor da árvore
pNodoABP * raizPorAntecessor(pNodoABP *arv)
{

    pNodoABP *elo, *busca;
    busca = NULL;
    if(arv == NULL) return NULL;

    if(arv->dir == NULL && arv->esq == NULL) free(arv); //caso for folha simplesmente retira

    if (arv->esq == NULL)
    {
          busca = arv->dir;//caso não houver antecessor(arvore esquerda vazia) retorna o primeiro da direita
          free(arv);
          return busca;
    }
    elo = arv; busca = arv->esq;
    while (busca->dir != NULL)// posiciona busca no antecessor e elo no anterior a este
    {
          elo = busca;
          busca = busca->dir;
    }
    if (elo != arv)
    {
          elo->dir = busca->esq;// caso exista mais de um nodo entre a raiz e o antecessor,
          busca->esq = arv->esq;// substitui o nodo a esquerda
    }
    busca->dir = arv->dir; // substitui o nodo a direita do antecessor pelo da raiz
    free (arv);// libera a raiz
    return busca;
 }

 ///conulta o nodo anterior ao da chave
pNodoABP * consultaAnterior(pNodoABP *arv, int chave)
{

    while (arv!=NULL && arv->dir != NULL && arv->esq != NULL)
    {
          if (arv->dir->info == chave || arv->esq->info == chave)
             return arv; //achou então retorna o ponteiro para o nodo anterior ao da chave
          else
          {
            if (arv->info > chave)
               arv = arv->esq;
            else
               arv = arv->dir;
          }
    }
            return NULL; //se não achou
}

///remove um novo com magnitude key
pNodoABP * removeABP(pNodoABP* arv, int key)
{
      pNodoABP * elo,  *aux;
      aux = consultaABP(arv, key);//atribui aux ao nodo que será removido

      if(aux != NULL)
      {
          elo = consultaAnterior(arv, key); //atribui elo ao nodo anterior de aux

          if(elo != NULL)
          {
          if(elo->info >= key) elo->esq = raizPorAntecessor(aux);//dependendo da relação do módulo de aux e elo
          else elo->dir = raizPorAntecessor(aux);//coloca a raiz já substituida pela função raizPorAntecessor(Arv *r) e faz as devidas substituições
          }
      }
      return arv;
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
