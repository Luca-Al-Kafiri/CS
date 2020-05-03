#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int x = 0; x < candidate_count; x++)
    {
        if (strcmp(name, candidates[x].name) == 0)
        {
            candidates[x].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate winner = candidates[0]; // set the first candidate as the winner
    for (int z = 1; z < candidate_count; z++) // compare each candidate with the winner
    {
        if (winner.votes < candidates[z].votes) // if any candidate has more votes he became the winner
        {
            winner = candidates[z];
        }
    }
    for (int w = 0; w < candidate_count; w++) // check if any other candidate has same votes as the winner
    {
        if (winner.votes == candidates[w].votes)
        {
            printf("%s\n", candidates[w].name);
        }
    }
}

