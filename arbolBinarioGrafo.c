#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbolBinarioGrafo.h"

nodoGrafoA *basuraGrafoA = NULL;

void initArbolBinGrafo(arbolBinGrafo *arb, llaveOrd sk)
{
	arb->raiz = NULL;
	arb->numNodos = arb->numNiveles = 0;
	arb->sKey = sk;
}

nodoGrafoA *creaNodoGrafoA(char *v, int idx)
{
	nodoGrafoA *apu;
	
	if (basuraGrafoA == NULL) // Equivalente a if (!basura)
		apu = (nodoGrafoA *)malloc(sizeof(nodoGrafoA));
	else
	{
		apu = basuraGrafoA;
		basuraGrafoA = basuraGrafoA->der;
	}
	if (apu) //Equivalente a apu != NULL
	{
		strncpy (apu->vertice, v, MAX_VERT_NAME-1);\
		apu->idx = idx;
		apu->der = apu->izq = apu->padre = NULL;
	}
	return apu;
}

int liberaNodoGrafoA(nodoGrafoA *nd)
{
		if (nd) //Equivalente a nd != NULL
		{
			nd->der = basuraGrafoA;
			basuraGrafoA = nd;
			return 0;
		}
		return -1;
}

nodoGrafoA *buscaV(arbolBinGrafo *arb, char *v)
{
	nodoGrafoA *x;
	
	if (arb->sKey == INDICE)
	{
	   fprintf(stderr, "Error en buscaV: nos puede buscar un nodo del árbol en funcion del vertice, si el árbol esta ordenado por índices.\n");
	   return NULL;
	}
	
	x = arb->raiz;
	
	while (x != NULL && strncmp(x->vertice, v, MAX_VERT_NAME -1) != 0)
	{
		if (strncmp(v, x->vertice, MAX_VERT_NAME -1) < 0)
			x = x->izq;
		else
			x = x->der;
	}
	return x;
}

nodoGrafoA *buscaI(arbolBinGrafo *arb, unsigned int idx)
{
	nodoGrafoA *x;
	
	if (arb->sKey == VERTICE)
	{
	   fprintf(stderr, "Error en buscaI: nos puede buscar un nodo del árbol en funcion del índice, si el árbol esta ordenado por sus vertices.\n");
	   return NULL;
	}
	
	x = arb->raiz;
	
	while (x != NULL && x->idx != idx)
	{
		if (idx < x->idx)
			x = x->izq;
		else
			x = x->der;
	}
	return x;
}

void inserta (arbolBinGrafo *arb, nodoGrafoA *nd)
{
	nodoGrafoA *x, *y = NULL;
	int nNiv = 0;
	
	if (!nd || !arb)
		return;
		
	nd->izq = nd->der = nd->padre = NULL;
	
	//Recorremos el arbol hasta que "x" salga de él
	//y "y" apunte a una "hoja" del árbol.
	x = arb->raiz;
	while (x != NULL)
	{
		y = x;
		if (arb->sKey == VERTICE)
   	{
   	   if (strncmp(nd->vertice, x->vertice, MAX_VERT_NAME -1) < 0)
   			x = x->izq;
	   	else
		   	x = x->der;
		}
		else
      {
   	   if (nd->idx < x->idx)
   			x = x->izq;
	   	else
		   	x = x->der;
		}
		nNiv++;
	}
	
	nd->padre = y; //conectamos a nd con su nodo padre.
	
	//Insertamos nd abajo de y.
	if (y == NULL) //El árbol esta vacío
		arb->raiz = nd;
	else
	   if (arb->sKey == VERTICE)
	   {
	   	if (strncmp(nd->vertice, y->vertice, MAX_VERT_NAME -1) < 0)
		   	y->izq = nd;
   		else
	   		y->der = nd;
	   }
	   else
	   {
	   	if (nd->idx < y->idx)
		   	y->izq = nd;
   		else
	   		y->der = nd;
	   }
	
	arb->numNodos++;
	if (nNiv+1 > arb->numNiveles)
		arb->numNiveles = nNiv + 1;
}

void __decrementaIndiceV(nodoGrafoA *r, unsigned int idx)
{
	if (r) //Equivalente a r != NULL
	{
		__decrementaIndiceV(r->izq, idx);
		if (r->idx > idx)
			r->idx--;
		__decrementaIndiceV(r->der, idx);
	}
}

void decrementaIndiceV(arbolBinGrafo *arb, unsigned int idx)
{
	if (arb->sKey == VERTICE)
		__decrementaIndiceV(arb->raiz, idx);
}

void __decrementaIndiceI(arbolBinGrafo *arb, nodoGrafoA *r, unsigned int idx)
{
	if (r) //Equivalente a r != NULL
	{
		if (r->idx != idx)
		{
			nodoGrafoA *nd;
			
			nd = creaNodoGrafoA(r->vertice, r->idx);
			if (nd->idx > idx)
				nd->idx--;
			inserta (arb, nd);
		}
		__decrementaIndiceI(arb, r->izq, idx);
		__decrementaIndiceI(arb, r->der, idx);
	}
}

// Esta función elimina el nodo con el índice idx del arbol,
// y decrementoa el atributo idx a aquellos nodos donde éste es
// mayor que el parámetro indice.
void decrementaIndiceI(arbolBinGrafo *arb, unsigned int indice)
{
	if (arb->sKey == INDICE)
	{
		arbolBinGrafo nArb;
	
		initArbolBinGrafo(&nArb, INDICE);
		__decrementaIndiceI(&nArb, arb->raiz, indice);
		eliminaArbol(arb);
		arb->raiz = nArb.raiz;
		arb->numNodos = nArb.numNodos;
		arb->numNiveles = nArb.numNiveles;
		arb->sKey = INDICE;
	}
}

void __busquedaInversaPar(nodoGrafoA *r, unsigned int idx, nodoGrafoA **n)
{
	if (r && *n == NULL) //Equivalente a r != NULL
	{
		__busquedaInversaPar(r->izq, idx, n);
		if (idx == r->idx)
		{
			*n = r;
			return;
		}
		__busquedaInversaPar(r->der, idx, n);
	}
}

void busquedaInversaPar(arbolBinGrafo *arb, unsigned int idx, nodoGrafoA **n)
{
	*n = NULL;
	__busquedaInversaPar(arb->raiz, idx, n);
}

void __inorder(nodoGrafoA *r)
{
	if (r) //Equivalente a r != NULL
	{
		__inorder(r->izq);
		printf("%s, %u ", r->vertice, r->idx);
		__inorder(r->der);
	}
}

void inorder(arbolBinGrafo *arb)
{
	__inorder (arb->raiz);
}

void __inorderV(nodoGrafoA *r)
{
	if (r) //Equivalente a r != NULL
	{
		__inorderV(r->izq);
		printf("%s ", r->vertice);
		__inorderV(r->der);
	}
}

void inorderV(arbolBinGrafo *arb)
{
	__inorderV (arb->raiz);
}

void __preorder(nodoGrafoA *r)
{
	if (r) //Equivalente a r != NULL
	{
		printf("%s, %u ", r->vertice, r->idx);
		__preorder(r->izq);
		__preorder(r->der);
	}
}

void preorder(arbolBinGrafo *arb)
{
	__preorder (arb->raiz);
}

void __posorder(nodoGrafoA *r)
{
	if (r) //Equivalente a r != NULL
	{
		__posorder(r->izq);
		__posorder(r->der);
		printf("%s, %u ", r->vertice, r->idx);
	}
}

void posorder(arbolBinGrafo *arb)
{
	__posorder (arb->raiz);
}

void __cuentaIndices(nodoGrafoA *r, unsigned int indice, unsigned int *maxIndice)
{
	if (r) //Equivalente a r != NULL
	{
		if (*maxIndice < indice)
			*maxIndice = indice;
		__cuentaIndices(r->izq, indice+1, maxIndice);
		__cuentaIndices(r->der, indice+1, maxIndice);
	}
}

unsigned int cuentaNiveles(arbolBinGrafo *arb)
{
	unsigned int max = 0;
	if (arb->raiz)
	{
		__cuentaIndices(arb->raiz, 0, &max);
		return max + 1;
	}
	else
		return 0;
}

nodoGrafoA *minArbolGrafo(arbolBinGrafo *arb)
{
	if (arb->raiz)
		return _minArbolGrafo(arb->raiz);
	return NULL;
}

nodoGrafoA *maxArbolGrafo(arbolBinGrafo *arb)
{
	if (arb->raiz)
		return _maxArbolGrafo(arb->raiz);
	return NULL;
}

nodoGrafoA *_minArbolGrafo(nodoGrafoA *x)
{
		while (x->izq != NULL)
			x = x->izq;
		return x;
}

nodoGrafoA *_maxArbolGrafo(nodoGrafoA *x)
{
	while (x->der != NULL)
			x = x->der;
		return x;
}

nodoGrafoA *sucesor (nodoGrafoA *x)
{
	if (x != NULL)
	{
		nodoGrafoA *y;
		
		if (x->der != NULL)
			return _minArbolGrafo(x->der);
		y = x->padre;
		while (y != NULL && x == y->der)
		{
			x = y;
			y = y->padre;
		}
		return y;
	}
	return NULL;
}

nodoGrafoA *predecesor (nodoGrafoA *x)
{
	if (x != NULL)
	{
		nodoGrafoA *y;
		
		if (x->izq != NULL)
			return _maxArbolGrafo(x->izq);
		y = x->padre;
		while (y != NULL && x == y->izq)
		{
			x = y;
			y = y->padre;
		}
		return y;
	}
	return NULL;
}

nodoGrafoA *borraNodoGrafoA(arbolBinGrafo *arb, nodoGrafoA *z)
{
	nodoGrafoA *x, *y;
	
	if (z->izq == NULL || z->der == NULL) //Si 'z' tiene menos de 2 hijos
		y = z;   // 'y' es el apuntador al nodo que vamos a desconectar 
	else        //del Arbol.
		y = sucesor (z);
		
	if (y->izq != NULL) // 'x' es el apuntor al nodo que está abajo del
		x = y->izq;      // nodo a borrar.
	else
		x = y->der;
		
	//Esta condicion se cumple si 'y' no es una hoja del árbol.
	if (x != NULL)
		x->padre = y->padre; //Conectamos a 'x' con el padre de 'y'

	if (y->padre == NULL) // Si el nodo 'y' a extraer es la raiz
		arb->raiz = x;     // hacemos que su hijo sea la nueva raiz.
	else
		if (y == y->padre->izq) // Si no es así conectamos al padre de 'y'
			y->padre->izq = x;   // con su hijo 'x'
		else
			y->padre->der = x;
			
	// Si 'y' es diferente de 'z', que implica que 'z' tiene dos hijos
	// copiamos el contenido de 'y' en 'z',
	if (y != z)
	{
		strncpy (z->vertice, y->vertice, MAX_VERT_NAME-1);
		z->idx = y->idx;
	}	
	arb->numNodos--;
	arb->numNiveles = cuentaNiveles(arb);
		
	// Regresamos 'y', que es el apuntador al nodo que desconectamos
	// del árbol.
	return y;
}

void eliminaArbolCandida (arbolBinGrafo *arb)
{
	nodoGrafoA *x;
	
	while(arb->raiz != NULL)
	{
		x = borraNodoGrafoA(arb, arb->raiz);
		liberaNodoGrafoA(x);
	}
}

void __eliminaArbol(nodoGrafoA *r)
{
	if (r)
	{
		__eliminaArbol(r->izq);
		__eliminaArbol(r->der);
		liberaNodoGrafoA(r);
	}
}

void eliminaArbol(arbolBinGrafo *arb)
{
	__eliminaArbol(arb->raiz);
	arb->numNodos = arb->numNiveles = 0;
	arb->raiz = NULL;
}

void liberaBasuraGrafoA()
{
	nodoGrafoA *apu;
	
	while (basuraGrafoA)
	{
		apu = basuraGrafoA;
		basuraGrafoA = basuraGrafoA->der;
		free(apu);
	}
}

