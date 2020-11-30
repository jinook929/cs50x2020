#include <stdio.h>

int main(void)
{
    int x;
    printf("Enter a number: ");
    scanf("%i", &x);
    printf("x = %i\n", x);
    
    char str[10];
    printf("Enter a string: ");
    scanf("%s", str);
    printf("str = %s\n", str);
}