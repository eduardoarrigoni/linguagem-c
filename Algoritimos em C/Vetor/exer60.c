#include <stdio.h>

int main(){

    float valor;
    double vetor[100];
    int pos = 0;
    double soma = 0;
    double media = 0;

    printf("Diga um valor(insira um valor negativo para encerrar): ");
    scanf("%f", &valor);

    while (valor >= 0){

        vetor[pos] = valor;
        soma += valor;

        printf("Diga um valor(insira um valor negativo para encerrar): ");
        scanf("%f", &valor);
        
        pos += 1;
    }

    media = soma/pos;

    printf("Média dos valores: %lf\n", media);
    printf("Valores maiores que a média:");

    for (int i = 0; i < pos; i++){

        if (vetor[i] > media){

            printf("\n%lf", vetor[i]);
        }
    }




    return 0;
}