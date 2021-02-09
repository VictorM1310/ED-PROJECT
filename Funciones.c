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
