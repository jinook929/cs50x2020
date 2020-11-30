#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[4] = {{"EMMA", "111-111-1111"}, {"RODRIGO", "222-222-2222"}, {"BRIAN", "333-333-3333"}, {"DAVID", "444-444-4444"}}; 
    // string names[4] = {"EMMA", "RODRIGO", "BRIAN", "DAVID"};
    // string numbers[4] = {"111-111-1111", "222-222-2222", "333-333-3333", "444-444-4444"};
    
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(people[i].name, "DAVID") == 0)
        {
            printf("%s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}