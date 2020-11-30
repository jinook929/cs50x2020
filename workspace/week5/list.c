#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // int list[3];
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }
    
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    
    int *tmp = malloc(4 * sizeof(int));
    if (tmp == NULL)
    {
        return 1;
    }
    
    for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }
    
    tmp[3] = 4;
    
    free(list);
    
    list = tmp;
    
    for (int i = 0; i < 4; i++)
    {
        printf("=> %i\n", list[i]);
    }
    
    printf("\n");
    
    int *tmp2 = realloc(list, 5 * sizeof(int));
    if (tmp2 == NULL)
    {
        return 1;
    }
    list = tmp2;

    // free(tmp2);

    list[4] = 5;

    for (int i = 0; i < 5; i++)
    {
        printf("%i\n", list[i]);
    }
    
    free(list);
}