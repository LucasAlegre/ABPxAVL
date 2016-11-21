#ifndef AVL_H
#define AVL_H
typedef int TipoInfo;

struct TNodoAVL{
    TipoInfo info;
    int FB;
    struct TNodoAVL *esq;
    struct TNodoAVL *dir;
};

typedef struct TNodoAVL pNodoAVL;

pNodoAVL* inicializa_AVL();
pNodoAVL* insere_AVL (pNodoAVL * a, TipoInfo x, int *ok);
pNodoAVL* consulta_AVL(pNodoAVL *a, TipoInfo chave);
pNodoAVL* miniValueNode(pNodoAVL* node);
 pNodoAVL * removeNO(pNodoAVL *a, int key);

int conta_nodos_AVL(pNodoAVL *a);

int altura_AVL(pNodoAVL *a);
int calcula_FB(pNodoAVL *a);
void desenha(pNodoAVL *a , int nivel);
int is_AVL(pNodoAVL *a);
int max(int a, int b);

pNodoAVL* rotacao_direita(pNodoAVL *pt);
pNodoAVL* rotacao_esquerda(pNodoAVL *pt);
pNodoAVL* rotacao_dupla_direita (pNodoAVL *pt);
pNodoAVL* rotacao_dupla_esquerda (pNodoAVL *pt);
pNodoAVL* caso1 (pNodoAVL *a , int *ok);
pNodoAVL* caso2 (pNodoAVL *a , int *ok);

#endif