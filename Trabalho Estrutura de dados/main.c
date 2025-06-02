#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"

int main() {
    char filename[100];
    printf("Diga o nome do arquivo para que possamos carrega-lo: "); //nome do arquivo csv que o usu�rio quer carregar
    scanf("%99s", filename);

    BDPaciente *bd = bd_criar(); //criar base de dados de pacientes
    if (bd_carregar_csv(bd, filename) == 1) {
        return 0;
    }

    int opcao = 0;
    while (opcao != 6) { //menu principal
        printf("\n--- Sistema de Pacientes ---\n");
        printf("1. Inserir paciente\n");
        printf("2. Consultar paciente\n");
        printf("3. Atualizar paciente\n");
        printf("4. Remover paciente\n");
        printf("5. Imprimir todos os pacientes\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) { // executa de acordo com op��o escolhida
            case 2:
                bd_consultar_paciente(bd);
                break;
            case 5:
                bd_imprimir_lista_pacientes(bd);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao em manutencao ou invalida.\n");
        }
        
    }

    bd_free(bd); //liberar mem�ria base de dados
    return 0;
}
