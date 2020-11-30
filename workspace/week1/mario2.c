#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int width;
    do
    {
        width = get_int("Width: ");
    }
    while(width < 1);
    for(int i = 0; i < width; i++)
    {
        printf("?");
    }
    printf("\n");
}