// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// *** Number of words in dictionary
int wordCounter = 0;

// Number of buckets in hash table
const unsigned int N = 676 + 1 + 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Create traverse node
    node *trav;
    
    // Hash word and link trav to hash-assigned linked list
    int hashkey = hash(word);
    trav = table[hashkey];
    
    // Check if word is in loaded dictionary
    while (trav != NULL)
    {
        if (trav == NULL)
        {
            free(trav);
            return false;
        }
        
        if (strcasecmp(word, trav->word) == 0)
        {
            trav = NULL;
            return true;
        }
        trav = trav->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Initialize hashkey
    int hash = 0;

    // Check first 2 letters of word    
    for (int i = 0; i < 2; i++)
    {
        // If 1-letter word, set hashkey as 0
        if (word[i] == '\0')
        {
            return 702;
        }
        
        // Hash first letter
        if (i == 0)
        {
            if (word[i] >= 65 && word[i] <= 90)
            {
                hash += 26 * (((int) word[i] + 32 - 96) - 1);
            }
            else
            {
                hash += 26 * (((int) word[i] - 96) - 1);
            }
        }
        // Hash second letter and return hashkey
        else if (i == 1)
        {
            // When second letter is apostrophe...
            if ((int) word[i] == 39)
            {
                if (word[0] >= 65 && word[0] <= 90)
                {
                    return 676 + (int) word[0] + 32 - 96;
                }
                else
                {
                    return 676 + (int) word[0] - 96;
                }
            }
            
            if (word[i] >= 65 && word[i] <= 90)
            {
                return hash += (int) word[i] + 32 - 96;
            }
            else
            {
                return hash += (int) word[i] - 96;
            }
        }
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Set variable for word from dictionary
    char word[LENGTH];

    // Open dictionary file for reading
    FILE *file = fopen(dictionary, "r");
    // If unable to open file
    if (file == NULL)
    {
        return false;
    }
    else
    {
        // Read word from dictionary and put them into hashtable using chaining (that is, linked list)
        while (fscanf(file, "%s", word) != EOF)
        {
            wordCounter++;
            // Create new node
            node *newNode = malloc(sizeof(node));
            if (newNode == NULL)
            {
                return false;
            }
            strcpy(newNode->word, word);
            newNode->next = NULL;
            
            // Create hashkey for new node
            int hashKey = hash(word);
            // Insert new node into table according to hashkey
            newNode->next = table[hashKey];
            table[hashKey] = newNode;
        }
        fclose(file);
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // When not yet loaded
    if (wordCounter == 0)
    {
        return 0;
    }
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp;
        // When index[i] is NULL, free that node
        if (cursor == NULL)
        {
            continue;
        }

        // When index[i] has linked list...
        while (cursor != NULL)
        {
            // Set pointer to second node in list
            tmp = cursor->next;
            // Free first node in list
            free(cursor);
            // Set pointer as new head
            cursor = tmp;
        }
    }
    return true;
}
