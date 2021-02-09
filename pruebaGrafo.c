#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<Grafo.h>

int main()
{
	Grafo G;
	char vertId[5][64]={"pato", "gato", "perro", "venado", "pato"};
	int i;
	
	initGrafo (&G);
	
	for (i = 0; i < 5; ++i)
	{
		if (agregaVertice (&G, vertId[i]))
			fprintf (stderr, "El vertice %s ya existe en el grafo\n", vertId[i]);
		inorder (&(G.TV));
		printf("\n____________________________________\n\n");
	}
	
	if (agregaArista(&G, "pato", "gato") == 0)
		printf ("Agregamos una arista entre los vertices \"pato\" y \"gato\".\n");
	
	if (agregaArista(&G, "pato", "perro") == 0)
		printf ("Agregamos una arista entre los vertices \"pato\" y \"perro\".\n");
		
	if (agregaArista(&G, "venado", "gato") == 0)
		printf ("Agregamos una arista entre los vertices \"venado\" y \"gato\".\n");
	
	if (agregaArista(&G, "perro", "venado") == 0)
		printf ("Agregamos una arista entre los vertices \"perro\" y \"venado\".\n");
	
	if (agregaArista(&G, "pato", "gato") == 0)
		printf ("Agregamos una arista entre los vertices \"pato\" y \"gato\".\n");
		
	imprimeGrafo(&G);
	
	if (eliminaArista(&G, "perro", "pato") == 0)
		printf ("Eliminamos una arista entre los vertices \"pato\" y \"perro\".\n");
	
	imprimeGrafo(&G);
	printf("\n**********************************\n\n");
	
	for (i = 0; i < 5; ++i)
	{
		nodoGrafoA *n = NULL;
		
		n = buscaV(&(G.TV), vertId[i]);
		
		if (n)
		{	
			printf ("\nEliminamos el vertice \"%s\" del grafo\n", vertId[i]);
			eliminaVertice(&G, vertId[i]);
			printf ("\nAhora el grafo luce así,\n");
			imprimeGrafo(&G);
			printf("\n____________________________________\n\n");
		}
		else
		{
			printf ("\nEl vertice \"%s\" no existe en el grafo\n", vertId[i]);
			printf("\n____________________________________\n\n");
		}
	}
	
	return 0;
}
