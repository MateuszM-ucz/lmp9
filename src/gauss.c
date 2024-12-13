#include "gauss.h"
#include "mat_io.h"
/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    int i, j, k;
    int n = mat->r;

    for(i= 0; i<n; i++){ 			//szukanie najwiekszego elementu
        double m= fabs(mat->data[i][i]);
        int w= i;
        for(k= i+1; k<n; k++){
            if(fabs(mat->data[k][i]) > m){
		m= fabs(mat->data[k][i]);
                w= k;
            }
        }

        if(mat->data[w][i] == 0){		//sprawdzanie czy na przekatnej sa zera
            fprintf(stderr, "Macierz jest osobliwa (dzielenie przez zero w wierszu %d)\n", i);
            return 1;
        }

        if(w!=i){				//przenoszenie najwiekszzego elementu na przekatne	
            double *t= mat->data[i];
            mat->data[i]= mat->data[w];
            mat->data[w]= t;
            double tempVal= b->data[i][0];
            b->data[i][0]= b->data[w][0];
            b->data[w][0]= tempVal;
        }

        double pivot= mat->data[i][i];		//przez co mnozymy
        for(j=i; j<n; j++){
            mat->data[i][j] /= pivot;
        }
        b->data[i][0] /= pivot;
        for(k= i+1; k<n; k++){			//eliminacja kolumn ponizej przekatnej
            double factor= mat->data[k][i];
            for(j=i; j<n; j++){
                mat->data[k][j]-=factor*mat->data[i][j];
            }
            b->data[k][0]-=factor*b->data[i][0];
        }
    }
    return 0;
}


