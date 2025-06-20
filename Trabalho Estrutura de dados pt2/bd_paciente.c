#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "bd_paciente.h"

#define MAX_PACIENTES 100
#define TAMANHO_PAGINA 10
#define MAX_CPF_LEN 15
#define MAX_NOME_LEN 100
#define MAX_DATA_LEN 11

struct queue
{
   BDPaciente *front; // Pointer to the front of the queue.
   BDPaciente *rear;
   int total_pacientes;  // Pointer to the rear of the queue.
};
struct paciente { //estrutura para cada paciente
    int id;
    char cpf[MAX_CPF_LEN];
    char nome[MAX_NOME_LEN];
    int idade;
    char data_cadastro[MAX_DATA_LEN];
};

struct bdpaciente {
    Paciente pacientes[MAX_PACIENTES];
    BDPaciente *next;
};

Queue *q_create()
{
   Queue *q = (Queue *)malloc(sizeof(Queue)); // Allocate memory for the queue structure.
   q->front = q->rear = NULL;
   printf("Base de dados criada.\n");                // Initialize the front and rear pointers to NULL, indicating an empty queue.
   return q;
}
int q_is_empty(Queue *bd)
{
   return bd->front == NULL;
}
void *inserir_na_fila(Queue *bd, Paciente paciente){

    BDPaciente *node = (BDPaciente*)malloc(sizeof(BDPaciente));
    node->pacientes[MAX_PACIENTES] = paciente;
    node->next = NULL;
    if (q_is_empty(bd)){
        bd->front = node;
    }else{
        bd->rear->next = node;
    }
    bd->rear = node;
}
Paciente remover_da_fila(Queue *bd)
{
   assert(!q_is_empty(bd));

   Paciente *v = bd->front->pacientes;
   BDPaciente *p = bd->front; // Store for removal

   if (bd->front != bd->rear)
      bd->front = bd->front->next;
   else
      bd->front = bd->rear = NULL;

   free(p);
   return *v;
}
void q_free(Queue *bd)
{
   BDPaciente *p = bd->front;
   while (p != NULL)
   {
      BDPaciente *t = p->next; // Store a reference to the next node.
      free(p);                // Free the memory allocated for the current node.
      p = t;                  // Move to the next node.
   }
   free(bd); // Free the memory allocated for the queue structure itself.
}

void excluir_espaco_branco(char *s) { //remover espa�os em branco no final da string
    int i = strlen(s) - 1;
    while (i >= 0 && isspace((unsigned char)s[i])) {
        s[i] = '\0';
        i--;
    }
}

int bd_carregar_csv(Queue* bd, const char* filename) { //carregar pacientes a partir de um arquivo csv
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro: Nao foi possivel abrir o arquivo '%s'.\n", filename);
        return 1;
    }

    char line[256];
    int first_line = 1;

    bd->total_pacientes = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (first_line) {
            first_line = 0;
        }

        excluir_espaco_branco(line);

        if (strlen(line) == 0) {
            continue;
        }

        if (bd->total_pacientes >= MAX_PACIENTES) {
            fprintf(stderr, "Aviso: Limite maximo de pacientes atingido (%d). Ignorando registros restantes.\n", MAX_PACIENTES);
            break;
        }

        Paciente *p; //leitura e separa��o dos campos do csv
        char *token = strtok(line, ",");
        if (token) 
            p->id = atoi(token);

        token = strtok(NULL, ",");
        if (token) {
            strncpy(p->cpf, token, MAX_CPF_LEN - 1);
            p->cpf[MAX_CPF_LEN - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token) {
            strncpy(p->nome, token, MAX_NOME_LEN - 1);
            p->nome[MAX_NOME_LEN - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token) p->idade = atoi(token);

        token = strtok(NULL, ",");
        if (token) {
            strncpy(p->data_cadastro, token, MAX_DATA_LEN - 1);
            p->data_cadastro[MAX_DATA_LEN - 1] = '\0';
        }

        bd->front->pacientes[bd->total_pacientes++] = *p;
    }

    fclose(file);
    printf("Dados carregados de '%s'. Total de pacientes: %d\n", filename, bd->total_pacientes);
    return 0;
}

void imprimir_cabecalho() { //exibir o cabe�alho da tabela de pacientes
    printf("\n");
    printf("%-4s %-15s %-30s %-5s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
    printf("---- --------------- ------------------------------ ----- ------------\n");
}

void bd_consultar_paciente(Queue* bd) { //consulta do paciente por nome ou cpf
    if (bd->total_pacientes == 0) {
        printf("Nenhum paciente cadastrado para consulta.\n");
        return;
    }

    int escolha_modo;
    char termo_busca[MAX_NOME_LEN];
    int encontrados = 0;

    while (1) { //loop at� a op��o inserida ser v�lida
        printf("[Sistema]\nEscolha o modo de consulta:\n");
        printf("1 - Por nome\n");
        printf("2 - Por CPF\n");
        printf("3 - Retornar ao menu principal\n");
        printf("[Usuario]");
        scanf("%d", &escolha_modo);
        getchar();

        if (escolha_modo == 3) return;

        if (escolha_modo == 1 || escolha_modo == 2) {
            printf("[Sistema] Digite o termo: ");
            fgets(termo_busca, sizeof(termo_busca), stdin);
            excluir_espaco_branco(termo_busca);
            break;
        } else {
            printf("Opcao invalida. Por favor, escolha 1, 2 ou 3.\n");
        }
    }

    imprimir_cabecalho();

    for (BDPaciente *p = bd->front; p != NULL; p = p->next) { //busca pelos poss�veis pacientes com o que foi digitado pelo usu�rio
        int encontra = 0;
        if (escolha_modo == 1 && strstr(p->pacientes->nome, termo_busca)) { //utiliza��o de strstr() para encontrar primeira ocorr�ncia de uma substring na string principal
            encontra = 1;
        } else if (escolha_modo == 2 && strstr(p->pacientes->cpf, termo_busca)) {
            encontra = 1;
        }

        if (encontra) {
            paciente_imprimir(*p->pacientes);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum paciente encontrado com o termo '%s'.\n", termo_busca);
    } else {
        printf("\nTotal de pacientes encontrados: %d\n", encontrados);
    }
}

void bd_imprimir_lista_pacientes(Queue* bd) { //imprimir todos pacientes
    if (bd->total_pacientes == 0) {
        printf("Nenhum paciente cadastrado para imprimir.\n");
        return;
    }

    printf("\nImprimindo lista de pacientes...\n");
    imprimir_cabecalho();

	for (BDPaciente *p = bd->front; p != NULL; p = p->next) {
        paciente_imprimir(*p->pacientes);
		int a = 0;
        if ((a + 1) % TAMANHO_PAGINA == 0 && (a + 1) < bd->total_pacientes) { //pagina��o
            printf("\nPressione ENTER para ver a proxima pagina...\n");
            while (getchar() != '\n');
        }
        a += 1;
    }

    printf("\nFim da lista de pacientes.\n");
}

void paciente_imprimir(Paciente p) { //imprimir �nico paciente
    printf("%-4d %-15s %-30s %-5d %-12s\n",
           p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
}

void bd_inserir_paciente(Queue* bd){
    char cpf[25];
    char nome[50];
    int idade;
    char data_cadastro[20];
    printf("Para inserir um novo registro, digite os valores para os campos CPF (apenas dígitos), Nome, Idade e Data_Cadastro(precione enter a cada informação escrita):\n");

    scanf("%s", &cpf[25]);
    scanf("%s", &nome[50]);
    scanf("%d", &idade);
    scanf("%s", &data_cadastro[20]);

    printf("Confirma a inserção do registro abaixo? (S/N)\n");
    imprimir_cabecalho();
    printf("%-4d %-15s %-30s %-5d %-12s\n", bd->total_pacientes, cpf, nome, idade, data_cadastro);
}
