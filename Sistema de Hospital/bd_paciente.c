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
   printf("Base de dados criada.\n");
   q->total_pacientes = 0;                // Initialize the front and rear pointers to NULL, indicating an empty queue.
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

    bd->total_pacientes -= 1;
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
    
    
    bd->total_pacientes = 0;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        
        excluir_espaco_branco(line);
        
        if (strlen(line) == 0) {
            continue;
        }
        
        Paciente p; //leitura e separação dos campos do csv
        char *token = strtok(line, ",");
        if (token){
            if (atoi(token) == 0){
                continue;
            }
            p.id = atoi(token);
        } 
        
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

    }

    int escolha_modo;
    char termo_busca[MAX_NOME_LEN];
    int encontrados = 0;
    char prefix_cpf[20];

    while (1) { //loop at� a op��o inserida ser v�lida
        printf("[Sistema]\nEscolha o modo de consulta:\n");
        printf("1 - Por nome\n");
        printf("2 - Por CPF\n");
        printf("3 - Retornar ao menu principal\n");
        printf("[Usuario]\n");
        scanf("%d", &escolha_modo);
        getchar();


        if (escolha_modo == 3) return;

        if (escolha_modo == 1) {
            printf("[Sistema]\n Digite o nome: ");
            fgets(termo_busca, sizeof(termo_busca), stdin);
            excluir_espaco_branco(termo_busca);
            break;
        } else if(escolha_modo == 2) {
            printf("[Sistema]\n Digite o cpf: ");
            fgets(termo_busca, sizeof(termo_busca), stdin);
            excluir_espaco_branco(termo_busca);
            
            formatar_prefix_cpf(termo_busca, prefix_cpf);
            break;
        }else{
            
            printf("[Sistema]\nOpcao invalida. Por favor, escolha 1, 2 ou 3.\n");
        }
    }


    imprimir_cabecalho();
    
    for (BDPaciente *p = bd->front; p != NULL; p = p->next) { //busca pelos poss�veis pacientes com o que foi digitado pelo usu�rio
        int encontra = 0;
        if (escolha_modo == 1 && search_prefix(p->pacientes.nome, termo_busca)) {
            encontra = 1;
        } 
         else if (escolha_modo == 2 && search_prefix(p->pacientes.cpf, prefix_cpf)) {
            encontra = 1;
        }

        if (encontra) {
            paciente_imprimir(p->pacientes);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("[Sistema]\nNenhum paciente encontrado com o termo '%s'.\n", termo_busca);
    } else {
        printf("\n[Sistema]\nTotal de pacientes encontrados: %d\n", encontrados);
    }
}

void bd_imprimir_lista_pacientes(Queue* bd) { //imprimir todos pacientes
    if (bd->total_pacientes == 0) {
        printf("[Sistema]\nNenhum paciente cadastrado para imprimir.\n");
        return;
    }

    printf("\n[Sistema]\nImprimindo lista de pacientes...\n");
    imprimir_cabecalho();

	for (BDPaciente *p = bd->front; p != NULL; p = p->next) {
        paciente_imprimir(p->pacientes);
		int a = 0;
        if ((a + 1) % TAMANHO_PAGINA == 0 && (a + 1) < bd->total_pacientes) { //pagina��o
            printf("\n[Sistema]\nPressione ENTER para ver a proxima pagina...\n");
            while (getchar() != '\n');
        }
        a += 1;
    }

    printf("\n[Sistema]\nFim da lista de pacientes.\n");
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
    int cpf_igual = 1;

    printf("[Sistema]\nPara inserir um novo registro, digite os valores para os campos CPF (apenas dígitos), Nome, Idade e Data_Cadastro(precione enter a cada informação escrita):\n");
    while (escolha != 's'){
        scanf(" %s", &*cpf);
        scanf(" %s", &*nome);
        scanf(" %d", &idade);
        scanf(" %s", &*data_cadastro);

        formatarCPF(cpf, saida_cpf);
        
        while(cpf_igual == 1){
            cpf_igual = 0;
            for (BDPaciente *p = bd->front; p != NULL; p = p->next){
                
                if(saida_cpf == p->pacientes.cpf){
                    
                    printf("[Sistema]\nEsse cpf já está cadastrado, digite outro: \n");
                    cpf_igual = 1;
                    break;
                }
            }

        }
        printf("[Sistema]\nConfirma a inserção do registro abaixo? (S/N)\n");

        imprimir_cabecalho();
        printf("%-4d ", bd->total_pacientes + 1);
        
        printf("%s ", saida_cpf);    
        printf(" %-30s %-5d %-12s\n", nome, idade, data_cadastro);
        
        scanf(" %c", &escolha);

        if (escolha != 's'){
            printf("[Sistema]\n1. Sair\n");
            printf("2. Preencher novamente\n");
            scanf(" %c", &escolha);
            if (escolha == '1'){
                return;
            }
            cpf_igual = 1;
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

void bd_atualizar_paciente(Queue* bd) {
    if (bd->total_pacientes == 0) {
        printf("[Sistema]\nNenhum paciente cadastrado para atualizacao.\n");
        return;
    }

    int id_busca;
    char mem_temporaria[100];

    bd_consultar_paciente(bd);

    printf("\n[Sistema]\nDigite o ID do registro a ser atualizado: ");
    scanf("%d", &id_busca);
    getchar(); // Limpa newline do scanf

    BDPaciente *no = bd->front;
    while (no && no->pacientes.id != id_busca) no = no->next;

    if (!no) {
        printf("[Sistema]\nPaciente com ID %d nao encontrado.\n", id_busca);
        return;
    }

    Paciente *p = &no->pacientes;
    Paciente copia = *p; // Para exibir antes de confirmar

    printf("\n[Sistema]\nDigite o novo valor para os campos CPF (apenas dígitos), Nome, Idade e Data_Cadastro (para manter o valor atual de um campo, digite -):\n");

    
    fgets(mem_temporaria, sizeof(mem_temporaria), stdin); excluir_espaco_branco(mem_temporaria);
    if (strcmp(mem_temporaria, "-") != 0) {
        formatarCPF(mem_temporaria, copia.cpf);
    }

    
    fgets(mem_temporaria, sizeof(mem_temporaria), stdin); excluir_espaco_branco(mem_temporaria);
    if (strcmp(mem_temporaria, "-") != 0) {
        strncpy(copia.nome, mem_temporaria, MAX_NOME_LEN);
    }

    
    fgets(mem_temporaria, sizeof(mem_temporaria), stdin); excluir_espaco_branco(mem_temporaria);
    if (strcmp(mem_temporaria, "-") != 0) {
        copia.idade = atoi(mem_temporaria);
    }

    
    fgets(mem_temporaria, sizeof(mem_temporaria), stdin); excluir_espaco_branco(mem_temporaria);
    if (strcmp(mem_temporaria, "-") != 0) {
        strncpy(copia.data_cadastro, mem_temporaria, MAX_DATA_LEN);
    }

    imprimir_cabecalho();
    paciente_imprimir(copia);

    printf("Confirma a atualização? (S/N): ");
    char c;
    scanf(" %c", &c);

    if (tolower(c) == 's') {
        *p = copia;
        printf("Registro atualizado com sucesso!\n");
    } else {
        printf("Atualizacao cancelada.\n");
    }
}

int search_prefix(const char* nome, const char* termo_busca){

    int count_prefix = 0;
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
    char excluir;
    int flag_removido = 0;

    bd_consultar_paciente(bd);

    printf("Digite o ID do registro a ser removido:\n");

    printf("[Usuário]\n");
    scanf("%d", &id_remover);
    
    printf("[Sistema]\nTem certeza de que deseja excluir o registro abaixo? (S/N)\n");

    BDPaciente *d = bd->front;
    while(validador){

        if(d->pacientes.id == id_remover){
            imprimir_cabecalho();
            paciente_imprimir(d->pacientes);
            validador = 0;
        }
        d = d->next;
    }
    scanf(" %c", &excluir);

    if(tolower(excluir) == 'n') return;

    BDPaciente *p = bd->front; 

    while(p->next != NULL){

        if((p->pacientes.id == id_remover) && flag_removido == 0){

            if (p == bd->front){

                bd->front = bd->front->next;
                flag_removido = 1;
            }
            
        }else if((p->next->pacientes.id == id_remover) && flag_removido == 0){
            
            if(p->next == bd->rear){

                BDPaciente *rem = bd->rear;
                bd->rear = p;
                free(rem);
            }else{

                BDPaciente *rem = p->next;
                p->next = p->next->next;
                free(rem);
            }
            flag_removido = 1;
        }
        p = p->next;
        if(flag_removido){
            p->pacientes.id -= 1;
        }
    }
    free(p);
    printf("[Sistema]\nRegistro removido com sucesso.\n");
}

void formatar_prefix_cpf(const char *entrada, char *saida){

    int a = 0;
    int i = 0;
    while(a <= strlen(entrada)){

        if(i == 3 || i == 7){
            //333.333.333-33
            saida[i] = '.';
            i++;

        }else if(i == 11){

            saida[i] = '-';
            i++;
        }else{

            saida[i] = entrada[a];
            i++;
            a++;
        }
    }
}

