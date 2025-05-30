#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char* filename = "bancodedados.csv";

    FILE* file = fopen(filename, "r");

    char line[256];
    int first_line = 1;


    while (fgets(line, sizeof(line), file) != NULL) {
        if (first_line) {
            first_line = 0; // Pula a linha do cabeçalho
            
            printf("%d", first_line);
        }

        printf("linha\n");
    }

}
