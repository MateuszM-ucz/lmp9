#include "gauss.h"
#include <math.h>
#include <stdio.h>
#include "mat_io.h"

void swap(double* a, double* b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    double eps = 0.000000001;
    int n = mat->r;

    for(int i=0; i<n; i++){
        //wybór elementu głównego
        double minVal = fabs(mat->data[i][i]);
        int pozycja = i;
        for(int j = i + 1; j < n; j++){
            double val = fabs(mat->data[j][i]);
            if(val > minVal){
                minVal = val;
                pozycja = j;
            }
        }

        //zamiana wierszy
        if(pozycja != i){
            for(int k = 0; k < n; k++){
                swap(&mat->data[pozycja][k], &mat->data[i][k]);
            }
            swap(&b->data[pozycja][0], &b->data[i][0]);
        }

        //sprawdzanie czy na przekątnej są zera
        if(fabs(mat->data[i][i]) < eps){
            fprintf(stderr, "Macierz jest osobliwa (dzielenie przez zero w wierszu %d)\n", i);
            return 1;
        }

        //schodkowanie
        for(int j = i + 1; j < n; j++){
            double factor = mat->data[j][i]/mat->data[i][i];
            for(int k = i; k < n; k++){
                mat->data[j][k] -= factor*mat->data[i][k];
            }
            b->data[j][0] -= factor*b->data[i][0];
        }
    }
    return 0;
}
