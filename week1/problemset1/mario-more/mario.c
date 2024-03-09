#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);
void print_bricks(int bricks, string brick);

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while(height < 1 || height > 8);

    for(int i = 1; i <= height; i++)
    {
        print_row(height - i, i);
    }
}

void print_row(int spaces, int bricks)
{
    print_bricks(spaces, " ");

    print_bricks(bricks, "#");

    printf("  ");

    print_bricks(bricks, "#");

    printf("\n");
}

void print_bricks(int bricks, string brick){
    for (int i = 0; i < bricks; i++)
    {
        printf("%s", brick);
    }
}