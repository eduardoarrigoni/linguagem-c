#include <stdio.h>

#define MAX 3

int busca(float M[MAX][MAX], int n_lin, int n_col, float v, int *lin, int *col){

    for (int i = 0; i < MAX; i++){

        for (int j = 0; j < MAX; j++){

            if (v == M[i][j]){

                *lin = i;
                *col = j;
                return 0;
            }
        }
    }

    return -1;
}

int main(){

    int n_lin, n_col;
    float v = 0;
    int lin, col;
    float M[MAX][MAX] = {{1, 1, 1}, {0, 2, 2}, {0, 1, 1}};
    
    busca(M, n_lin, n_col, v, &lin, &col);

    printf("lin: %d col: %d", lin, col);

    return 0;
}