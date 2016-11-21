typedef int tipoinfo;

struct TNodoABP{
        tipoinfo info;
        struct TNodoABP *esq;
        struct TNodoABP *dir;
};

typedef struct TNodoABP pNodoABP;

pNodoABP* inicializa_ABP();
pNodoABP* insere_arvore(pNodoABP *a, tipoinfo ch, long int * compara);
pNodoABP* consulta_ABP(pNodoABP *a, tipoinfo chave, long int * compara);
pNodoABP* consulta_ABP2(pNodoABP *a, tipoinfo chave);
pNodoABP* deleteNode(pNodoABP* root, int key, long int * compara);

int conta_nodos_ABP(pNodoABP *a);

void pre_fixado(pNodoABP *a);
void pos_fixado(pNodoABP *a);
void central(pNodoABP *a);

int altura_ABP(pNodoABP *a);
int nivel_no(pNodoABP * arv, int valor, long int * compara);

int arvores_iguais(pNodoABP* arv1, pNodoABP* arv2);
int calcula_FB_ABP(pNodoABP *a);
int eh_AVL(pNodoABP *a);
