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
bool cycle_check(int first, int second);

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

    pair_count = 0;
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
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // ranks[j] array stored in order of preference per voter with ranks[j] = i where i is the index of the candidates array to be pulled out later
    int i;
    for (i = 0; i < candidate_count; i++)
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
    // increase the preferences[rank[0 -> 1 -> ...]][rank[1 -> 2 -> ...]] array by 1 to store the voters preference of their first choice to second and so on
    // This stores an array which when all voter have finished, will show the overall values of how many people prefer one candidate to another
    int i, j;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = 1; j < candidate_count - i; j++)
        {
            preferences[ranks[i]][ranks[i + j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // pair_count has been initilaized to 0 in the main function
    // If there is a preference between 2 candidates then store in the pairs array the winner and loser's i/j value which corresponds to their index in the candidates[array]
    int i, j;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Cycle through and if the preferences value is larger than the previous then swap them
    // j must depend on i as that is how you make sure they are sorted next to each other
    int i, j;
    pair z;
    for (i = 0; i < pair_count; i++)
    {
        for (j =  i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                z = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = z;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // Seperate function needed to keep looping until the graph has been checked for a cycle
    // using x and y to just visually simply the winner and loser in the functions
    int i, x, y;
    for (i = 0; i < pair_count; i++)
    {
        x = pairs[i].winner;
        y = pairs[i].loser;
        if (!cycle_check(x, y))
        {
            locked[x][y] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // Print winner if they are found to have no losses in the locked[][] array
    int i, j;
    for (i = 0; i < candidate_count; i++)
    {
        int source = 1;
        for (j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                source = 0;
                break;
            }
        }
        if (source == 1)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

// Extra function needed to run until all options are checked for a cycle
bool cycle_check(int first, int second)
{
    // First see if the locked pair would create an immediate cycle
    // Next check that the input winner has any locked pairs where they are the loser, if not then just return false so that the function can lock the pair
    // Lastly if the winner does have any locked pairs where they are the loser then we need to loop back to the top of the cycle_check to see check again till there is no cycle and then return false
    int i;
    if (locked[second][first] == true)
    {
        return true;
    }
    for (i = 0; i < candidate_count; i++)
    {
        if (locked[i][first] == true)
        {
            return cycle_check(i, second);
        }
    }
    return false;
}