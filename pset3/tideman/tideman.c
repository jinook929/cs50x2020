#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("[%i]", locked[i][j]);
        }
        printf("\n");
    }
    
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        printf("%i ", ranks[i]);
    }
    printf("\n");
    int iranksIndex, jranksIndex;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            iranksIndex = -1;
            jranksIndex = -2;
            for (int k = 0; k < candidate_count; k++)
            {
                if (i == ranks[k])
                {
                    iranksIndex = k;
                }
            }
            for (int l = 0; l < candidate_count; l++)
            {
                if (j == ranks[l])
                {
                    jranksIndex = l;
                }
            }

            if (iranksIndex < jranksIndex && iranksIndex != -1 && jranksIndex != -2)
            {
                printf("preferences index : [%i(R#%i)]<[%i(R#%i)]\n", i, iranksIndex, j, jranksIndex);
                preferences[i][j]++;
                for (int x = 0; x < candidate_count; x++)
                {
                    for (int y = 0; y < candidate_count; y++)
                    {
                        printf(" %i ||", preferences[x][y]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int counter = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[counter].winner = i;
                pairs[counter].loser = j;
                counter++;
                pair_count = counter;
            }
        }
    }
    printf("pair_count = %i\n", pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair temp;
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - 1 - i; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < pair_count; i++)
    {
        printf("sorted pair #%i = { winner:%i , loser: %i }\n", i + 1, pairs[i].winner, pairs[i].loser);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (pairs[i].loser == pairs[j].winner)
            {
                for (int k = 0; k < pair_count; k++)
                {
                    if (pairs[k].winner == pairs[j].loser && pairs[k].loser == pairs[i].winner)
                    {
                        printf("CYCLE!!! pairs[%i] is the last found.\n", k);
                        for (int l = 0; l < pair_count; l++)
                        {
                            if (preferences[pairs[k].winner][pairs[k].loser] > preferences[pairs[l].winner][pairs[l].loser])
                            {
                                locked[pairs[l].winner][pairs[l].loser] = false;
                                return;
                            }
                        }
                        locked[pairs[k].winner][pairs[k].loser] = false;
                        return;
                    }
                }
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO

    int counter;
    for (int i = 0; i < candidate_count; i++)
    {
        counter = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                counter++;
            }
            if (counter == candidate_count - 1)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }
    return;
}

