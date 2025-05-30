#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para tolower, se for implementar busca case-insensitive
#include "bd_paciente.h"

#define MAX_PACIENTES 100 // Tamanho máximo do vetor estático de pacientes
#define PAGE_SIZE 10
#define MAX_CPF_LEN 15    // Ex: "123.456.789-00\0"
#define MAX_NOME_LEN 100
#define MAX_DATA_LEN 11 

struct paciente
{
    int id;
    char cpf[MAX_CPF_LEN];
    char nome[MAX_NOME_LEN];
    int idade;
    char data_cadastro[MAX_DATA_LEN];
};
struct bdpaciente
{
    Paciente pacientes[MAX_PACIENTES];
    int total_pacientes;
};

/**
 * @brief Aloca e inicializa uma nova estrutura BDPaciente.
 * @return Um ponteiro para a estrutura BDPaciente alocada, ou NULL em caso de falha.
 */
BDPaciente* bd_criar() {
    BDPaciente* bd = (BDPaciente*) malloc(sizeof(BDPaciente));
    if (bd == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para BDPaciente.\n");
        return NULL;
    }
    bd->total_pacientes = 0; // Inicializa o contador de pacientes
    return bd;
}


/**
 * @brief Libera a memória alocada para a estrutura BDPaciente.
 * @param bd O ponteiro para a estrutura BDPaciente a ser destruída.
 */
void bd_destruir(BDPaciente* bd) {
    if (bd != NULL) {
        free(bd);
    }
}


/**
 * @brief Remove espaços em branco (incluindo quebras de linha) do final de uma string.
 * @param s A string a ser 'trimada'.
 */
static void trim_trailing_whitespace(char *s) {
    int i = strlen(s) - 1;
    while (i >= 0 && isspace((unsigned char)s[i])) {
        s[i] = '\0';
        i--;
    }
}


/**
 * @brief Carrega os dados dos pacientes de um arquivo CSV para a memória.
 * @param bd O ponteiro para a estrutura BDPaciente onde os dados serão carregados.
 * @param filename O nome do arquivo CSV a ser lido.
 * @return 0 em caso de sucesso, -1 em caso de falha (ex: arquivo não encontrado).
 */
int bd_carregar_csv(BDPaciente* bd, const char* filename) {
    
    FILE* file = fopen(filename, "r");
    
    if (file == NULL) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo '%s'.\n", filename);
        return 1;
    }
    
    char line[256]; // Buffer para ler cada linha do CSV
    int first_line = 1; // Flag para pular o cabeçalho
    
    
    bd->total_pacientes = 0; // Reinicia o contador de pacientes
    
    
    while (fgets(line, sizeof(line), file) != NULL) {
        if (first_line) {
            first_line = 0; // Pula a linha do cabeçalho    
        }

        // Remove a quebra de linha do final da string
        trim_trailing_whitespace(line);

        if (strlen(line) == 0) { // Pula linhas vazias
        
        }

        if (bd->total_pacientes >= MAX_PACIENTES) {
            fprintf(stderr, "Aviso: Limite máximo de pacientes atingido (%d). Ignorando registros restantes.\n", MAX_PACIENTES);
            break;
        }


        Paciente p;
        char *token;
        char *rest = line; // Usar uma cópia para strtok_r ou strtok seguro


        // ID
        token = strtok(rest, ",");
        if (token){
            p.id = atoi(token);
        }
        

        // CPF
        token = strtok(rest, ",");
        if (token){

            strncpy(p.cpf, token, MAX_CPF_LEN - 1); 
            p.cpf[MAX_CPF_LEN - 1] = '\0'; 
        } 
        

        // Nome
        token = strtok(rest, ",");
        if (token){
        
            strncpy(p.nome, token, MAX_NOME_LEN - 1); p.nome[MAX_NOME_LEN - 1] = '\0'; 
        } 


        // Idade
        token = strtok(rest, ",");
        if (token) {

            p.idade = atoi(token); 
        }


        // Data_Cadastro
        token = strtok(rest, ",");
        if (token) {
            strncpy(p.data_cadastro, token, MAX_DATA_LEN - 1); p.data_cadastro[MAX_DATA_LEN - 1] = '\0'; 

        }

        bd->pacientes[bd->total_pacientes++] = p;
    }


    fclose(file);
    printf("Dados carregados de '%s'. Total de pacientes: %d\n", filename, bd->total_pacientes);
    return 0;
}


/**
 * @brief Imprime o cabeçalho da tabela de pacientes.
 */
static void imprimir_cabecalho() {
    printf("\n");
    printf("%-4s %-15s %-30s %-5s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
    printf("---- --------------- ------------------------------ ----- ------------\n");
}


/**
 * @brief Permite ao usuário consultar pacientes por nome ou CPF (busca por prefixo).
 * @param bd O ponteiro para a estrutura BDPaciente.
 */
void bd_consultar_paciente(BDPaciente* bd) {
    if (bd->total_pacientes == 0) {
        printf("Nenhum paciente cadastrado para consulta.\n");
        return;
    }


    int escolha_modo;
    char termo_busca[MAX_NOME_LEN]; // Suficiente para nome ou CPF
    int encontrados = 0;


    while (1) {
        printf("[Sistema]");
        printf("\nEscolha o modo de consulta:\n");
        printf("1 - Por nome\n");
        printf("2 - Por CPF\n");
        printf("3 - Retornar ao menu principal\n");
       
        printf("[Usuário]");
        scanf("%d", &escolha_modo);

        if (escolha_modo == 3) {
            return; // Retorna ao menu principal
        }

        if (escolha_modo == 1) {

            printf("[Sistema]");
            printf("Digite o nome: ");

            fgets(termo_busca, sizeof(termo_busca), stdin);
            trim_trailing_whitespace(termo_busca);

            break;
        } else if (escolha_modo == 2) {
            printf("[Sistema]");
            printf("Digite o CPF: ");

            fgets(termo_busca, sizeof(termo_busca), stdin);
            trim_trailing_whitespace(termo_busca);

            break;
        } else {
            printf("Opção inválida. Por favor, escolha 1, 2 ou 3.\n");
        }
    }


    imprimir_cabecalho();


    for (int i = 0; i < bd->total_pacientes; i++) {
        int match = 0;
        if (escolha_modo == 1) { // Busca por nome
            // strstr busca a primeira ocorrência de termo_busca em bd->pacientes[i].nome
            if (strstr(bd->pacientes[i].nome, termo_busca) != NULL) {
                match = 1;
            }
        } else if (escolha_modo == 2) { // Busca por CPF
            if (strstr(bd->pacientes[i].cpf, termo_busca) != NULL) {
                match = 1;
            }
        }


        if (match) {
    
            printf("[Sistema]");
            paciente_imprimir(bd->pacientes[i]);
            encontrados++;
        }
    }


    if (encontrados == 0) {
        printf("Nenhum paciente encontrado com o termo '%s'.\n", termo_busca);
    } else {
        printf("\nTotal de pacientes encontrados: %d\n", encontrados);
    }
}


/**
 * @brief Imprime a lista completa de pacientes armazenados no sistema, com paginação.
 * @param bd O ponteiro para a estrutura BDPaciente.
 */
void bd_imprimir_lista_pacientes(BDPaciente* bd) {
    if (bd->total_pacientes == 0) {
        printf("Nenhum paciente cadastrado para imprimir.\n");
        return;
    }


    printf("\nImprimindo lista de pacientes...\n");
    imprimir_cabecalho();


    for (int i = 0; i < bd->total_pacientes; i++) {
        paciente_imprimir(bd->pacientes[i]);


        // Implementa paginação
        if ((i + 1) % PAGE_SIZE == 0 && (i + 1) < bd->total_pacientes) {
            printf("\nPressione ENTER para ver a próxima página...");
            while (getchar() != '\n'); // Espera por ENTER
        }
    }
    printf("\nFim da lista de pacientes.\n");
}

void paciente_imprimir(Paciente p) {
    printf("%-4d %-15s %-30s %-5d %-12s\n",
           p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
}
