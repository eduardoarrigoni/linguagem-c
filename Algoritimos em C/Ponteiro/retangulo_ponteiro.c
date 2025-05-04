#include <stdio.h>
#include <math.h>

void calc_info_retangulo(double comprimento, double largura, double *area, double *perimetro, double *diagonal){

    *area = comprimento*largura;
    *perimetro = (2*comprimento) + (2*largura);
    *diagonal = sqrt(pow(comprimento, 2) + pow(largura, 2));
}

int main(){

    double comprimento, largura, area, perimetro, diagonal;

    printf("Diga o comprimento do retangulo: ");
    scanf("%lf", &comprimento);

    printf("Diga a largura do retangulo: ");
    scanf("%lf", &largura);

    calc_info_retangulo(comprimento, largura, &area, &perimetro, &diagonal);

    printf("Area: %lf\nPerimetro: %lf\nDiagonal: %lf", area, perimetro, diagonal);

    return 0;
}
