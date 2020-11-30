#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(string key);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int n = strlen(argv[1]);
        if (n == 26)
        {
            for (int i = 0; i < 26; i++)
            {
                if (!(argv[1][i] >= 65 && argv[1][i] <= 90) && !(argv[1][i] >= 97 && argv[1][i] <= 122))
                {
                    printf("Usage: ./substitution key\n");
                    return 1;
                }
                for (int j = i + 1; j < 26; j++)
                {
                    if (argv[1][i] == argv[1][j])
                    {
                        printf("Usage: ./substitution key\n");
                        return 1;
                    }
                }
            }
            encrypt(argv[1]);
            // printf("ciphertext: %c\n", encrypt(argv[1]));
            return 0;
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

void encrypt(string key)
{
    string s = get_string("plaintext: ");
    int n = strlen(s);
    char encrypted[n];
    int index;
    char allUppercaseKey[26];
    for (int i = 0; i < 26; i++) 
    {
        allUppercaseKey[i] = toupper(key[i]);
    }
    string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lowercase = "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < n; i++)
    {
        if (s[i] >= 65 && s[i] <= 90)
        {
            index = 0;
            for (int j = 0; j < 26; j++)
            {
                if (s[i] == uppercase[j])
                {
                    break;
                }
                index++;
            }
            encrypted[i] = allUppercaseKey[index];
        }
        else if (s[i] >= 97 && s[i] <= 122)
        {
            index = 0;
            for (int k = 0; k < 26; k++)
            {
                if (s[i] == lowercase[k])
                {
                    break;
                }
                index++;
            }
            encrypted[i] = allUppercaseKey[index] + 32;
        }
        else
        {
            encrypted[i] = s[i];
        }
    }
    
    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
    {
        printf("%c", encrypted[i]);
    }
    printf("\n");
}