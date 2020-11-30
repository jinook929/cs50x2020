#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
double colemanLiauIndex(int l, int w, int s);

int main(void)
{
    string s = get_string("Text: ");
    int l = count_letters(s);
    int w = count_words(s);
    int ss = count_sentences(s);
    
    printf("%i letter(s)\n", l);
    printf("%i word(s)\n", w);
    printf("%i sentence(s)\n", ss);

    int c = round(colemanLiauIndex(l, w, ss));
    if (c < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (c > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", c);
    }
}

int count_letters(string s) 
{
    int n = strlen(s);
    int letterNum = 0;
    for (int i = 0; i < n; i++)
    {
        if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122)) 
        {
            letterNum++;
        }
    }
    
    return letterNum;
}

int count_words(string s)
{
    int n = strlen(s);
    int blankNum = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 32) 
        {
            blankNum++;
        }
    }
    
    return blankNum + 1;
}

int count_sentences(string s)
{
    int n = strlen(s);
    int sentenceNum = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 33 || s[i] == 46 || s[i] == 63) 
        {
            sentenceNum++;
        }
    }
    
    return sentenceNum;
}

double colemanLiauIndex(int l, int w, int s)
{
    return 0.0588 * ((double) l * 100 / (double) w) - 0.296 * ((double)s * 100 / (double)w) - 15.8;
}