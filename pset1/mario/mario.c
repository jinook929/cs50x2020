#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < ((height * 2) + 2); j++)
        {
            if (((j < height) && (height <= (i + j + 1))) || ((j > height + 1) && ((height > (j - i - 2))))) 
            {
                printf("#");
            }
            else if (height == (j - i - 2))
            {
                printf("#");
                break;
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}