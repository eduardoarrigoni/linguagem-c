#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analise_sintatica_pilha.h"

int main() {
    char filename[100];
    printf("Diga o nome do arquivo para que possamos carrega-lo: "); 
    scanf("%s", filename);

    Stack* s = s_create();

    if (procurar_sintaxe(filename, s) == 1) {
        return 0;
    }


    return 0;
}