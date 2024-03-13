#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // int numbers[] = {20, 500, 10, 5, 100, 1, 50};

    // int n;

    // do
    // {
    //     n = get_int("Number: ");
    // }
    // while(n < 1);

    // for (int i = 0; i < 7; i++)
    // {
    //     if(numbers[i] == n)
    //     {
    //         printf("Found\n");
    //         return 0;
    //     }
    // }

    // printf("Not Found\n");
    // return 1;

    string strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    string s = get_string("String: ");

    for (int i = 0; i < 6; i++)
    {
        if(strcmp(strings[i], s) == 0)
        {
            printf("Found\n");
            return 0;
        }
    }    

    printf("Not Found\n");
    return 1;
}