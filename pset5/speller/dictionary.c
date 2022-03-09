// Implements a dictionary's functionality
#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
# include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h> 

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
// Number of buckets in hash table
const unsigned int N = 2000;
// Hash table
node *table[N];
unsigned int hash_value;
int counter = 0;



// Returns true if word is in dictionary else false//***4***
bool check(const char *word)
{
    hash_value = hash(word);
    node *cursor = table[hash_value];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}



// Hashes word to a number//***2***
//run a hash function corresponding the word
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}



// Loads dictionary into memory, returning true if successful else false***1***
//responsible for loading all words in dictionary into a hast table structure
bool load(const char *dictionary)
{

//Open file--
    FILE *f = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        return 1;
    }
//Read strings from the file
    char buffer[LENGTH + 1];
    while (fscanf(f, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        //create new node for each word
        strcpy(n->word, buffer);
        //hash the word
        hash_value = hash(buffer);
        //insert node into hash table at that location
        n->next = table[hash_value];
        //hash table, array of linked lists
        //bu seure to set pointers in the corretct order
        //index into the hast table.
        table[hash_value] = n;
        //count the words which have been taken into the memory
        counter++;
    }
    fclose(f);
    if (size() > 0)
    {
        printf("this part has success\n");
        return true;

    }
    else
    {
        printf("error1\n");
        return false;
    }
}



// Returns number of words in dictionary if loaded else 0 if not yet loaded//***3***
unsigned int size(void)
{
    // TODO
    if (counter > 0)
    {
        return counter;
    }
    return 0;
}
// Unloads dictionary from memory, returning true if successful else false//***5***
bool unload(void)
{
    node *cursor;
    node *tmp;
    for (int i = 0 ; i < N ; i++)
    {
        cursor = table[i];
        while (cursor)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp); 
        }
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
