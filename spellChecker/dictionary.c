// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 700;
int globalSize = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int idx = hash(word);
    node *tmp = table[idx];
    while(tmp != NULL)
    {
        if(strcasecmp(word, tmp->word) == 0)
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
    {

unsigned long hash = 5381;

int c = *word;

c = tolower(c);

while (*word != 0)

{

hash = ((hash << 5) + hash) + c;

c = *word++;

c = tolower(c);

}

return hash % N;

}
    // TODO
    //int n = (26  * (tolower(word[0]) - 97)) + (tolower(word[0]) - 97);
    //return n;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char word[LENGTH+1];
    //open dictionary file
    FILE *myDictionary = fopen(dictionary,"r");

    if(myDictionary == NULL)
    {
        return false;
    }
    //read strings from file one at a time
    while(fscanf(myDictionary, "%s",word) != EOF)
    {
        //create a new node for each word
        node *tmp = malloc(sizeof(node));
        if(tmp == NULL)
        {
            printf("couldnt malloc\n");
            return false;
        }

        //copy the word into the new node.
        strcpy(tmp->word,word);

        //hash word to obtain a hash value
        int hashed = hash(word);

        //insert node into hash table at that location
         tmp->next = table[hashed];
         table[hashed] = tmp;
         globalSize++;
    }
    fclose(myDictionary);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if(globalSize > 0)
    {
        return globalSize;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        node *cursor = table[i];
        while(cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
