#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int size;

    do
    {
        size = get_int("Size: ");
    }
    while(size < 1);

    int sequance[size];

    sequance[0] = 1;
    printf("%i\n", sequance[0]);

    for(int i = 1; i < size; i++)
    {
        sequance[i] = sequance[i - 1] * 2;
        printf("%i\n", sequance[i]);
    }
}