#include <stdio.h>

int main(){

    int usuario1, usuario2;

    printf("Escolha uma das opcoes, Usuario 1: \n0 - pedra\n1 - papel\n2 - tesoura\n");
    scanf("%d", &usuario1);

    printf("Escolha uma das opcoes, Usuario 2: \n0 - pedra\n1 - papel\n2 - tesoura\n");
    scanf("%d", &usuario2);

    if (usuario1 == usuario2){

        printf("empate");

    }else if((usuario1 == 0 && usuario2 == 2) || (usuario1 == 1 && usuario2 == 0) || (usuario1 == 2 && usuario2 == 1)){

        printf("usuario 1 vence");
    }else{

        printf("usuario 2 vence");
    }

    return 0;
}