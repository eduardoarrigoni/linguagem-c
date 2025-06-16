#include "analise_sintatica_pilha.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the queue.
struct stack
{
    StackNode *top; // Pointer to top of the stack.
};

// Define a structure for a node in the stack.
struct stacknode
{
    char info;      // A float value stored in the node.
    StackNode *next; // A pointer to the next node in the stack.
};

// Function to create a new empty stack.
Stack *s_create()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

// Function to check whether the stack is empty.
int s_is_empty(Stack *s)
{
    return s->top == NULL;
}

// Function to push a float value into the queue.
void s_push(Stack *s, char v)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode)); // Allocate memory for a new node.
    node->info = v;
    node->next = s->top;
    s->top = node;
}
//char s_top(Stack *s)
//{
//    assert(!s_is_empty(s));
//    return s->top->info;
//}

char s_pop(Stack *s)
{
    assert(!s_is_empty(s));

    char v = s->top->info;
    StackNode *p = s->top; // Store for removal
    s->top = s->top->next;
    free(p);
    return v;
}

// Function to free the memory used by the stack.
void s_free(Stack *s)
{
    StackNode *p = s->top;
    while (p != NULL)
    {
        StackNode *t = p->next; // Store a reference to the next node.
        free(p);                // Free the memory allocated for the current node.
        p = t;                  // Move to the next node.
    }
    free(s); // Free the memory allocated for the queue structure itself.
}

// Function to display all elements of the queue.
void s_print(Stack *s)
{
    for (StackNode *p = s->top; p != NULL; p = p->next)
        printf("%c ", p->info);

    printf("\n");
}

int procurar_sintaxe(const char* filename, Stack *s) {

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo %s.\n", filename);
        return 1;
    }
    StackNode *p;
    char line[256];
    char a;
    while (fgets(line, sizeof(line), file) != NULL) {
        
        for (int i = 0; line[i] != '\0'; i++){

            if (line[i] == '{') s_push(s, '}');   
            
            if (line[i] == '[') s_push(s, ']');
                
            if (line[i] == '(') s_push(s, ')');
            
            if (line[i] == ')' || line[i] == '}' || line[i] == ']'){
                p = s->top;
                if (line[i] == p->info){
            
                    printf("sucess\n");
                    a = s_pop(s); 
                    printf("Encontrado o par: %c\n", a);
                }else{
                    printf("Erro\n");
                    return 1;
                }
            }
        }
    }      
    sem_sintaxe(s);
    return 0;
}


void sem_sintaxe(Stack* s){

    for (StackNode *i = s->top; i != NULL; i = i->next){
    
        printf("fail %c\n", i->info);
    }
}
