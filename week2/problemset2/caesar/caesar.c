#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);

    string plain_text = get_string("plaintext: ");

    for (int i = 0; i < strlen(plain_text); i++)
    {
        char c = plain_text[i];

        if (isalpha(c))
        {
            if (islower(c))
            {
                c = (c - 'a' + key) % 26 + 'a';
            }
            else if (isupper(c))
            {
                c = (c - 'A' + key) % 26 + 'A';
            }
        }

        plain_text[i] = c;
    }

    printf("ciphertext: %s\n", plain_text);
}
