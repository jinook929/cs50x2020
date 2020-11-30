#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string names[4];
    names[0] = "JINOOK";
    names[1] = "SUNMI";
    names[2] = "SUA";
    names[3] = "JUA";
    
    printf("%s\n", names[0]);
    printf("%c %c %c.%i.\n", names[0][0], names[0][1], names[0][2], names[0][6]);
    
    string name1 = "EMMA";
    string name2 = "TODRIGO";
    string name3 = "BRIAN";
    string name4 = "DAVID";
}