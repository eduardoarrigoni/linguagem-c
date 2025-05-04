#include <stdio.h>

int trajeto(int const m[5][5], int const vetor[6], int *distancia){

    for (int i = 1; i < 6; i++){

        *distancia += m[vetor[i-1]][vetor[i]];
        printf("%d ", *distancia);
    }

}

int main(){

    int m[5][5] = {{0, 10, 7, 15, 50}, {10, 0, 15, 8, 45}, {7, 15, 0, 20, 55}, {15, 8, 20, 0, 40}, {50, 45, 55, 40, 0}};
    int vetor[6];
    int distancia = 0;

    printf("Informe o circuito desejado: ");

    for (int i = 0; i < 6; i++){

        scanf(" %d", &vetor[i]);

    }
    
    trajeto(m, vetor, &distancia);

    printf("Distancia: %d km", distancia);

    return 0;
}