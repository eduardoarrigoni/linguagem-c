#include <stdio.h>
void encontre_indices(char vetor[], int tamanho, char c) {

    printf("O caractere '%c' foi encontrado nos seguintes índices: ", c);

    for (int i = 0; i < tamanho; i++){
        
        if (vetor[i] == c){

            printf("\n%d", i);
        }
    }
}
int main(){
    char c;
    int n;

    printf("Digite o caractere a ser procurado (c): ");
    scanf(" %c", &c);

    printf("Digite o tamanho do vetor (n): ");
    scanf("%d", &n);

    char vetor[n];

    printf("Digite os caracteres do vetor (separados por espaço ou enter):\n");

    for (int i = 0; i < n; i++){

        scanf(" %c", &vetor[i]);
    }

    encontre_indices(vetor, n, c);

    return 0;
}
