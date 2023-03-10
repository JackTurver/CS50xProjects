// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// dictionary size counter
long dictionarysizecount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // use hash function to get tablevalue for the word
    long tablevalue = hash(word);

    // look at linked list at the tablevalue point in the hash table
    node *tmp = table[tablevalue];

    // scan through linked list in order to look if the word is in the list
    while (tmp != NULL)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // take the word string input and return a tablevalue that adds up all ASCII values of char's
    long tablevalue = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        tablevalue += toupper(word[i]);
    }
    return tablevalue % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // open the file which we are using as the dictionary
    FILE *wordlist = fopen(dictionary, "r");
    // return false if file cannot be opened
    if (wordlist == NULL)
    {
        printf("Could not open dictionary file.\n");
        return false;
    }
    char nextword[LENGTH + 1];
    // read all words from dictionary one at a time
    while (fscanf(wordlist, "%s", nextword) != EOF)
    {
        // create buffer node to store words and next word
        node *buffer = malloc(sizeof(node));
        if (buffer == NULL)
        {
            return false;
        }
        strcpy(buffer->word, nextword);
        // find hash value from the hash function that has been created
        int tablevalue = hash(nextword);
        // use the hash value to put the word in the hash table with correct key
        buffer->next = table[tablevalue];
        table[tablevalue] = buffer;
        dictionarysizecount++;
    }

    // close dictionary
    fclose(wordlist);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // we set this up inthe load function so if the file was loaded then it will return the value
    // if it wasn't loaded then the dictionarysizecount value stays at it's originaly set value of 0
    return dictionarysizecount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // scan through the hash table and free the linked lists up in order without losing the info for the next node
    for (int i = 0; i < N; i++)
    {
        // use temporary pointer to scan through linked list
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
        if (ptr == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
