#include <stdio.h>
#include "linkedlist.h"

int main(){

    LinkedList *l1;
    LinkedList *l2;
    LinkedList *list_concatenate;
    int num;

    printf("Criado uma lista encadiada\n");
    l1 = ll_create(); 

    for (int i = 0; i < 4; i++){

        printf("Qual o elemento de numero %d: \n", i);
        scanf("%d", &num);
        ll_insert(l1, num); // Insert elements into the list using ll_insert.
    }
    printf("------------\n\n");

    printf("Criado uma lista encadiada\n");
    l2 = ll_create(); 

    for (int i = 0; i < 4; i++){

        printf("Qual o elemento de numero %d: \n", i);
        scanf("%d", &num);
        ll_insert(l2, num); // Insert elements into the list using ll_insert.
    }
    printf("------------\n\n");

    list_concatenate = ll_concatenate(l1, l2);

    ll_print(list_concatenate);

    return 0;
}