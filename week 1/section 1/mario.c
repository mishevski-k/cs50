#include <stdio.h>
#include "../../lib/cs50.h"

void print_row(int length);
void print_left_pyramid(int height);

int main(void){

    int height = get_int("Height: ");
    print_left_pyramid(height);
}

void print_left_pyramid(int height){
    for(int i = 1; i <= height; i++){
        print_row(i);
    }
}

void print_row(int length){
    for(int i = 0; i < length; i++){
        printf("#");
    }
    printf("\n");
}