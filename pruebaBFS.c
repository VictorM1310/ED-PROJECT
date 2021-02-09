#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Grafo.h"
#include"RedSocial.h"

#define NVERTICES 1000
#define NARISTAS 34629

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

   if (Tabla_BFS != NULL)
      free(Tabla_BFS);

	return 0;

	free(nomUsuarioD);
	free(nomUsuarioO);
}
