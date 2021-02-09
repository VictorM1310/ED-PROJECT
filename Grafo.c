#include <stdlib.h>
#include <string.h>
#include "Grafo.h"
#include "Cola.h"

void imprimeMatrizAdyacencia(matAdyacencia *M)
{
	int i, j;
	
	printf("\n");
	for (i=0;i<M->nV;++i)
	{
		for (j=0;j<=i;++j)
			if (M->Tabla[i][j])
				printf("1");
			else
				printf("0");
		printf("\n");
	}
	printf("\n");
}
void initGrafo(Grafo *G)
{
	initArbolBinGrafo(&(G->TV), VERTICE);
	initArbolBinGrafo(&(G->TI), INDICE);
	initMatAdyacencia(&(G->M));
}

void initMatAdyacencia(matAdyacencia *M)
{
	M->Tabla = NULL;
	M->nV = M->nA = 0;
}

void agregaRenglon(matAdyacencia *M)
{
	if (M->nV == 0)
	{
		M->Tabla = malloc(1 * sizeof(char *));
		M->Tabla[0] = malloc(1 * sizeof(char));
	}
	else
	{
		M->Tabla = realloc(M->Tabla, sizeof(char *) * (M->nV + 1));
		M->Tabla[M->nV] = malloc((M->nV + 1) * sizeof(char));
		memset (M->Tabla[M->nV], 0, (M->nV + 1) * sizeof(char));
	}
	M->nV++;
}

int agregaVertice(Grafo *G, char *v)
{
	nodoGrafoA *n;
	
	// Validamos que no exista un vertice con el identificador
	// v en el grafo.
	if (buscaV(&(G->TV), v) == NULL)
	{
		agregaRenglon(&(G->M));
		n = creaNodoGrafoA(v, G->M.nV - 1);
		inserta (&(G->TV), n);

		n = creaNodoGrafoA(v, G->M.nV - 1);
		inserta (&(G->TI), n);
		return 0;
	}
	return -1;
}

char existeVertice(Grafo *G, char *v)
{
		if (buscaV(&(G->TV), v) == NULL)
			return 0;
		return 1;
}

int eliminaVertice(Grafo *G, char *v)
{
	nodoGrafoA *n;
	unsigned int i, j;
	
	
	n = buscaV(&(G->TV), v);
	if (n == NULL)
		return -1;
	
	//Decrementamos en numero de aristas que se van a perder
	//al desconectar al vertice.
	for (i = n->idx; i < (G->M).nV; ++i)
		if ((G->M).Tabla[i][n->idx] != 0)
			(G->M).nA--;
	for (i = 0; i < n->idx; ++i)
		if ((G->M).Tabla[n->idx][i] != 0)
			(G->M).nA--;
		
	//Eliminamos el renglon y columna n->idx de la tabla.
	for (i = n->idx + 1; i < (G->M).nV; ++i)
	{
		//Recorriendo ala izq. columnas mayores que n->idx
		for (j = n->idx + 1; j <= i; ++j)
			(G->M).Tabla[i][j-1] = (G->M).Tabla[i][j];
		//Cambiamos tamano de renglones.
		(G->M).Tabla[i] = realloc((G->M).Tabla[i], i * sizeof(char)); 
	}
	
	free((G->M).Tabla[n->idx]);
	for (i = n->idx + 1; i < (G->M).nV; ++i)
		(G->M).Tabla[i-1]=(G->M).Tabla[i];
		
	(G->M).nV--;
	(G->M).Tabla = realloc((G->M).Tabla, (G->M).nV * sizeof(char *));
	
	//Ajustamos indices a nodos mayores a n->idx
	decrementaIndiceV(&(G->TV), n->idx);
	decrementaIndiceI(&(G->TI), n->idx);
	
	//Eliminamos el nodo n del árbol
	n = borraNodoGrafoA(&(G->TV), n);
	liberaNodoGrafoA(n);
	
	return 0;
}

int buscaCeldaMatriz(Grafo *G, char *v1, char *v2, unsigned int *idx1, unsigned int *idx2)
{
	nodoGrafoA *n1, *n2;
	 
	 //Buscamos los indices de los vertices v1 y v2
	n1 = buscaV(&(G->TV), v1);
	if (n1 == NULL)
		return -1;
	n2 = buscaV(&(G->TV), v2);
	if (n2 == NULL)
		return -1;
	
	//Copiamos 'valor' a la celda de la tabla correspondiente.	
	if (n1->idx > n2->idx)
	{
		*idx1 = n1->idx;
		*idx2 = n2->idx;
	}
	else
	{
		*idx1 = n2->idx;
		*idx2 = n1->idx;
	}
	return 0;
}

int modificaArista(Grafo *G, char *v1, char *v2, char valor)
{
	unsigned int idx1, idx2;

	if (buscaCeldaMatriz(G, v1, v2, &idx1, &idx2) < 0)
		return -1;
	 
	// Modificamos la variable que contien número de Aristas en 
	// el grafo.
	if ((G->M).Tabla[idx1][idx2] == 0 && valor != 0)
		(G->M).nA++;
	else
		if ((G->M).Tabla[idx1][idx2] != 0 && valor == 0)
			(G->M).nA--;
		
	//asignamos 'valor' a la celda correspondiente.
	(G->M).Tabla[idx1][idx2] = valor;
	
	return 0;
}

int agregaArista(Grafo *G, char *v1, char *v2)
{
	return modificaArista(G, v1, v2, 1);
}

int eliminaArista(Grafo *G, char *v1, char *v2)
{
	return modificaArista(G, v1, v2, 0);
}

char existeArista(Grafo *G, char *v1, char *v2)
{

	unsigned int idx1, idx2;

	if (buscaCeldaMatriz(G, v1, v2, &idx1, &idx2) < 0)
		return -1; 
	
	return (G->M).Tabla[idx1][idx2];
}
	
void imprimeGrafo (Grafo *G)
{
	unsigned int i, j;
	
	printf("\nEl grafo tiene %d vertices y %d aristas.\n\n",\
	 (G->M).nV, (G->M).nA);
	 
	 printf("\nVertices: {");
	 inorderV(&(G->TV));
	 printf("}\n\n");
	 
	 printf("\nAristas: {");
	 for (i=0;i<(G->M).nV;++i)
		for (j=0;j <= i;++j)
			if ((G->M).Tabla[i][j] != 0)
			{
				nodoGrafoA *n1, *n2;
			
				n1 = buscaI(&(G->TI), i);
				if (n1 == NULL)
					continue;
				n2 = buscaI(&(G->TI), j);
				if (n2 == NULL)
					continue;
				printf("(%s, %s) ", n1->vertice, n2->vertice);
		}
	printf ("}\n\n");
}

void BFS(Grafo *G, char *x, BFS_ElemTabla **T)
{
	if(*T != NULL)
			return;
	*T = (BFS_ElemTabla *)calloc( G->M.nV,  sizeof (BFS_ElemTabla));
	if (*T != NULL)
	{
		//Inicializamos la tabla.
		unsigned int i;
		nodoGrafoA *n;
		
		
		
		n = buscaV(&(G->TV), x);
		if (n != NULL)
		{
			//Indice al nodo desde donde se iniciara la busqueda.
			int u, v;
			ColaI Q;
			
			iniColaI(&Q, (G->M).nV);
		
			v = n->idx;
		
			//Init Tabla.
			for (i = 0;i < (G->M).nV; ++i)
			{
				//Encontramos el nodo en la tabla asociada al indice i
				(*T)[i].C = BLANCO;
				(*T)[i].D = -1;//Equiv. a no es conocida la distancia aún
				(*T)[i].Padre = -1;//Equiv. a no conocemos el padre aún.
			}
			(*T)[v].C = GRIS;
			(*T)[v].D = 0;
			mete(&Q, v);
			
			// Mientras la cola no este vacia.
			while (vacia(&Q) != 0)
			{
				saca(&Q, &u);
				
				//Recorremos los adyacentes a u;
				//Primero recorremos todo el renglon con indice u
				for (v =0; v <= u; ++v)
					if ((G->M).Tabla[u][v] != 0)
					{
						if ((*T)[v].C == BLANCO)
						{
							(*T)[v].C = GRIS;
							(*T)[v].D = (*T)[u].D + 1;
							(*T)[v].Padre = u;
							mete(&Q, v);
						}
					}
				//Y continuamos con la columna u.
				for (v =u + 1; v < (G->M).nV; ++v)
					if ((G->M).Tabla[v][u] != 0)
					{
						if ((*T)[v].C == BLANCO)
						{
							(*T)[v].C = GRIS;
							(*T)[v].D = (*T)[u].D + 1;
							(*T)[v].Padre = u;
							mete(&Q, v);
						}
					}
				(*T)[u].C = NEGRO;
			}
			liberaColaI(&Q);
		}
	}
}

void imprimeRutaInv(Grafo *G, char *vertice, BFS_ElemTabla *T)
{
	nodoGrafoA *n1, *n2;
	
	n1 = buscaV(&(G->TV), vertice);
	if (n1 != NULL)
	{
		unsigned int idx;
		
		printf("La ruta para ir del nodo %s al origen es:\n\n", vertice);
		idx = n1->idx;
		printf ("%s -> ", n1->vertice);
		while (T[idx].Padre != -1)
		{
			n2 = buscaI(&(G->TI), T[idx].Padre);
			printf("%s ", n2->vertice);
			if (T[n2->idx].Padre != -1)
				printf(" -> ");
			idx = n2->idx; //pudo haber sido idx = T[idx].Padre
		}
		printf("\n\n");
	}
}

void __imprimeRuta(Grafo *G, unsigned int idx, BFS_ElemTabla *T)
{
	if (idx != -1)
	{
		nodoGrafoA *n;
		__imprimeRuta(G, T[idx].Padre, T);
	
		n = buscaI(&(G->TI), idx);
		if (T[idx].Padre == -1)
			printf("%s", n->vertice);
		else
			printf(" -> %s", n->vertice);
	}
}

void imprimeRuta(Grafo *G, char *vertice, BFS_ElemTabla *T)
{
	nodoGrafoA *n1;
	
	n1 = buscaV(&(G->TV), vertice);
	if (n1 != NULL)
	{
		__imprimeRuta(G, n1->idx, T);
		printf("\n\n");
   } 
}
