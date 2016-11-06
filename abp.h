typedef int tipoinfo;

struct TNodoAVL{
        tipoinfo info;
        struct TNodoAVL *esq;
        struct TNodoAVL *dir;
};

typedef struct TNodoAVL pNodoABP;

pNodoABP* inicializa();
pNodoABP* InsereArvore(pNodoABP *a, tipoinfo ch);
void preFixado(pNodoABP *a);
void posFixado(pNodoABP *a);
void Central(pNodoABP *a);
pNodoABP* consultaABP(pNodoABP *a, tipoinfo chave);
pNodoABP* consultaABP2(pNodoABP *a, tipoinfo chave);
int nivelNo(pNodoABP * arv, int valor);
bool achaCaminho(pNodoABP* arv, int valor1, int valor2);
int arvoresIguais(pNodoABP* arv1, pNodoABP* arv2);
int fator(pNodoABP *a, int ch);
int ehAVL(pNodoABP *a);
int ehARB(pNodoABP *a);
