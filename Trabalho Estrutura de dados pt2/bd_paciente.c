#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "bd_paciente.h"

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
    Paciente pacientes;
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
void inserir_na_fila(Queue *bd, Paciente paciente){

    BDPaciente *node = (BDPaciente*)malloc(sizeof(BDPaciente));
    node->pacientes = paciente;
    node->next = NULL;
    if (q_is_empty(bd)){
        bd->front = node;
    }else{
        bd->rear->next = node;
    }
    bd->total_pacientes += 1;
    bd->rear = node;
}
Paciente remover_da_fila(Queue *bd){
   assert(!q_is_empty(bd));

   Paciente v = bd->front->pacientes;
   BDPaciente *p = bd->front; // Store for removal

   if (bd->front != bd->rear)
      bd->front = bd->front->next;
   else
      bd->front = bd->rear = NULL;

   free(p);
   return v;
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
        
        Paciente p; //leitura e separação dos campos do csv
        char *token = strtok(line, ",");
        if (token) p.id = atoi(token);
        
        token = strtok(NULL, ",");
        if (token) {
            strncpy(p.cpf, token, MAX_CPF_LEN - 1);
            p.cpf[MAX_CPF_LEN - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token) {
            strncpy(p.nome, token, MAX_NOME_LEN - 1);
            p.nome[MAX_NOME_LEN - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token) p.idade = atoi(token);

        token = strtok(NULL, ",");
        if (token) {
            strncpy(p.data_cadastro, token, MAX_DATA_LEN - 1);
            p.data_cadastro[MAX_DATA_LEN - 1] = '\0';
        }
        
        inserir_na_fila(bd, p);
        
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
        printf("[Usuario]\n");
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
        if (escolha_modo == 1 && search_prefix(p->pacientes.nome, termo_busca)) {
            encontra = 1;
        } 
         else if (escolha_modo == 2 && search_prefix(p->pacientes.cpf, termo_busca)) {
            encontra = 1;
        }

        if (encontra) {
            paciente_imprimir(p->pacientes);
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
        paciente_imprimir(p->pacientes);
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
void formatarCPF(const char *entrada, char *saida) {
    // Verifica se a string de entrada tem exatamente 11 dígitos
    if (strlen(entrada) != 11) {
        sprintf(saida, "CPF inválido");
        return;
    }

    // Formata a string no padrão XXX.XXX.XXX-XX
    sprintf(saida, "%.3s.%.3s.%.3s-%.2s",
            entrada, entrada + 3, entrada + 6, entrada + 9);
}
void bd_inserir_paciente(Queue* bd){

    char cpf[25];
    char nome[50];
    int idade;
    char data_cadastro[20];
    char escolha = 'n';
    char saida_cpf[15];

    printf("[Sistema]\nPara inserir um novo registro, digite os valores para os campos CPF (apenas dígitos), Nome, Idade e Data_Cadastro(precione enter a cada informação escrita):\n");
    while (escolha != 's'){
        scanf("%s", &cpf);
        scanf(" %s", &nome);
        scanf(" %d", &idade);
        scanf(" %s", &data_cadastro);

        printf("[Sistema]\nConfirma a inserção do registro abaixo? (S/N)\n");

        imprimir_cabecalho();
        printf("%-4d ", bd->total_pacientes);
        
        formatarCPF(cpf, saida_cpf);
        
        printf("%s ", saida_cpf);    
        printf(" %-30s %-5d %-12s\n", nome, idade, data_cadastro);
        
        scanf(" %c", &escolha);

        if (escolha != 's'){
            printf("[Sistema]\nOps, preencha novamente: \n");
        }
        
        
    }
    if(escolha == 's'){
        
        Paciente p;

        p.id = bd->total_pacientes;
        strncpy(p.cpf, saida_cpf, MAX_CPF_LEN - 1);
        p.cpf[MAX_CPF_LEN - 1] = '\0';
        
        strncpy(p.nome, nome, MAX_NOME_LEN - 1);
        p.nome[MAX_NOME_LEN - 1] = '\0';

        p.idade = idade;

        strncpy(p.data_cadastro, data_cadastro, MAX_DATA_LEN - 1);
        p.data_cadastro[MAX_DATA_LEN - 1] = '\0';

        inserir_na_fila(bd, p);
        
        printf("[Sistema]\nO registro foi inserido com sucesso.\n");
    }

}
void bd_atualizar_paciente(Queue* bd){
    int id;
    char cpf[25];
    char nome[50];
    int idade;
    char data_cadastro[20];

    bd_consultar_paciente(bd);

    printf("Digite o ID do registro a ser atualizado:\n");

    printf("[Usuario]\n");
    scanf("%d", &id);
    
    printf("[Sistema]\n");
    printf("Digite o novo valor para os campos CPF (apenas dígitos), Nome, Idade e Data_Cadastro (para manter o valor atual de um campo, digite ’-’):\n");
    
    scanf("%s", &cpf);
    scanf(" %s", &nome);
    scanf(" %d", &idade);
    scanf(" %s", &data_cadastro);

    printf("[Sistema]\n");
    printf("Confirma os novos valores para o registro abaixo? (S/N)\n");

}
int search_prefix(const char* nome, const char* termo_busca){

    int count_prefix;
    for (int i = 0; i < strlen(termo_busca); i++){
    
        if(termo_busca[i] == nome[i]){

            count_prefix++;
        }
    }

    if(count_prefix == strlen(termo_busca)){

        return 1;
    }

    return 0;

}

void bd_remover_paciente(Queue* bd){

    int id_remover;
    int validador = 1;

    bd_consultar_paciente(bd);

    printf("Digite o ID do registro a ser removido:\n");

    printf("[Usuário]\n");
    scanf("%d", &id_remover);

    BDPaciente *d = bd->front;
    while(d.id != id_remover){

        
    }

    free(d);

    assert(!q_is_empty(q));

    BDPaciente *p = bd->front; 

    while(validador){

        if(p->pacientes.id == id_remover){

            if (p == bd->front){

                bd->front = bd->front->next;
            }
            validador = 0;
            free(p);
        }else if(p->next == id_remover){
            
            if(p->next == bd->rear){

                BDPaciente rem = bd->rear;
                bd->rear = p;
                free(rem);
            }else{

                BDPaciente rem = p->next;
                p->next = p->next->next;
                free(rem);
            }
        }
    }
        
        p = p->next;
    free(p);
}