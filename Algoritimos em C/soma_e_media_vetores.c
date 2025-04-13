#include <stdio.h>

int main(){

    int n;
    float sum;
    float media;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    float vetor[n];

    for (int i = 0; i < n; ++i){

        printf("\nValor %d: ", i);
        scanf("%f", &vetor[i]);

        sum += vetor[i];
        
    }

    media = sum/n;

    printf("\nSoma dos valores: %f", sum);
    printf("\nMédia dos valores: %f", media);

    return 0;
}