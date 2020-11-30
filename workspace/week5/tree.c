#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
Node;

bool search (Node *tree, int num);

int main(void)
{
    // Initialize a tree
    Node *tree = NULL;
    
    // Create tree node and fill the fields
    Node *n = malloc(sizeof(Node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    tree = n;
    
    n = malloc(sizeof(Node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 2;
    n->left = tree;
    n->right = NULL;
    tree->right = n;
    
    n = malloc(sizeof(Node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 3;
    n->left = tree->right;
    n->right = NULL;
    tree->right->right = n;
    
    n = malloc(sizeof(Node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 4;
    n->left = tree->right->right;
    n->right = NULL;
    tree->right->right->right = n;
    
    n = malloc(sizeof(Node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 5;
    n->left = tree->right->right->right;
    n->right = NULL;
    tree->right->right->right->right = n;
    
    n = malloc(sizeof(Node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 6;
    n->left = tree->right->right->right->right;
    n->right = NULL;
    tree->right->right->right->right->right = n;
    
    n = malloc(sizeof(Node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 7;
    n->left = tree->right->right->right->right->right;
    n->right = NULL;
    tree->right->right->right->right->right->right = n;
    
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    printf("=> %s\n", search(tree, num) ? "true" : "false");
}

bool search (Node *tree, int num)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (num < tree->number)
    {
        return search(tree->left, num);
    }
    else if (num > tree->number)
    {
        return search(tree->right, num);
    }
    else
    {
        return true;
    }
}