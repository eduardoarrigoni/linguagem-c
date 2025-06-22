#include <stdio.h>
#include <string.h>

void formatarCPF(const char *entrada, char *saida) {
    // Verifica se a string de entrada tem exatamente 11 dígitos
    if (strlen(entrada) > 12) {
        sprintf(saida, "CPF inválido");
        return;
    }

    // Formata a string no padrão XXX.XXX.XXX-XX
    sprintf(saida, "%.3s.%.3s.%.3s-%.2s",
            entrada, entrada + 3, entrada + 6, entrada + 9);
}

int main(){
    char cpf[25];
    char saida_cpf[25];

    scanf("%s", &cpf);

    formatarCPF(cpf, saida_cpf);
        
    printf("%s ", saida_cpf);

    return 0;
}

