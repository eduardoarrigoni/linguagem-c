#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"

int main(){

    char* filename;
    printf("Diga o nome do arquivo para que possamos carrega-lo: ");
    scanf("%s", filename);

    BDPaciente *bd = bd_criar();

    if (bd_carregar_csv(bd, filename) == 1){

        return 0;

    }
    
    int opcao;
    
    while (opcao != 6){

        printf("\n--- Sistema de Pacientes ---\n");
        printf("1. Inserir paciente\n");
        printf("2. Consultar paciente\n");
        printf("3. Atualizar paciente\n");
        printf("4. Remover paciente\n");
        printf("5. Imprimir todos os pacientes\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 2: 
                bd_consultar_paciente(bd); 
                
                break;
            
            case 5: 
                bd_imprimir_lista_pacientes(bd); break;

            case 6: 
                printf("Saindo...\n"); break;

            default: 
                printf("Opção em manutenção ou inválida.\n");
        }


    }

    return 0;
}