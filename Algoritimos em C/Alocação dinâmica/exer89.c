#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* interseccao(int *x1, int *x2, int n1, int n2, int *n3){

    bool validador = false;
    int pos = 0;
    *n3 = n1 + n2;
    int *x3 = (int *)malloc(*n3 * sizeof(int));

    *n3 = 0;
    for (int i = 0; i < n1; i++){

        for (int a = 0; a < n2; a++){

            if (x1[i] == x2[a]){

                validador = true;

            }
        }

        if (validador == true){

            x3[pos] = x1[i];
            *n3 += 1;
            pos += 1;
        }

        validador = false;
    }

    return x3;
}
int main(){

    int x1[5] = {1, 3, 5, 6, 7};
    int x2[5] = {1, 3, 4, 6, 8};
    int n1, n2;
    int n3;

    n1 = sizeof(x1)/sizeof(int);
    n2 = sizeof(x2)/sizeof(int);

    int *x3 = interseccao(x1, x2, n1, n2, &n3);

    for (int i = 0; i < n3; i++){

        printf("%d ", x3[i]);
    }

    printf("\n%d", n3);

    return 0;
}