#include <stdlib.h>
#include <Cola.h>

int iniColaI(ColaI *c, unsigned int n)
{
	c->H = c->T = 0;
	if (n) //Equivalente a n!=0
	{
		c->Cola = (int *)malloc((n + 1) * sizeof(int));
		if (c->Cola) //Equivalente a c->C != NULL
		{
			c->tama = n + 1;
			return 0;
		}
		c->tama = 0;
		return -1;
	}
	c->tama = 0;
	return 0;
}

void liberaColaI(ColaI *c)
{
	if (c->Cola) //Equivalente a c->Cola != NULL
	{
		free (c->Cola);
		c->Cola = NULL;
	}
	c->H = c->T = c->tama = 0;
}

int mete(ColaI *c, int val)
{
	if ((c->T + 1) % c->tama != c->H) //La cola no esta llena
	{
		c->Cola[c->T] = val;
		c->T = (c->T + 1) % c->tama;//incrementamos T modulo tama
		return 0;
	}
	return -1;
}

int saca(ColaI *c, int *val)
{
	if (c->H != c->T) //La cola no está vacia.
	{
		*val = c->Cola[c->H];
		c->H = (c->H + 1) % c->tama; //incrementamos H modulo tama
		return 0;
	}
	return -1;
}

char vacia(ColaI *c)
{
	
	if (c->H == c->T)
		return 0;
	else
		return 1;
}
