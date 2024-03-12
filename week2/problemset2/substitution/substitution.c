#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>

bool validate_key(string key);
string encrypt(string key, string plain_text);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    bool isValid = validate_key(key);

    if (!isValid)
    {
        return 1;
    }

    string plain_text = get_string("plaintext: ");
    string cipher_text = encrypt(key, plain_text);

    printf("ciphertext: %s\n", cipher_text);
}

string encrypt(string key, string plain_text)
{
    for (int i = 0; i < strlen(plain_text); i++)
    {
        char c = plain_text[i];

        if (isalpha(c))
        {
            char cipher_char;
            if (islower(c))
            {
                cipher_char = key[c - 'a'];
                c = isupper(cipher_char) ? tolower(cipher_char) : cipher_char;
            }
            else
            {
                cipher_char = key[c - 'A'];
                c = islower(cipher_char) ? toupper(cipher_char) : cipher_char;
            }

            plain_text[i] = c;
        }
    }

    return plain_text;
}

bool validate_key(string key)
{
    char duplicateKeyValues[26];

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Usage: ./substitution key\n");
            return false;
        }

        bool isDuplicate = false;

        for (int j = 0; j < 26; j++)
        {
            if (toupper(key[i]) == toupper(duplicateKeyValues[j]))
            {
                isDuplicate = true;
            }
        }

        if (isDuplicate)
        {
            printf("Usage: ./substitution key\n");
            return false;
        }
        else
        {
            duplicateKeyValues[i] = key[i];
        }
    }

    return true;
}
