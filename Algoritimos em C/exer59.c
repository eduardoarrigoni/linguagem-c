#include <stdio.h>

int main(){

    int n;

    printf("Diga o tamanho n do vetor: ");
    scanf("%d", &n);

    int v[n];

    for (int i = 0; i < n; i++){

        printf("diga o elemento: ");
        scanf("%d", &v[i]);

    }

    int s[n];

    s[0] = v[0];
    for (int i = 1; i < n; i++){

        s[i] = s[i - 1] + v[i];

    }


    for (int i = 0; i < n; i++){

        printf("%d ", v[i]);
        
    }
    printf("\n");
    for (int i = 0; i < n; i++){

        printf("%d ", s[i]);
        
    }
    return 0;
}