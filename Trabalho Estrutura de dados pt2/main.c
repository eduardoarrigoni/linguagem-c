#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"
#include <ctype.h>

int main() {
    char filename[100];
    printf("Diga o nome do arquivo para que possamos carrega-lo: "); //nome do arquivo csv que o usuario quer carregar
    scanf("%99s", filename);

    Queue *bd = q_create(); //criar base de dados de pacientes
    if (bd_carregar_csv(bd, filename) == 1) {
        return 0;
    }

    char opcao;
    while (tolower(opcao) != 'q') { //menu principal
        printf("\n--- Sistema de Pacientes ---\n");
        printf("1. Inserir paciente\n");
        printf("2. Consultar paciente\n");
        printf("3. Atualizar paciente\n");
        printf("4. Remover paciente\n");
        printf("5. Imprimir todos os pacientes\n");
        printf("Q. Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);

        if (opcao == '1') { // executa de acordo com opcao escolhida

            bd_inserir_paciente(bd);
            
        }else if (opcao == '2'){

            bd_consultar_paciente(bd);

        }else if (opcao == '3'){

            bd_atualizar_paciente(bd);

        }else if (opcao == '4'){

            bd_remover_paciente(bd);

        }else if (opcao == '5'){

            bd_imprimir_lista_pacientes(bd);

        }else if (tolower(opcao) == 'q'){
            printf("Saindo...\n");
        }
    }

    q_free(bd); //liberar memoria base de dados
    return 0;
}
