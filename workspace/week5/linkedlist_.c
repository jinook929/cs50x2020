#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represent a node
struct node
{
    char *data;
    struct node *next;
};
typedef struct node Node;

// Create a head node of size 0, initially not pointing to anything
Node *head = NULL;

// ********** In case, head is not global  **********
// void addFirst(Node **p, char *item); 

void addFirst(char *item);
void addAfter(Node *prev, char *item);
void addByIndex(int index, char *item);
Node *removeFirst();
Node *removeAfter(Node *prev);
Node *removeByIndex(int index);
Node *removeByValue(char *item);
Node *getNode(int index);
Node *find (char *item);

int main(void)
{
    // Case for head node is local
    // Node *head = NULL;
    
    // Create the first node and link it to head
    Node *n = malloc(sizeof(Node));
    if (n == NULL)
    {
        return 1;
    }
    n->data = "Tuesday";
    n->next = NULL;
    head = n;
    
    // Create the second node and link it to the first node
    n = malloc(sizeof(Node));
    if (n == NULL)
    {
        return 1;
    }
    n->data = "Thursday";
    n->next = NULL;
    head->next = n;
    
    // Create the third node and make it head
    n = malloc(sizeof(Node));
    if (n == NULL)
    {
        return 1;
    }
    n->data = "Monday";
    n->next = head;
    head = n;
    
    printf("=> initial linked list head : %s\n", head->data);
    
    // Print linked list
    Node *p = head;
    while(p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }
    
    // Add Sunday at the first index
    addFirst("Sunday");
    printf("=> current head after addFirst('Sunday') : %s\n", head->data);
    
    // Get 2nd node and add Wednesday after it
    Node *nthNode = getNode(2);
    if (nthNode == NULL)
    {
        return 2;
    }
    addAfter(nthNode, "Wednesday");
    printf("=> Wednesday added after index[2]\n");
    
    // Print linked list
    p = head;
    while(p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }
    
    // Remove the first node and free it
    free(removeFirst());
    printf("=> First node removed, then current head : %s\n", head->data);
    
    // Get the 1st node and remove node after it
    nthNode = getNode(1);
    printf("=> Node after [%s] will be deleted.\n", nthNode->data);
    if (nthNode == NULL)
    {
        return 2;
    }
    free(removeAfter(nthNode));

    // Print linked list
    p = head;
    while(p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }
    
    // Add Friday in index[3], remove node in index[2, and remove node of Monday
    addByIndex(3, "Friday");
    free(removeByIndex(2));
    free(removeByValue("Tuesday"));
    printf("=> added Friday, removed Thursday, and removed Tuesday\n");
    
    // Print linked list
    p = head;
    while(p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }
    
    free(removeByValue(find("Monday")->data));
    printf("=> removed Monday\n");
    
    // Print linked list
    p = head;
    while(p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }
    
    // Free linked list
    while(head != NULL)
    {
        Node *trav = head->next;
        free(head);
        head = trav;
    }
}

// ********** In case, head is not global **********
// void addFirst(Node **p, char *item)
// {
//     Node *temp = malloc(sizeof(Node));
//     temp->data = item;
//     temp->next = *p;
//     *p = temp;
// }

// Add node in first index
void addFirst(char *item)
{
    // Allocate memory for new node
    Node *temp = malloc(sizeof(Node));
    // Populate data field of new node
    temp->data = item;
    // Link new node to previous first node
    temp->next = head;
    // Move head to new node
    head = temp;
}

// Add node after speific node
void addAfter(Node *prev, char *item)
{
    // Check if target node is valid
    if (prev != NULL)
    {
        // Allocate memory for new node
        Node *temp = malloc(sizeof(Node));
        // Populate data field of new node
        temp->data = item;
        // Link new node to previous node's next
        temp->next = prev->next;
        // Link previous node to new node
        prev->next = temp;
    }
}

// Add node to specific index
void addByIndex(int index, char *item)
{
    // Add new node when index[0]
    if(index == 0)
    {
        addFirst(item);
    }
    // Add new node to specific index other than 0
    else if (index > 0)
    {
        // Get previous node of target index
        Node *prev = getNode(index - 1);
        if (prev != NULL)
        {
            // Add new node after previous node of target index
            addAfter(prev, item);
        }
    }
}

// Remove node in first index
Node *removeFirst()
{
    // Check if there is any node in list
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        // Remember to-be-removed node
        Node *removed = head;
        // Link head to second node
        head = head-> next;
        // Return removed node
        return removed;
    }
}

// Remove node after selected node
Node *removeAfter(Node *prev)
{
    // Remember to-be-removed node
    Node *removed = prev->next;
    // Check if target node is NULL
    if (removed == NULL)
    {
        return NULL;
    }
    else
    {
        // Link selected node to next of to-be-removed node
        prev->next = removed->next;
        // Return removed node
        return removed;
    }
}

// Remove node at target index
Node *removeByIndex(int index)
{
    // Check if target index is valid
    if (index < 0)
    {
        return NULL;
    }
    
    // When target is 0, remove first node and return its address
    if (index == 0)
    {
        return removeFirst();
    }
    
    // When target is not 0...
    // Get previous node of target index
    Node *prev = getNode(index - 1);
    // If next of previous node, which is target index, is not NULL, 
    // remove next of previous node, again, which is target index
    if (prev->next != NULL)
    {
        return removeAfter(prev);
    }
    // If no index matches, return NULL
    return NULL;
}

// Remove node with target data
Node *removeByValue(char *item)
{
    // Create travers node
    Node *trav = head;
    // Create node that follows traverse
    Node *temp = NULL;
    // Find node with target data
    while (trav != NULL && strcmp(trav->data, item) != 0)
    {
        // Set temp as current traverse
        temp = trav;
        // Move traverse to next in list
        trav = trav->next;
    }
    
    // Check if there is no match
    if (trav == NULL)
    {
        return NULL;
    }
    // Check if there is only one node in list
    if (temp == NULL)
    {
        return removeFirst();
    }
    else
    {
        // Remove next of node that follows traverse, which is target node
        return removeAfter(temp);
    }
}

// Get node with index
Node *getNode(int index)
{
    // Check if index is valid
    if (index < 0)
    {
        return NULL;
    }
    
    // ********** Get target node by using for loop **********
    // Node *p = head;
    // for (int i = 0; i < index && p != NULL; i++)
    // {
    //     p = p->next;
    // }
    // return p;
    
    // Create traverse node
    Node *trav = head;
    // Set counter to track current index of traverse node
    int count = 0;
    // Loop linked list until traverse node is NULL
    while (trav != NULL)
    {
        // Check if target index is current index of traverse node
        if (count == index)
        {
            return trav;
        }
        count++;
        trav = trav->next;
    }
    // Return NULL when target item is not present
    return NULL;
}

// Get node with data value
Node *find (char *item)
{
    // Create traverse node
    Node *trav = head;
    // Loop linked list until traverse node is NULL
    while (trav != NULL)
    {
        // Check if target item equals to data field of current traverse node position
        if (strcmp(trav->data, item) == 0)
        {
            return trav;
        }
        // Move traverse node to next in linked list
        trav = trav->next;
    }
    // Return NULL when target item is not present
    return NULL;
}