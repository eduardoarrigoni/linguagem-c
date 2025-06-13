#ifndef analise_sintatica_pilha_H
#define analise_sintatica_pilha_H

typedef struct stack Stack;
typedef struct stacknode StackNode;

Stack *s_create();

char s_pop(Stack *q);

char s_top(Stack *q);

void s_push(Stack *s, char* v);

void l_push(char *l, char v);

int s_is_empty(Stack *s);

void s_free(Stack *s);

void s_print(Stack *s);

int procurar_sintaxe(const char* filename, Stack *s, char* l);

void sem_sintaxe(Stack* s, char* l);

void search(Stack *s, char* l, char* caracter);

#endif