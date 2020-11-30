#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define LENGTH 45

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 676 + 1 + 26;
node *table[N];
int wordCounter = 0;

node *createNode(char *w);
int hash(char *w);
bool check(char *word);
void unload(void);

int main(void)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char word[LENGTH];
    node *head = NULL;
   
    FILE *file = fopen("large", "r");
    
    if (file == NULL)
    {
        return 1;
    }
    else
    {
        while (fscanf(file, "%s", word) != EOF)
        {
            wordCounter++;
            node *newNode = createNode(word);
            int hashKey = hash(word);
            newNode->next = table[hashKey];
            table[hashKey] = newNode;
        }
        fclose(file);
        
        node *p = malloc(sizeof(node));
        if (p == NULL)
        {
            return 1;
        }
        p = table[653];
        while (p != NULL)
        {
            printf("%s\n", p->word);
            p = p->next;
        }

        printf("[I'd] hashed => %i\n", hash("I'd"));
        printf("Number of words : %i\n", wordCounter);
        
        char *testWord = "I'd";
        
        // for (int i = 0; i <= strlen(testWord); i++)
        // {
        //     if (testWord[i] >= 65 && testWord[i] <= 90)
        //     {
        //         testWord[i] += 32;
        //     }
        // }
        
        if (check(testWord))
        {
            printf("Word [%s] found!!!\n", testWord);
        }
        
        unload();
        return 0;
    }
}

node *createNode(char *w)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    strcpy(n->word, w);
    n->next = NULL;
    
    return n;
}

int hash(char *w)
{
    int hash = 0;
    for (int i = 0; i < 2; i++)
    {
        if (w[i] == '\0')
        {
            return 0;
        }
        
        if (i == 0)
        {
            if (w[i] >= 65 && w[i] <= 90)
            {
                hash += 26 * (((int) w[i] + 32 - 96) - 1);
            }
            else
            {
                hash += 26 * (((int) w[i] - 96) - 1);
            }
        }
        
        else if (i == 1)
        {
            if ((int) w[i] == 39)
            {
                if (w[0] >= 65 && w[0] <= 90)
                {
                    return 676 + (int) w[0] + 32 - 96;
                }
                else
                {
                    return 676 + (int) w[0] - 96;
                }
                // return 676 + (int) w[0] - 96;
            }
            if (w[i] >= 65 && w[i] <= 90)
            {
                hash += (int) w[i] + 32 - 96;
            }
            else
            {
                hash += (int) w[i] - 96;
            }
        }
    }
    
    return hash;
}

int size(void)
{
    return wordCounter;
}

bool check(char *w)
{
    // Create traverse node
    node *trav = malloc(sizeof(node));
    if (trav == NULL)
    {
        return false;
    }
    
    // Hash word and link trav to hash-assigned linked list
    int hashkey = hash(w);
    trav = table[hashkey];
    
    // Check if word is in loaded dictionary
    int counter = -1;
    while (trav != NULL)
    {
        counter++;
        printf("table #%03i [%03i] : %s\n", hashkey, counter, trav->word);
        if (strcasecmp(w, trav->word) == 0)
        {
            // free(trav);
            return true;
        }
        trav = trav->next;
    }
    // free(trav);
    return false;
}

void unload(void)
{
    printf("Now, unloading...\n");
    for (int i = 0; i < N; i++)
    {
        node *current = table[i];
        node *next;
        while(current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        
        current = NULL;
    }
}