#include <stdio.h>
#include <stdlib.h>
#define n 3

void jogada(int humano, int *num_vitoria_humano, int *num_vitoria_computador, int *num_empate){

    int computador;

    computador = rand() % 4;
    
    if (humano == computador){

        *num_empate += 1;
        printf("Empate\n");

    }else if((humano == 0 && computador == 2) || (humano == 1 && (computador == 0 || computador == 3)) || (humano == 2 && computador == 1)){

        *num_vitoria_humano += 1;
        printf("Humano vence\n");

    }else{

        *num_vitoria_computador += 1;
        printf("Computador vence\n");

    }
}
int main(){

    int num_vitoria_humano, num_vitoria_computador, num_empate;
    int humano;
    
    num_empate = num_vitoria_computador = 0;

    for (int i = 0; i<=n; ++i){

        printf("Escolha uma das opcoes: \n0 - pedra\n1 - papel\n2 - tesoura\n");
        scanf("%d", &humano);

        if (humano > 2){

            return 1;
        }
        jogada(humano, &num_vitoria_humano, &num_vitoria_computador, &num_empate);

    }
    printf("Número de vitórias do humano: %d\n", num_vitoria_humano);
    printf("Número de vitórias do computador: %d\n", num_vitoria_computador);
    printf("Número de empate: %d", num_empate);
    
    return 0;
}
