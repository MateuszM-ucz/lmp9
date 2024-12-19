#include "gauss.h"
#include <math.h>
#include <stdio.h>
#include "mat_io.h"
/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    double eps = 0.000000001;
    int n = mat->r;

    for(int i=0; i<n; i++){
        //wybor elementu glownego
        double x = fabs(mat->data[i][i]);
        int p = i;
        for(int j=i+1; j<n; j++){
            if(fabs(mat->data[j][i]) > x){
                x = fabs(mat->data[j][i]);
                p = j;
            }
        }

        //zamiana wierszy
        if(p != i){
            double temp;
            for(int k=0; k<n; k++){
                temp = mat->data[p][k];
                mat->data[p][k] = mat->data[i][k];
                mat->data[i][k] = temp;
            }
            temp = b->data[p][0];
            b->data[p][0] = b->data[i][0];
            b->data[i][0] = temp;
        }

        //sprawdzanie czy na przekatnej sa zera
        if(fabs(mat->data[i][i]) < eps){
            fprintf(stderr, "Macierz jest osobliwa (dzielenie przez zero w wierszu %d)\n", i);
            return 1;
        }

        //schodkowanie
        for(int j=i+1; j<n; j++){
            double factor = mat->data[j][i]/mat->data[i][i];
            for(int k=i; k<n; k++){
                mat->data[j][k] -= factor*mat->data[i][k];
            }
            b->data[j][0] -= factor*b->data[i][0];
        }
    }
    return 0;
}
