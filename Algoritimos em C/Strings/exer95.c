#include <stdio.h>
#include <stdbool.h>

int main(){

    bool validador = true;
    int n1, n2;
    
    printf("Diga o tamanho da s1: ");
    scanf("%d", &n1);

    printf("Diga o tamanho da s2: ");
    scanf("%d", &n2);

    char s1[n1], s2[n2];

    printf("Digite os valores de s1(separados por espaço): ");
    for (int i = 0; i < n1; i++){
        scanf(" %c", &s1[i]);
    }

    printf("Digite os valores de s2(separados por espaço): ");
    for (int i = 0; i < n2; i++){
        scanf(" %c", &s2[i]);
    }

    for (int i = 0; i <= (n1 - n2); i++){
    
        for (int a = 0; a < n2; a++){

            if (s1[i+a] != s2[a]){

                validador = false;
            }
        }                                                                      
        
        if (validador){
            return 0;
        }
        validador = true;
    }

    return -1;
}