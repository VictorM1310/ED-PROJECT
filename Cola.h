#ifndef __COLAINT__
#define __COLAINT__

typedef struct 
{
	int *Cola;
	unsigned int H, T, tama;
} ColaI;

int iniColaI(ColaI *c, unsigned int n);
void liberaColaI(ColaI *c);
int mete(ColaI *c, int val);
int saca(ColaI *c, int *val);
char vacia(ColaI *c);


#endif
