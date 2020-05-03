// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//size is 2^16
const unsigned int N = 65536;

// Hash table
node *table[N];

//Total words in the dictionary
int count = 0;

//Returns true if word is in dictionary else false
bool check(const char *word)
{
    // check the length of the word and create an array with length + 1 and set the last char to \0
    int len = strlen(word);
    char new_word[len + 1];
    new_word[len] = '\0';

    //turn the letters to lowercase.
    for (int i = 0; i < len; i++)
    {
        new_word[i] = tolower(word[i]);
    }

    // get the hash index of the word.
    int search = hash(new_word);

    // check each word in the linked list the word is in the dictionary.
    for (node *cursor = table[search]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
//credit to delipity(staff) on cs50 reddit page
unsigned int hash(const char *word)
{
    unsigned int h = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        h = (h << 2) ^ word[i];
    }
    return h % N;
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];


    while (fscanf(file, "%s", word) != EOF)
    {
        // allocate a memory for each word in the dictionary.
        node *n = malloc(sizeof(node));
        // copy the word to the allocated memory.
        strcpy(n->word, word);
        // run the hash function.
        int found = hash(word);

        // if there is no words in that bucket just insert the word.
        if (table[found] == NULL)
        {
            table[found] = n;
            n->next = NULL;
            count++;
        }
        // else if the bucket is taken then append the new word.
        else
        {
            n->next = table[found];
            table[found] = n;
            count++;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i < N; i++)
    {
        // create pointer to the beginning of the bucket.
        node *pointer = table[i];
        while (pointer != NULL)
        {
            // create temp node pointing at the pointer.
            node *temp = pointer;
            // moving the pointer the next word in the linked list.
            pointer =  pointer->next;
            free(temp);
        }
    }
    return true;
    count = 0;
}
