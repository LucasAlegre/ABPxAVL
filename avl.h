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
pNodoAVL* insere_AVL (pNodoAVL* a, TipoInfo x, int *ok, unsigned long int *comparacoes, int* rotacoes);
pNodoAVL* consulta_AVL(pNodoAVL* a, TipoInfo chave, unsigned long int *comparacoes);
pNodoAVL* maior_no_AVL(pNodoAVL* a);
pNodoAVL* remove_no(pNodoAVL* a, int key, unsigned long int* comparacoes,int *rotacoes);

int conta_nodos_AVL(pNodoAVL *a);
int altura_AVL(pNodoAVL *a);
int calcula_FB(pNodoAVL *a);
int maior_fator_AVL(pNodoAVL* a);
void desenha(pNodoAVL *a, int nivel);
int is_AVL(pNodoAVL *a);

pNodoAVL* rotacao_direita(pNodoAVL *pt, int *rotacoes);
pNodoAVL* rotacao_esquerda(pNodoAVL *pt, int *rotacoes);
pNodoAVL* rotacao_dupla_direita (pNodoAVL *pt, int *rotacoes);
pNodoAVL* rotacao_dupla_esquerda (pNodoAVL *pt, int *rotacoes);
pNodoAVL* caso1(pNodoAVL *a , int *ok, int *rotacoes);
pNodoAVL* caso2(pNodoAVL *a , int *ok, int *rotacoes);

#endif
