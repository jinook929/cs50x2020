#include <cs50.h>
#include <stdio.h>

void cough(int num);

int main(void)
{
    int n = get_int("How many times do you cough?\n");
    cough(n);
}

void cough(int num) 
{
    for(int i = 0; i < num; i++)
    {
        printf("cough #%i\n", i+1);
    }
}