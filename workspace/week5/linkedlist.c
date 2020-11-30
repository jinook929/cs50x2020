#include <stdio.h>
#include <stdlib.h>

// Represent a node
typedef struct node
{
    int number;
    struct node *next;
}
Node;

int main(void)
{
    // List of size 0, initially not pointing to anything
    Node *list = NULL;
    
    // Add number to list: create the first node in the list and link the list head to this
    Node *n = malloc(sizeof(Node));
    if(n == NULL)
    {
        return 1;
    }
    n->number = 1;
    n-> next = NULL;
    list = n;
    
    // Add nuber to list: create the second node and link the first node to this
    n = malloc(sizeof(Node));
    if(n == NULL)
    {
        return 1;
    }
    n->number = 2;
    n->next = NULL;
    list->next = n;
    
    // Add number to list: create another node and link the previous node to this
    n = malloc(sizeof(Node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 3;
    n->next = NULL;
    list->next->next = n;
    
    // Print list
    for (Node *trav = list; trav != NULL; trav = trav->next)
    {
        printf("%i\n", trav->number);
    }
    
    // Free list
    while(list != NULL)
    {
        Node *trav = list->next;
        free(list);
        list = trav;
    }
}