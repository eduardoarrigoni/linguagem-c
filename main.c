#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analise_sintatica_pilha.h"

int main() {
    char filename[100];
    printf("Diga o nome do arquivo para que possamos carrega-lo: "); 
    scanf("%99s", filename);
    char* l;
    l = (char*)malloc(sizeof(char)*10);

    Stack* s = s_create();

    if (procurar_sintaxe(filename, s, l) == 1) {
        return 0;
    }


    return 0;
}