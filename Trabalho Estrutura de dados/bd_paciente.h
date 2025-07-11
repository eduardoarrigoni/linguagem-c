#ifndef BD_PACIENTE_H
#define BD_PACIENTE_H

typedef struct bdpaciente BDPaciente;
typedef struct paciente Paciente;

BDPaciente* bd_criar();

void bd_free(BDPaciente* bd);

int bd_carregar_csv(BDPaciente* bd, const char* filename);

void bd_consultar_paciente(BDPaciente* bd);

void bd_imprimir_lista_pacientes(BDPaciente* bd);

void paciente_imprimir(Paciente p);

#endif 
