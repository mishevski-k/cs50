// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 50000;

// Hash table
node *table[N];

int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    node *ptr = table[index];

    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }

        ptr = ptr->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hashvalue = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hashvalue += tolower(word[i]);
        hashvalue = (hashvalue * tolower(word[i])) % N;
    }
    return hashvalue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *input = fopen(dictionary, "r");

    if (input == NULL)
    {
        printf("Error loading dictionary");
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(input, "%s", word) != EOF)
    {
        dictionary_size++;

        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return 1;
        }

        strcpy(n->word, word);

        int index = hash(word);

        if (table[index] != NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
    }

    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *ptr = NULL;

    for (int i = 0; i < N; i++)
    {
        node *list = table[i];

        while (list != NULL)
        {
            ptr = list;
            list = list->next;
            free(ptr);
        }
    }
    return true;
}
