#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	
	int size = mat->c;
	if (mat->r != size || x->r != size || b->r != size || x->c != 1 || b->c != 1)
	{
		return 2;
	}

	for (int i = size - 1; i >= 0; i--)
	{
		double val = b->data[i][0];
		for (int j = size - 1; j > i; j--)
		{
			val -= mat->data[i][j] * x->data[j][0];
		}

		double div = mat->data[i][i];
		if (div == 0.0) { return 1; }

		x->data[i][0] = val / div;
	}
	return 0;
}


