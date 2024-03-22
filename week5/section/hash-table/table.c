#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    string phrase;
    struct node *next;
}
node;

node *table[26];

int hash(string phrase);
bool unload(void);
void visualizer(node *list);
int main(void)
{
    for(int i = 0; i < 26; i++)
    {
        table[i] = NULL;
    }

    // Add items
    for (int i = 0; i < 3; i++)
    {
        string phrase = get_string("Enter a new phrase: ");

        // Find phrase bucket
        int bucket = hash(phrase);
        printf("%s hashes to %i\n", phrase, bucket);
    }

    unload();
}

// TODO: return the correct bucket for a given phrase
int hash(string phrase)
{

    if (strlen(phrase) < 0)
    {
        return -1;
    }

    char first_letter = phrase[0];

    node *n = malloc(sizeof(node));
    n->phrase = phrase;
    n->next = NULL;

    int node_index = toupper(first_letter) - 'A';

    if(table[node_index] != NULL)
    {
        n->next = table[node_index];
    }

    table[node_index] = n;

    return node_index;
}

bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        node *list = table[i];
        
        if(list == NULL)
        {
            continue;
        }

        node *ptr = list;

        while(ptr != NULL)
        {
            ptr = list->next;
            free(list);
            list = ptr->next;
        }
    }

    return true;
}