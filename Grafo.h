#include <stdlib.h>
#include <stdio.h>
#include "arbolBinarioGrafo.h"

typedef enum {BLANCO, GRIS, NEGRO} BFS_Color;

typedef struct
{
	char **Tabla;//Matriz de Adyacencia
	unsigned int nV, nA;
} matAdyacencia;

typedef struct
{
	//Arbol que registra relacion de índices en función de nombres de vertices en la tabla
	arbolBinGrafo TV; 
	
	//Arbol que registra relacion de índices en funcion de nombres de vertices
	//de la tabla
	arbolBinGrafo TI; 
	
	//Matriz de Adyacencia.
	matAdyacencia M;
} Grafo;

typedef struct
{
		BFS_Color C;
		int D; 
		int Padre; //Indice al nodo Padre.
} BFS_ElemTabla;


void imprimeMatrizAdyacencia(matAdyacencia *M);

void imprimeGrafo (Grafo *G);

//Inicializa la estructura Grafo,
void initGrafo(Grafo *G);

//Inicializa una matriz de adyacencia.
void initMatAdyacencia(matAdyacencia *M);

//Agrega un renglo a la matriz de adyacencia.
void agregaRenglon(matAdyacencia *M);

//Agrega un vertice al grafo.
int agregaVertice(Grafo *G, char *v);

//Elimina un vértice del grafo.
int eliminaVertice(Grafo *G, char *v);

//Determina si existe un vertice v en el grafo.
//regresa 0 (falso), si no existe y 1 (verdadero) en caso contrario;
char existeVertice(Grafo *G, char *v);

//Encuentra los índices en la tabla que corresponden
//a los vertices v1 y v2
int buscaCeldaMatriz(Grafo *G, char *v1, char *v2, unsigned int *idx1, unsigned int *idx2);

//Modifica una celda de la matriz de adyacencia
int modificaArista(Grafo *G, char *v1, char *v2, char valor);

//Agrega un arista a nuestro grafo.
int agregaArista(Grafo *G, char *v1, char *v2);

//Elimina un arista a nuestro grafo.
int eliminaArista(Grafo *G, char *v1, char *v2);

// Nos regresa un valor indicando si existe o no una arista
// 0 -> si no existe
// diferente de 0 -> si sí existe.
char existeArista(Grafo *G, char *v1, char *v2);

void BFS(Grafo *G, char *x, BFS_ElemTabla **T);

void imprimeRutaInv(Grafo *G, char *vertice, BFS_ElemTabla *T);

void imprimeRuta(Grafo *G, char *vertice, BFS_ElemTabla *T);
