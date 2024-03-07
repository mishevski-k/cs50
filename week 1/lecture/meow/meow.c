#include <cs50.h>
#include <stdio.h>

void meow(int n); //Defining function before adding implementation

int main(void){
    //Old implementation: 1st
    // int counter = 0;

    // while(counter < 3){
    //     printf("meow\n");
    //     counter++;
    // }

    //Old implementation: 2nd
    // for(int i = 3; i < 3; i++){
    //     meow();
    // }

    meow(3);

}

void meow(int n){
    for(int i = 0; i < n; i++){
        printf("meow\n");
    }
}