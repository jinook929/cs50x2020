#include <stdio.h>

int main(void) 
{
    char c1 = 'H';
    char c2 = 'I';
    char c3 = '!';
    printf("%c %c %c\n", c1, c2, c3);
    printf("%i %i %i\n", c1, c2, c3);
    printf("%i %i %i\n", (int) c1, (int) c2, (int) c3);
    
    int score1 = 72;
    int score2 = 73;
    int score3 = 33;
    printf("%c %c %c\n", score1, score2, score3);
}