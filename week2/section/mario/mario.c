#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

void print_row(int lenght);

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./mario [height]");
        return 1;
    }

    int height = atoi(argv[1]);
    
    if(height > 8){
        printf("Maximum height is 8. Height provided: %i", height);
        return 1;
    }

    for(int i = 0; i < height; i++)
    {
        print_row(i + 1);
    }
}

void print_row(int lenght)
{
    for(int i = 0; i < lenght; i++)
    {
        printf("#");
    }
    printf("\n");
}