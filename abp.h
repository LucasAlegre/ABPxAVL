#ifndef ABP_H
#define ABP_H
typedef int tipoinfo;

struct TNodoABP{
        tipoinfo info;
        struct TNodoABP *esq;
        struct TNodoABP *dir;
};

typedef struct TNodoABP pNodoABP;

pNodoABP* inicializa_ABP();
pNodoABP* insere_arvore(pNodoABP *a, tipoinfo ch,unsigned long int * compara);
pNodoABP* consulta_ABP(pNodoABP *a, tipoinfo chave,unsigned long int * compara);
pNodoABP* consulta_ABP2(pNodoABP *a, tipoinfo chave, unsigned long int * compara);
pNodoABP* deleteNode(pNodoABP* root, int key,unsigned long int * compara);

int maior_fator_ABP(pNodoABP* a);
int conta_nodos_ABP(pNodoABP *a);
void pre_fixado(pNodoABP *a);
void pos_fixado(pNodoABP *a);
void central(pNodoABP *a);

int altura_ABP(pNodoABP *a);
int nivel_no(pNodoABP * arv, int valor,unsigned long int * compara);

int arvores_iguais(pNodoABP* arv1, pNodoABP* arv2);
int calcula_FB_ABP(pNodoABP *a);
int eh_AVL(pNodoABP *a);

#endif

