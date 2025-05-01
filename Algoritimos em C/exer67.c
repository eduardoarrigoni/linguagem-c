#include <stdio.h>

int min(int v[], int n, int *idxmin){

    int menor_valor;
    menor_valor = v[0];

    for (int i = 0; i < n; i++){

        if (v[i] < menor_valor){

            menor_valor = v[i];
            *idxmin = i;

        }

    }
    return menor_valor;
}

int main(){

    int n;
    int menor;
    int idxmin;

    printf("Digite o tamanho do vetor (n): ");
    scanf("%d", &n);

    int vetor[n];

    printf("Digite os caracteres do vetor (separados por espaço ou enter):\n");

    for (int i = 0; i < n; i++){

        scanf(" %d", &vetor[i]);
    }

    menor = min(vetor, n, &idxmin);

    printf("Menor valor do vetor: %d\n", menor);
    printf("Indice correspondente: %d", idxmin);

    return 0;
}