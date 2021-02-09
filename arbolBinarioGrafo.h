#ifndef __ARBOLBIN__
#define __ARBOLBIN__

#define MAX_VERT_NAME 64

typedef enum {VERTICE, INDICE} llaveOrd;

typedef 
struct _nodoGrafoA
{
	char vertice[MAX_VERT_NAME];
	unsigned int idx;
	struct _nodoGrafoA *izq, *der, *padre;
} nodoGrafoA;

typedef
struct 
{
	nodoGrafoA *raiz;
	unsigned int numNodos, numNiveles;
	llaveOrd sKey;
} arbolBinGrafo;

extern nodoGrafoA *basuraGrafoA;

void initArbolBinGrafo(arbolBinGrafo *arb, llaveOrd sK);

nodoGrafoA *creaNodoGrafoA(char *v, int idx);

int liberaNodoGrafoA(nodoGrafoA *nd);

nodoGrafoA *buscaV(arbolBinGrafo *arb, char *v);

nodoGrafoA *buscaI(arbolBinGrafo *arb, unsigned int idx);

void decrementaIndiceV(arbolBinGrafo *arb, unsigned int idx);

void decrementaIndiceI(arbolBinGrafo *arb, unsigned int idx);

void busquedaInversaPar(arbolBinGrafo *arb, unsigned int idx, nodoGrafoA **n);

void inserta (arbolBinGrafo *arb, nodoGrafoA *nd);

void inorder (arbolBinGrafo *arb);

void inorderV (arbolBinGrafo *arb);

void preorder (arbolBinGrafo *arb);

void posorder (arbolBinGrafo *arb);

unsigned int cuentaNiveles(arbolBinGrafo *arb);

nodoGrafoA *minArbolGrafo(arbolBinGrafo *arb);

nodoGrafoA *maxArbolGrafo(arbolBinGrafo *arb);

nodoGrafoA *_minArbolGrafo(nodoGrafoA *x);

nodoGrafoA *_maxArbolGrafo(nodoGrafoA *x);

nodoGrafoA *sucesor (nodoGrafoA *x);

nodoGrafoA *predecesor (nodoGrafoA *x);

nodoGrafoA *borraNodoGrafoA(arbolBinGrafo *arb, nodoGrafoA *z);

void eliminaArbolCandida (arbolBinGrafo *arb);

void eliminaArbol (arbolBinGrafo *arb);

void liberaBasuraGrafoA();

#endif
