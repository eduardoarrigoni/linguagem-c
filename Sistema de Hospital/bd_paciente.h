#ifndef BD_PACIENTE_H
#define BD_PACIENTE_H

typedef struct bdpaciente BDPaciente;
typedef struct paciente Paciente;
typedef struct queue Queue;

BDPaciente* bd_criar();

Queue *q_create();

void inserir_na_fila(Queue *bd, Paciente paciente);

void excluir_espaco_branco(char *s);

Paciente remover_da_fila(Queue *bd);

int q_is_empty(Queue *bd);

void q_free(Queue *bd);

int bd_carregar_csv(Queue* bd, const char* filename);

void bd_consultar_paciente(Queue* bd);

void bd_imprimir_lista_pacientes(Queue* bd);

void paciente_imprimir(Paciente p);

void formatarCPF(const char *entrada, char *saida);

void bd_inserir_paciente(Queue* bd);

void bd_atualizar_paciente(Queue* bd);

void bd_remover_paciente(Queue* bd);

int search_prefix(const char* nome, const char* termo_busca);

void formatar_prefix_cpf(const char *entrada, char *saida);

#endif 
