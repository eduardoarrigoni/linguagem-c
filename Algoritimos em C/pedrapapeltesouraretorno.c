#include <stdio.h>
#include <stdlib.h>
#define n 3

void jogada(int humano, int *num_vitoria_humano, int *num_vitoria_computador, int *num_empate){

    int computador;

    computador = rand() % 3;
    printf("%d", computador);
    if (humano == computador){

        *num_empate += 1;

    }else if((humano == 0 && computador == 2) || (humano == 1 && computador == 0) || (humano == 2 && computador == 1)){

        *num_vitoria_humano += 1;
    }else{

        *num_vitoria_computador += 1;
    }
}
int main(){

    int num_vitoria_humano, num_vitoria_computador, num_empate;
    int humano;
    
    for (int i = 0; i<=n; ++i){

        printf("Escolha uma das opcoes: \n0 - pedra\n1 - papel\n2 - tesoura\n");
        scanf("%d", &humano);

        jogada(humano, &num_vitoria_humano, &num_vitoria_computador, &num_empate);

    }
    printf("empate: %d", num_empate);
    printf("humano: %d", num_vitoria_humano);
    printf("computador: %d", num_vitoria_computador);
    
    return 0;
}