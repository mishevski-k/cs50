#include <stdio.h>
#include "../lib/cs50.h"

int main(void){
    int n;
    // Prompt user for size of wall
    do{
        n = get_int("Size: ");
    }while(n < 1);

    // Pring an n-by-b grid of brick
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("#");
        }
        printf("\n");
    }
}