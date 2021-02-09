#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Grafo.h"
#include"RedSocial.h"

#define NVERTICES 1000
#define NARISTAS 34629
#define swap(x,y,z) {z=x;x=y;y=z;}

typedef struct
{
	int **B;
	unsigned int ren;
	unsigned int col;
	unsigned int tama;

} arregloInt2D;


int initArregloInt2D(arregloInt2D *aI, unsigned int r1, unsigned int c1);

void liberaArregloInt2D(arregloInt2D *aI);



int initArregloInt2D(arregloInt2D *aI, unsigned int r1, unsigned int c1)
{
	if (r1 && c1) //Validamos que r y c sean diferentes de 0
	{
		unsigned int i;

		aI->B = malloc(r1 * sizeof (int *));
		if (aI->B != NULL) //equivalente a aI->A
		{
			aI->B[0] = malloc(r1 * c1 * sizeof (int));
			if (aI->B[0] != NULL) //equivalente a aI->A[0]
				for (i = 1; i < r1; ++i)
					//aI->A[i] = &(aI->A[0][i * c]);//Aqui usamos el operador &
					aI->B[i] = aI->B[0] + i * c1;//Aqui usamos aritmetica de apuntadores.
			else
			{
				free(aI->B);
				aI->B = NULL;
				aI->ren = aI->col = aI->tama = 0;
				return -1;
			}
		}
		else
		{
			aI->ren = aI->col = aI->tama = 0;
			return -1;
		}
		aI->ren = r1;
		aI->col = c1;
		aI->tama = r1 * c1;
		return 0;
	}
	aI->ren = aI->col = aI->tama = 0;
	aI->B = NULL;
	return 0;
}


void liberaArregloInt2D(arregloInt2D *aI)
{
		if(aI->tama)
		{
			free(aI->B[0]);
			free(aI->B);
			aI->ren = aI->col = aI->tama = 0;
			aI->B = NULL;
		}
}


int contarVinculos(Grafo *G, int vertice);

int contarVinculos(Grafo *G, int vertice)
{
	int valencia = 0;
	
	for (int i=0; i<vertice; ++i)
	{	
		if (G->M.Tabla[vertice][i] == 1)
		++valencia;	
	}
	
	for (int i=0; i<(G->M.nV - (vertice + 1)); ++i  )
	{
		if (G->M.Tabla[vertice+1+i][vertice] == 1)
		++valencia;		
	}
	
	return valencia;
}









int main(int argc, char**argv)
{
	Grafo G;
	int i;
	BFS_ElemTabla *Tabla_BFS = NULL;
   	nodoGrafoA *n1, *n2;
	char *nomUsuarioO;
	char *nomUsuarioD;
	
	
	initGrafo (&G);
	
	//Tenemos que cargar los vertices al grafo
	for (i = 0; i < NVERTICES; ++i)
	{
		agregaVertice(&G, Identificadores[i]);
			//fprintf (stderr, "El vertice %s ya existe en el grafo\n", Identificadores[i]);
		//inorder (&(G.TV));
		//printf("\n____________________________________\n\n");
	}

	for(int i = 0; i < NARISTAS; i++)
	{
		agregaArista(&G,Identificadores[Relaciones[i][0]], Identificadores[Relaciones[i][1]]);
		//printf("Agregamos una arista entre los vertices \"%s\" y \"%s\".\n",Identificadores[Relaciones[i][0]], Identificadores[Relaciones[i][1]]);
	
	}
	
	
	
	//imprimeGrafo(&G);

	nomUsuarioO =  malloc(20 * sizeof(char));
	nomUsuarioD =  malloc(20 * sizeof(char));
    
	if (argc > 1) 
	{
		strncpy(nomUsuarioO, argv[1], 20);
		if (argc > 2)
			 strncpy(nomUsuarioD, argv[2], 20);
	}
	
   BFS(&G,nomUsuarioO, &Tabla_BFS);
   /*
   for (i=0;i<G.M.nV;++i)
      printf ("V:%02d, D:%02d, Padre:%02d\n", i, Tabla_BFS[i].D, Tabla_BFS[i].Padre);
   printf("\n");
   
   for (i=0;i<G.M.nV;++i)
   {
      n1  = buscaI(&(G.TI), i);
      n2  = buscaI(&(G.TI), Tabla_BFS[i].Padre);
   }
   */

   	printf("\n");
	printf("La ruta de %s a %s es: \n\n",nomUsuarioO,nomUsuarioD);

	imprimeRuta(&G, nomUsuarioD, Tabla_BFS);
	
	
	int r = NVERTICES;	
	int c = 2;
	
	
	
	arregloInt2D listaValencias;
	initArregloInt2D(&listaValencias, r, c );
	
	for (int i=0; i<NVERTICES; ++i)
	{
		listaValencias.B[i][0] = contarVinculos(&G, i);  //LLENAMOS UN ARREGLO CON INDICES CON LAS VALENCIAS DE LOS VERTICES
		listaValencias.B[i][1] = i;
	}
	
	
	  for (int i=0; i < NVERTICES - 1; i++)
     		 for (j= NVERTICES -1; j > i;j--)
        		 if (listaValencias.B[j][0] < listaValencias.B[j-1][0]) //ORDENAMOS LOS INDICES DE LAS VALENCIAS 
				swap(listaValencias.B[j][1], listaValencias.B[j-1][1], tmp);
	
	for (int i=0; i<NVERTICES; ++i)
	{
		
		printf("%d . %s tiene valencia %d", i, Identificadores[listaValencias.B[i][1]], listaValencias.B[listaValencias.B[i][1]][0]);
		//IMPRIMIMOS CON RESPECTO AL ORDEN DE LOS INDICES 
	}
	
	
	
	

   if (Tabla_BFS != NULL)
      free(Tabla_BFS);

	free(nomUsuarioD);
	free(nomUsuarioO);
	liberaArregloInt2D(&listaValencias);
	
	return 0;

	
}
