#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analise_sintatica_pilha.h"

int main() {
    char filename[100];
    printf("Diga o nome do arquivo para que possamos carrega-lo: "); //nome do arquivo csv que o usu�rio quer carregar
    scanf("%99s", filename);

    Stack* s = s_create();

    if (carregar_txt(filename, s) == 1) {
        return 0;
    }else{
        printf("Pilha formada\n");
    }

    






    return 0;
}