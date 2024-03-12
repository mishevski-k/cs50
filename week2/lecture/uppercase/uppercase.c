#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");

    for(int i = 0, n = strlen(s); i < n; i++)
    {
        // If uppercase
        // if(s[i] >= 'a' && s[i] <= 'z')
        // {
        //     // Hacky way of doing uppercase. referance A = 65 a = 97 in ASCII
        //     //printf("%c", s[i] - 32); 
        //     printf("%c", toupper(s[i]));
        // }
        // else
        // {
        //     printf("%c", s[i]);
        // }

        printf("%c", toupper(s[i]));
    }

    printf("\n");
}