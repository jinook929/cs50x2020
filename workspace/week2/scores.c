#include <cs50.h>
#include <stdio.h>

float average(int length, int array[]);

const int N = 3;

int main(void)
{
    int score1 = 72;
    int score2 = 73;
    int score3 = 33;
    printf("Average: %i\n", (score1 + score2 + score3) / 3);
    
    int scores[N];
    scores[0] = 72;
    scores[1] = 73;
    scores[2] = 33;
    for (int i = 0; i < 3; i++)
    {
        printf("%c", scores[i]);
    }
    printf("\n");
    
    printf("Average: %i\n", (scores[0] + scores[1] + scores[2]) / N);
    
    int total = 0;
    for(int i = 0; i < (sizeof(scores) / sizeof(scores[0])); i++)
    {
        total += scores[i];
    }
    printf("Average: %i\n", (total / N));
    
    int n = get_int("Number of scores: ");
    
    int scores1[n];
    int t = 0;
    for (int i = 0; i < n; i++)
    {
        scores1[i] = get_int("Score#%i: ", (i + 1));
        t += scores1[i];
    }
    printf("The average is %i.\n", t/n);
    printf("Average: %.2f\n", average(n, scores1));
    
    char s[] = "HI THERE!";
    printf("%s\n", s);
    printf("%c\n", s[9]);
    printf("%i\n", s[9]);
    printf("string s Length: %i\n", (int) (sizeof(s) / sizeof(s[0]) - 1));
}

float average(int length, int array[])
{
    int total = 0;
    for (int i = 0; i < length; i++)
    {
        total += array[i];
    }
    
    return (float) total / length;
}