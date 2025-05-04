#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* unir_colecoes(int *colecao_herois_hq, int *colecao_acao_comics, int tamanho_herois_hq, int tamanho_acao_comics, int *tamanho_final){

    bool validador;
    *tamanho_final = tamanho_herois_hq + tamanho_acao_comics;
    int *colecao_unificada = (int *)malloc(*tamanho_final * sizeof(int));
    int menor;
    int maior;
    int auxiliar[*tamanho_final];

    if (tamanho_herois_hq > tamanho_acao_comics){
        
        for (int i = 0; i < tamanho_herois_hq; i++)
        {
            colecao_unificada[i] = colecao_herois_hq[i];
        }
        
        for (int i = 0; i < tamanho_herois_hq; i++)
        {
            auxiliar[i] = colecao_acao_comics[i];
        }

        menor = tamanho_acao_comics;
        maior = tamanho_herois_hq;

    }else{

        for (int i = 0; i < tamanho_acao_comics; i++)
        {
            colecao_unificada[i] = colecao_acao_comics[i];
        }
        
        for (int i = 0; i < tamanho_herois_hq; i++)
        {
            auxiliar[i] = colecao_herois_hq[i];
        }

        menor = tamanho_herois_hq;
        maior = tamanho_acao_comics;
        
    }

    for (int i = 0; i < menor; i++){
            
        validador = true;
        for (int a = 0; a < maior; a++){
            
            if (auxiliar[i] == colecao_unificada[a]){
                
                validador = false;
                
            }
        }
        
        if (validador == true){
            
            colecao_unificada[maior + i] = auxiliar[i];
        }
    }

    return colecao_unificada;
}

int main(){

    int colecao_herois_hq[] = {101, 102, 103, 104, 201};
    int colecao_acao_comics[] = {201, 202, 203}; 
    int tamanho_herois_hq = sizeof(colecao_herois_hq)/sizeof(int);
    int tamanho_acao_comics = sizeof(colecao_acao_comics)/sizeof(int);
    int tamanho_final; 
    
    int *colecao_unificada = unir_colecoes(colecao_herois_hq, colecao_acao_comics, tamanho_herois_hq, tamanho_acao_comics, &tamanho_final);
    
    printf("Colecao unificada: ");

    for (int i = 0; i < tamanho_final; i++){

        printf("%d ", colecao_unificada[i]);
    }

    printf("Tamanho da colecao unificada: %d", tamanho_final);
    

    free(colecao_unificada);

return 0;
}