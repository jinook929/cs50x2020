#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9
string candidates[MAX];
int preferences[MAX][MAX];

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);

int main(int argc, string argv[])
{
    for (int i = 0; i < 3; i++)
    {
        candidates[i] = argv[i + 1];
        printf("Candidate[%i]: %s\n", i, candidates[i]);
    }

                for (int x = 0; x < 3; x++)
                {
                    for (int y = 0; y < 3; y++)
                    {
                        printf(" %i ||", preferences[x][y]);
                    }
                    printf("\n");
                }
                printf("\n");

    for (int i = 0; i < 5; i++)
    {

        // ranks[i] is voter's ith preference
        int ranks[3];

        // Query for each rank
        for (int j = 0; j < 3; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        printf("\n");
        record_preferences(ranks);

        printf("\n");
    }
}

bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            // printf("rank[%i] <- %i\n", rank, ranks[rank]);
            return true;
        }
    }
    return false;
}

void record_preferences(int ranks[])
{
    // TODO
    int iranksIndex, jranksIndex;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            iranksIndex = -1;
            jranksIndex = -2;
            
            for (int k = 0; k <3; k++)
            {
                if (i == ranks[k])
                {
                    iranksIndex = k;
                }
            }
            for (int l = 0; l < 3; l++)
            {
                if (j == ranks[l])
                {
                    jranksIndex = l;
                }
            }

            if (iranksIndex < jranksIndex)
            {
                printf("=> iranksIndex = %i, jranksIndex = %i\n", iranksIndex, jranksIndex);
                preferences[i][j]++;
                for (int x = 0; x < 3; x++)
                {
                    for (int y = 0; y < 3; y++)
                    {
                        printf(" %i ||", preferences[x][y]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
    }

    // for (int x = 0; x < candidate_count; x++)
    // {
    //     for (int y = 0; y < candidate_count; y++)
    //     {
    //         printf("|| %i ||", preferences[ranks[x]][ranks[y]]);
    //     }
    //     printf("\n");
    // }
    return;
}